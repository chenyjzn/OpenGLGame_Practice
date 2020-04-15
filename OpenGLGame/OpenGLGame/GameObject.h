#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class GameObject
{
public:
	static void GameObjectInitial(glm::mat4 projection);
	static Shader GameObjectShader;
	static unsigned int VAO;
	static unsigned int VBO;
	static unsigned int EBO;
};

#endif