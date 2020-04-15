#include "Bullet.h"

float Bullet::Speed = 100.0f;
float Bullet::Radius = 5.0f;
glm::vec2 Bullet::Size = glm::vec2(2 * Radius, 2 * Radius);

Bullet::Bullet()
{
	OutofWindow = false;
	Pos = glm::vec2(0.0f, 0.0f);
	Vector = glm::vec2(0.0f, 0.0f);	
	Texture BT = Texture("awesomeface.png");
	BulletTexture = BT;
}
void Bullet::PosIni(glm::vec2 inipos, glm::vec2 target)
{
	Pos = inipos;
	Vector = glm::normalize(target - Pos);
}
void Bullet::Move(float dt, glm::vec2 target)
{
	if (Pos.x > 400 || Pos.x < -400 || Pos.y>300 || Pos.y < -300)
	{
		Pos.x = -Pos.x;
		Pos.y = -Pos.y;
		float xx = (float)(rand() % 100) * (rand() % 2 ? 1 : -1);
		float yy = (float)(rand() % 100) * (rand() % 2 ? 1 : -1);
		glm::vec2 bullettarget = rand() % 2 ? glm::vec2(target.x + xx, target.y + yy) : glm::vec2(xx, yy);
		Vector = glm::normalize(bullettarget - Pos);
	}
	Pos += Vector * Speed * dt;
}

void Bullet::RenderBullet()
{
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	BulletTexture.BindTexture();
	GameObjectShader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3((Pos.x - 0.5f * Size.x), (Pos.y - 0.5f * Size.y), 0.0f));
	model = glm::scale(model, glm::vec3(Size, 1.0f));
	glUniform1i(glGetUniformLocation(GameObjectShader.ID, "image"), 0);
	glUniformMatrix4fv(glGetUniformLocation(GameObjectShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}