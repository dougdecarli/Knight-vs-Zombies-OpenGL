#include "main.h"

GLFWwindow* window;
int g_width = 1020;
int g_heigth = 600;
int g_key;

int main(void) 
{
	Init();
	GameLoop();
	glfwTerminate();
	return 0;
}


void GameLoop()
{
	Graveyard graveyard = Graveyard();
	Knight knight = Knight();
	Zombie zombie = Zombie();
	GLuint zombies_killed = 0;

	if (StartGame() == 1)
	{
		while (!glfwWindowShouldClose(window))
		{
			ClearBuffers();

			graveyard.ProcessInput(g_key);

			if (!knight.IsDying())
				knight.ProcessInput(g_key);

			if (!zombie.IsDying())
				zombie.ProcessInput(g_key);

			if (knight.IsAttacking())
			{
				if (!zombie.IsDying())
				{
					if (zombie.IsInAttackHitbox(knight.GetPositionX(), knight.GetWidth()))
					{
						zombies_killed++;
						zombie.Die(knight.GetPositionX());
						std::cout << std::endl;
						std::cout << "You killed a zombie! Thus far you killed " << zombies_killed << " zombies." << std::endl;
					}
				}
			}
			else
			{
				if (!knight.IsDying())
				{
					if (knight.IsInAttackHitbox(zombie.GetPositionX(), zombie.GetWidth()))
					{
						std::cout << std::endl;
						std::cout << "You died. Game Over!!!" << std::endl;
						knight.Die();
					}
				}
			}

			graveyard.Draw();
			knight.Draw();
			zombie.Draw();

			if (!knight.IsAlive())
			{
				std::cout << std::endl;
				std::cout << "Press any key to restart or q to quit." << std::endl;

				char key;

				std::cin >> key;

				if (key == 'q')
					exit(0);
				
				zombies_killed = 0;
				knight.Reset();
				zombie.Reset();
			}

			if (!knight.IsWalking() && knight.FinishedAttacking() && !knight.IsDying())
				std::memset(&g_key, 0, sizeof(g_key));

			SwapBuffers();
		}
	}
}

void Init() 
{
	if (!glfwInit())
		std::cout << "GLFW could not be initialized properly!" << std::endl;

	window = glfwCreateWindow(g_width, g_heigth, "Knight vs Zombies", NULL, NULL);

	if (!window) 
	{
		glfwTerminate();
		std::cout << "GLFW could not create a window properly!" << std::endl;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW could not initialize its entry points properly!" << std::endl;

	glViewport(0, 0, g_width, g_heigth);
	glfwSwapInterval(1);
	glfwSetWindowSizeCallback(window, WindowResizeCallback);
	glfwSetKeyCallback(window, KeyboardCallback);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int StartGame()
{
	std::cout << "Welcome to Knight vs Zombies" << std::endl;
	std::cout  << std::endl;	
	std::cout << "Instructions: " << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "Press D to Walk Right" << std::endl;
	std::cout << "Press A to Walk Left" << std::endl;
	std::cout << "Press Space to Attack" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Press any key to Start the Game or q to quit" << std::endl;

	char key;

	std::cin >> key;

	if (key == 'q')
		return -1;

	std::cout << std::endl;
	std::cout << std::endl;
	return 1;
}

void ClearBuffers() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void SwapBuffers() 
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		g_key = key;
}

void WindowResizeCallback(GLFWwindow* window, int width, int height) 
{
	g_width = width;
	g_heigth = height;
	glViewport(0, 0, width, height);
}