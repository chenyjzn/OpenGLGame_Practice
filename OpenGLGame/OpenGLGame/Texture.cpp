#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Texture::Texture()
{

}

Texture::Texture(const char* filename)
{
	Wrap_S = GL_REPEAT;
	Wrap_T = GL_REPEAT;
	Filter_Min = GL_LINEAR;
	Filter_Max = GL_LINEAR;
	Internal_Format = GL_RGB;
	Image_Format = GL_RGB;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D,ID);

	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	if (data)
	{
		Width = width;
		Height= height;
		if (channels == 4)
		{
			Internal_Format = GL_RGBA;
			Image_Format = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, this->Width, this->Height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("load image failed.\n");
	}
	stbi_image_free(data);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}

