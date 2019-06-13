#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Shader.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Layer.h"
#include <Windows.h>
#include <vector>
#include <iostream>
#include "Knight.h"
#include "Zombie.h"
#include "Graveyard.h"

void Init();
int StartGame();
void GameLoop();
void ClearBuffers();
void SwapBuffers();
void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MousePositionCallback(GLFWwindow* window, double x, double y);
void WindowResizeCallback(GLFWwindow* window, int width, int height);
bool HasCollisionHappened(Knight knight, Zombie zombie);
