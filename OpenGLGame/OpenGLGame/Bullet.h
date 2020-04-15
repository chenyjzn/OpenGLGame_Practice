#ifndef BULLET_H
#define BULLET_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Texture.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	static float Speed;
	static float Radius;
	static glm::vec2 Size;
	bool OutofWindow;
	glm::vec2 Vector;
	glm::vec2 Pos;
	Texture BulletTexture;
	void Move(float dt, glm::vec2 target);
	void PosIni(glm::vec2 inipos, glm::vec2 target);
	void RenderBullet();
private:
};

#endif