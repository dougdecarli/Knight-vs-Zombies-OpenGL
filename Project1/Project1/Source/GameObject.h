#pragma once

#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Shader.h"
#include "Layer.h"
#include "Math.h"
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

constexpr int right = 1;
constexpr int left = 2;

enum class Direction {
	IDLE = 0, LEFT = 1, RIGHT = 2
};

enum class ZombieAction {
	WALK = 0, ATTACK = 1, IDLE = 2, FADE = 3
};

enum class KnightAction {
	WALK = 0, ATTACK = 1, IDLE = 2, FADE = 3
};

enum class AnimationState {
	IN_PROGRESS = 0, FINISHED = 1
};

class GameObject abstract{
public:

};