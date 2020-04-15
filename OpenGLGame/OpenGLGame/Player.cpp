#include "Player.h"

float Player::Speed = 100.0f;
glm::vec2 Player::Size = glm::vec2(20.0f, 20.0f);

Player::Player()
{
	Crash = false;
	Pos = glm::vec2(0.0f, 0.0f);
	Vector= glm::vec2(0.0f, 0.0f);
	Texture PT = Texture("container.jpg");
	PlayerTexture = PT;
}

void Player::UpdatePlayerPos(float dt)
{
	if (Pos.x > 390)
	{
		Pos.x = 390;
		Vector = glm::vec2(0.0f, 0.0f);
	}
	if (Pos.x < -390)
	{
		Pos.x = -390;
		Vector = glm::vec2(0.0f, 0.0f);
	}
	if (Pos.y > 290)
	{
		Pos.y = 290;
		Vector = glm::vec2(0.0f, 0.0f);
	}
	if (Pos.y < -290)
	{
		Pos.y = -290;
		Vector = glm::vec2(0.0f, 0.0f);
	}
	Pos += dt * Speed * Vector;
}

void Player::CheckCrash(Bullet& bullet)
{
	bool collisionX = Pos.x + Size.x / 2 >= bullet.Pos.x - bullet.Size.x / 2 && bullet.Pos.x + bullet.Size.x / 2 >= Pos.x - Size.x / 2;
	bool collisionY = Pos.y + Size.y / 2 >= bullet.Pos.y - bullet.Size.y / 2 && bullet.Pos.y + bullet.Size.y / 2 >= Pos.y - Size.y / 2;
	if(collisionX && collisionY)
	{
		Crash = true;
	}
}

void Player::IniPlayer()
{
	Crash = false;
	Pos = glm::vec2(0.0f, 0.0f);
	Vector = glm::vec2(0.0f, 0.0f);
}

void Player::RenderPlayer()
{

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE1);
	PlayerTexture.BindTexture();
	GameObjectShader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3((Pos.x - 0.5f * Size.x), (Pos.y - 0.5f * Size.y), 0.0f));
	model = glm::scale(model, glm::vec3(Size, 1.0f));
	glUniform1i(glGetUniformLocation(GameObjectShader.ID, "image"), 1);
	glUniformMatrix4fv(glGetUniformLocation(GameObjectShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}