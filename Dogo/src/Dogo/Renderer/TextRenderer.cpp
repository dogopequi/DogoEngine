#include "dgpch.h"
#include "TextRenderer.h"
#include "Dogo/Logger.h"
namespace Dogo
{
	unsigned int TextRenderer::VAO, TextRenderer::VBO;
	std::map<std::string, std::map<GLchar, Character>> TextRenderer::FontCharacters;
	void TextRenderer::Init()
	{
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            DG_FATAL("Could not init FreeType Library");
            return;
        }

        std::string fontDir = "../Dogo/resources/Fonts/";
        for (const auto& entry : std::filesystem::directory_iterator(fontDir))
        {
            if (entry.is_regular_file())
            {
                std::string path = entry.path().string();
                std::string extension = entry.path().extension().string();
                std::string filename = entry.path().stem().string(); // font name without extension

                // Only accept .ttf or .otf fonts
                if (extension == ".ttf" || extension == ".otf")
                {
                    FT_Face face;
                    if (FT_New_Face(ft, path.c_str(), 0, &face))
                    {
                        DG_WARN("Failed to load font: {}", path);
                        continue;
                    }

                    FT_Set_Pixel_Sizes(face, 0, 48);
                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                    std::map<GLchar, Character> characters;

                    for (GLubyte c = 0; c < 128; c++)
                    {
                        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                            DG_WARN("Failed to load glyph '{}' from font '{}'", c, filename.c_str());
                            continue;
                        }

                        unsigned int texture;
                        glGenTextures(1, &texture);
                        glBindTexture(GL_TEXTURE_2D, texture);
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                            face->glyph->bitmap.width,
                            face->glyph->bitmap.rows,
                            0, GL_RED, GL_UNSIGNED_BYTE,
                            face->glyph->bitmap.buffer);

                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                        Character character = {
                            texture,
                            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                            static_cast<unsigned int>(face->glyph->advance.x)
                        };

                        characters.insert(std::make_pair(c, character));
                    }

                    FontCharacters[filename] = characters;
                    DG_INFO("Loaded font: {}", filename);

                    FT_Done_Face(face);
                }
            }
        }

        FT_Done_FreeType(ft);

        // Set up VAO/VBO as before...
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}
	void TextRenderer::RenderText(Shader& shader, std::string font, std::string text, float x, float y, float scale, glm::vec3 color)
	{
        auto it = FontCharacters.find(font);
        if (it == FontCharacters.end()) {
            DG_FATAL("Font {} not loaded", font.c_str());
            return;
        }

        const auto& characters = it->second;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// activate corresponding render state	
		shader.Bind();
		shader.SetUniform3f("textColor", color);
		glm::mat4 projection = glm::orthoRH_NO(0.0f, 1280.0f, 0.0f, 720.0f, 0.0f, 1.0f);
		shader.SetUniformMatrix4f("projection", projection);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			char currentChar = *c;
            auto it = characters.find(currentChar);
            if (it == characters.end()) {
                DG_WARN("Character '{}' not found in font '{}'", currentChar, font);
                continue;  // Skip this character if it's not found
            }
            Character ch = it->second;  // Get the Character struct

			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
    std::vector<std::string> TextRenderer::GetAvailableFonts(){
    std::vector<std::string> fonts;
    for (const auto& [name, map] : FontCharacters)
        fonts.push_back(name);
    return fonts;
        }
}

