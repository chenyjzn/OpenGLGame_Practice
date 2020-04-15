#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Texture.h"
#include "Bullet.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	static float Speed;
	static glm::vec2 Size;
	bool Crash;
	glm::vec2 Pos;
	glm::vec2 Vector;
	Texture PlayerTexture;
	void UpdatePlayerPos(float dt);
	void CheckCrash(Bullet&);
	void IniPlayer();
	void RenderPlayer();
};

#endif
