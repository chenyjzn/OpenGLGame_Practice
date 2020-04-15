#ifndef SHADER_H
#define SHADER_H
#include <string>

class Shader
{
public:
	Shader();
	Shader(const char* vertex_path, const char* fragment_path);
	unsigned int ID;
	void Use();
private:
	void CheckCompileErrors(unsigned int ID, std::string type);
};

#endif

