#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
	Texture();
	Texture(const char* filename);
	unsigned int ID;
	int Width, Height;
	int Internal_Format;
	int Image_Format;
	int Wrap_S;
	int Wrap_T;
	int Filter_Min;
	int Filter_Max;
	void BindTexture();
private:
};

#endif
