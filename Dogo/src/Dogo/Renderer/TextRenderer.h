#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "ft2build.h"
#include "Dogo/Renderer/Shader.h"
#include FT_FREETYPE_H
namespace Dogo
{
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};

	struct TextRenderer
	{
		static unsigned int VAO, VBO;
		static void Init();
		static std::map<std::string, std::map<GLchar, Character>> FontCharacters;
		static void RenderText(Shader& shader, std::string font, std::string text, float x, float y, float scale, glm::vec3 color);
		static std::vector<std::string> GetAvailableFonts();
	};

}
