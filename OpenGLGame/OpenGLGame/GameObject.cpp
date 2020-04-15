#include "GameObject.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader GameObject::GameObjectShader;
unsigned int GameObject::VAO;
unsigned int GameObject::VBO;
unsigned int GameObject::EBO;

void GameObject::GameObjectInitial(glm::mat4 projection)
{
	Shader GOS = Shader("GameObjectVertex.vs", "GameObjectFragment.frag");
	GameObjectShader = GOS;
	GameObjectShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(GameObjectShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	float vertices[] = {
		// Pos      // Tex
		0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};

	unsigned int indices[] = {
		0,1,2,
		2,1,3
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
