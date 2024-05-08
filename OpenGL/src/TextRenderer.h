#pragma once

#include "Renderer.h"

#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <iostream>

#include "Shader.h"
#include "VertexBuffer.h"

struct Character
{
	unsigned int TextureId; 
	glm::ivec2 Size; 
	glm::ivec2 Bearing;
	unsigned int Advance; 
};

class TextRenderer
{
	private:
		FT_Library ft;
		FT_Face face;

		//char follows ASCII code (store 32 - 127)
		std::map<char, Character> Characters;

	public:
		TextRenderer();
		~TextRenderer();

		void generateGlyphTexture(FT_Face face, char c);

		void RenderText(Shader& shaderProgram, std::string text, VertexBuffer& vb, float x, float y, float scale, glm::vec4 color);
};
