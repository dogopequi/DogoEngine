#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace Dogo
{
	struct UV
	{
		glm::vec2 uvMin;
		glm::vec2 uvMax;
		UV() : uvMin(0.0f, 0.0f), uvMax(1.0f, 1.0f) {}
		UV(const glm::vec2& min, const glm::vec2& max) : uvMin(min), uvMax(max) {}
		UV(float xMin, float yMin, float xMax, float yMax) : uvMin(xMin, yMin), uvMax(xMax, yMax) {}
	};

	inline UV GetTileUV(int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight)
	{
		float tilesPerRow = (float)(atlasWidth / tileWidth);
		float tilesPerCol = (float)(atlasHeight / tileHeight);

		float uMin = tileX / tilesPerRow;
		float vMin = tileY / tilesPerCol;
		float uMax = (tileX + 1) / tilesPerRow;
		float vMax = (tileY + 1) / tilesPerCol;

		float texelOffsetX = 0.5f / atlasWidth;
		float texelOffsetY = 0.5f / atlasHeight;

		uMin += texelOffsetX;
		uMax -= texelOffsetX;
		vMin += texelOffsetY;
		vMax -= texelOffsetY;

		return UV(uMin, vMin, uMax, vMax);
	}
}