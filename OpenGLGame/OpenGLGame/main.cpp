#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <ctime>

#include"Shader.h"
#include"Texture.h"
#include"GameObject.h"
#include"Bullet.h"
#include"Player.h"
#include"Words.h"

#include <ft2build.h>
#include FT_FREETYPE_H

const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const int BULLETS_CNT = 99;

enum GameState
{
	MENU,
	START,
	END
}State;

float GameStartTime;
float GameEndTime;

std::pair<int, int> posradom[3]{ std::make_pair(1, 1),std::make_pair(1, 0),std::make_pair(0, 1) };

void processInput(GLFWwindow* window, Player& ship,Bullet* bullet);
void IniObject(Player &ship, Bullet* bullets);

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bullets99", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glm::mat4 projection = glm::ortho((-1 * SCREEN_WIDTH / 2), (SCREEN_WIDTH / 2), (-1 * SCREEN_HEIGHT / 2), (SCREEN_HEIGHT / 2), -1.0f, 1.0f);

	GameObject::GameObjectInitial(projection);
	Player Ship;
	Bullet Bullets[BULLETS_CNT];

	IniObject(Ship, Bullets);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	Words ShowWords = Words(projection);
	
	ShowWords.LoadWordsTextures("arial.ttf", 48);
	
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		processInput(window,Ship,Bullets);
		
		if (State == MENU)
		{
			// Render MENU
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			ShowWords.RenderText("Press Enter to Start", -210.0f, 0.0f, 1.0f);
		}
		else if (State ==START)
		{

			// Update Game state
			GameEndTime = glfwGetTime();
			for (int i = 0; i < BULLETS_CNT; i++)
			{
				Ship.CheckCrash(Bullets[i]);
				Bullets[i].Move(deltaTime, Ship.Pos);
			}
			Ship.UpdatePlayerPos(deltaTime);
			// Render
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Ship.RenderPlayer();
			for (int i = 0; i < BULLETS_CNT; i++)
			{
				Bullets[i].RenderBullet();
			}

			if (Ship.Crash)
			{
				State = END;
			}
		}
		else if (State == END)
		{
			// Render
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Ship.RenderPlayer();
			for (int i = 0; i < BULLETS_CNT; i++)
			{
				Bullets[i].RenderBullet();
			}
			ShowWords.RenderText(std::to_string(GameEndTime - GameStartTime)+" Second", -210.0f, 0.0f, 1.0f);
		}	
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window, Player& ship, Bullet* bullet)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (State == MENU && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		GameStartTime = glfwGetTime();
		State = START;
	}

	if (State == START)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS|| glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			ship.Vector = glm::vec2(0.0f, 1.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS||glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			ship.Vector = glm::vec2(0.0f, -1.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			ship.Vector = glm::vec2(-1.0f, 0.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			ship.Vector = glm::vec2(1.0f, 0.0f);
		}
		else
		{
			ship.Vector = glm::vec2(0.0f, 0.0f);
		}
	}

	if (State == END && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		IniObject(ship, bullet);
		GameStartTime = glfwGetTime();
		State = START;
	}
}
void IniObject(Player& Ship, Bullet* Bullets)
{
	Ship.IniPlayer();
	srand(time(NULL));
	int possel = 0;
	for (int i = 0; i < BULLETS_CNT; i++)
	{
		float x = (float)(rand() % 200 + 200 * posradom[possel % 3].first) * (rand() % 2 ? 1 : -1);
		float y = (float)(rand() % 150 + 150 * posradom[possel % 3].second) * (rand() % 2 ? 1 : -1);
		float xt = (float)(rand() % 200) * (rand() % 2 ? 1 : -1);
		float yt = (float)(rand() % 150) * (rand() % 2 ? 1 : -1);
		Bullets[i].PosIni(glm::vec2(x, y), glm::vec2(xt, yt));
		possel++;
	}
}