#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader::Shader()
{

}
Shader::Shader(const char* vertex_path, const char* fragment_path)
{
	std::ifstream vertex_file;
	std::ifstream fragment_file;
	std::stringstream vertex_sstream;
	std::stringstream fragment_sstream;

	vertex_file.open(vertex_path);
	fragment_file.open(fragment_path);
	vertex_file.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragment_file.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	try
	{
		if (!vertex_file.is_open()|| !fragment_file.is_open())
		{
			throw std::exception("open file err");
		}
		vertex_sstream << vertex_file.rdbuf();
		fragment_sstream << fragment_file.rdbuf();

		std::string vertex_string = vertex_sstream.str();
		std::string fragment_string = fragment_sstream.str();
		const char* vertex_code = vertex_string.c_str();
		const char* fragment_code = fragment_string.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertex_code, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragment_code, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");

		vertex_file.close();
		fragment_file.close();
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::CheckCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char info_log[512];
	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE, &success);
		{
			if (!success)
			{
				glGetShaderInfoLog(ID, 512, NULL, info_log);
				std::cout << "Shader compile error: " << info_log << std::endl;
			}
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, info_log);
			std::cout << "Program linking error: " << info_log << std::endl;
		}
	}
}