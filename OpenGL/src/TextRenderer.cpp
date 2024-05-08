#include "TextRenderer.h"

TextRenderer::TextRenderer()
{
	
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library." << std::endl;
		return;
	}

	if (FT_New_Face(ft, "res/fonts/Jersey25-Regular.ttf", 0, &face))
	{
		std::cout << "ERROR:FREETYPE: Failed to load font." << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); //disable byte-alignment restriction 

	for (unsigned char c = 32; c < 128; c++)
	{

		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load Gylph." << std::endl;
			std::cout << "Character code: " << c << std::endl;
			continue;
		}

		//generate texture for each of the characters
		generateGlyphTexture(face, c);
	}

	//clear freetype's resources
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	std::cout << "Text Renderer Init Success!" << std::endl;
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::generateGlyphTexture(FT_Face face, char c)
{
	unsigned int textureId;
	GLCall(glGenTextures(1, &textureId));
	GLCall(glBindTexture(GL_TEXTURE_2D, textureId));

	GLCall(glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer
	));

	// set texture options
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	Character character =
	{
		textureId,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		face->glyph->advance.x
	};
	
	Characters.insert(std::pair<char, Character>(c, character));
}

void TextRenderer::RenderText(Shader& shaderProgram, std::string text, VertexBuffer& vb, float x, float y, float scale, glm::vec4 color)
{
	shaderProgram.Bind();
	shaderProgram.SetUniform4F("u_Color", color.x, color.y, color.z, color.w);

	vb.Bind();
	//glActiveTexture(GL_TEXTURE0);

	//iterate through all characters 
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float width = ch.Size.x * scale;
		float height = ch.Size.y * scale;

		//update vertex buffer for each character
		float vertices[24] =
		{
			xpos,         ypos + height,   0.0f, 0.0f,
			xpos,         ypos,            0.0f, 1.0f,
			xpos + width, ypos,            1.0f, 1.0f,

			xpos,         ypos + height,   0.0f, 0.0f,
		    xpos + width, ypos,            1.0f, 1.0f,
			xpos + width, ypos + height,   1.0f, 0.0f
		};

		GLCall(glBindTexture(GL_TEXTURE_2D, ch.TextureId));

		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	vb.Unbind();
}
