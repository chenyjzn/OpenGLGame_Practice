#ifndef WORDS_H
#define WORDS_H
#include <iostream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Shader.h"

const int Words_Texture_Cnt = 128;

struct Character
{
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	int Advance;
};

class Words
{
public:
	Words(glm::mat4 projection);
	unsigned int VAO, VBO;
	Shader WordsShader;
	Character WordsTexture[Words_Texture_Cnt];
	void LoadWordsTextures(std::string font, int fontSize);
	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
};

#endif
