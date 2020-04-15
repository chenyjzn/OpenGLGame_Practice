#include"Words.h"
#include"Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Words::Words(glm::mat4 projection)
{
	Shader ws = Shader("WordsVertex.vs", "WordsFragment.frag");
	WordsShader = ws;
	WordsShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(WordsShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
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

void Words::LoadWordsTextures(std::string font, int fontSize)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		printf("ERROR::FREETYPE: Could not init FreeType Library\n");

	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
		printf("ERROR::FREETYPE: Failed to load font\n");

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	for (int c = 0; c < Words_Texture_Cnt; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			printf("ERROR::FREETYTPE: Failed to load Glyph\n");
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		WordsTexture[c] =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void Words::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
	glActiveTexture(GL_TEXTURE2);
	glBindVertexArray(VAO);
	WordsShader.Use();
	glUniform3f(glGetUniformLocation(WordsShader.ID, "textColor"), color.x, color.y, color.z);
	glUniform1i(glGetUniformLocation(WordsShader.ID, "text"), 2);
	
	for (int i = 0; i< text.size(); i++)
	{
		Character ch = WordsTexture[text[i]];
		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		x += (ch.Advance >> 6)* scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}