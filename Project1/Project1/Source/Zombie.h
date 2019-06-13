#pragma once

#include "GameObject.h"

class Zombie : GameObject {
private:
	VertexArrayObject m_vao;
	Shader m_shader;
	Texture m_texture;
	GLfloat m_offsetX;
	GLfloat m_offsetY;


	Direction m_direction;
	ZombieAction m_action;

	int m_sync;

	glm::mat4 m_mvp;
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_proj;

	bool m_dying;
	bool m_alive;
	GLuint count = 0;
	GLuint m_respawns;
	GLfloat knigthPositionXKill = 0;

public:
	Zombie() :
		m_shader(Shader()),
		m_vao(VertexArrayObject()),
		m_offsetX(0),
		m_offsetY(0),
		m_direction(Direction::LEFT),
		m_action(ZombieAction::WALK),
		m_alive(true),
		m_dying(false),
		m_respawns(1)
	{
		m_offsetX = 0.0f;
		m_offsetY = 0.0f;
		m_sync = 0;

		GLfloat vertices[] = { 0.0f, 0.0f, 120.0f, 0.0f, 120.0f, 140.0f, 0.0f, 140.0f };
		GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
		GLfloat textureVertices[] = { // X = 1/columns && Y = 1/rows
			0.0f, 0.0f,
			0.1f, 0.0f,
			0.1f, 0.166f,
			0.0f, 0.166f
		};

		VertexBufferObject vbo1 = VertexBufferObject(vertices, sizeof(vertices));
		VertexBufferObject vbo2 = VertexBufferObject(textureVertices, sizeof(textureVertices));
		VertexBufferObject vbo3 = VertexBufferObject(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);

		m_vao.AddBuffer(vbo1, 2);
		m_vao.AddBuffer(vbo2, 2);
		m_vao.AddBuffer(vbo3, 3, GL_ELEMENT_ARRAY_BUFFER);

		m_shader.CreateShader("C:\\Users\\i871294\\OneDrive - SAP SE\\GitHub\\Project1\\Project1\\Project1\\resources\\shaders\\Sprite.vert",
			"C:\\Users\\i871294\\OneDrive - SAP SE\\GitHub\\Project1\\Project1\\Project1\\resources\\shaders\\Sprite.frag");

		m_texture = Texture("C:\\Users\\i871294\\OneDrive - SAP SE\\GitHub\\Project1\\Project1\\Project1\\resources\\textures\\game\\zombie.png");

		m_proj = glm::ortho(0.0f, 1020.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		m_view = glm::mat4(1.0f);
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(800.0f, 70.0f, 0));

		m_mvp = m_proj * m_view * m_model;
	};


	void Draw()
	{
		glActiveTexture(GL_TEXTURE0);

		m_vao.Bind();
		m_shader.Use();
		m_texture.Bind();

		m_shader.SetTexture("u_Texture", 0);
		m_shader.SetFloat("u_Depth", -0.90f);
		m_shader.SetFloat("u_OffsetX", m_offsetX);
		m_shader.SetFloat("u_OffsetY", m_offsetY);
		m_shader.SetMat4("u_MVP", m_mvp);


		if (m_action == ZombieAction::FADE)
		{
			if (m_offsetX >= 1.0f)
			{
				this->Reset();
			}
			else if (m_offsetX < 1.0f)
			{
				if (m_sync > 10)
					m_sync = 0;

				if (m_sync % 5 == 0)
					m_offsetX += 0.1f;

				m_sync += 1;

				m_alive = false;
			}
		}
		else {

			if (m_sync > 10)
				m_sync = 0;

			if (m_sync % 5 == 0)
				m_offsetX += 0.1f;

			m_sync += 1;
		}

		if (GetPositionX() > 1000.0f || GetPositionX() < 0.0f) {
			this->Reset();
		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	};


	void ProcessInput(int key)
	{
		if (!m_dying)
		{
			if (key == GLFW_KEY_R)
			{
				Reset();
				m_direction = Direction::LEFT;
				m_action = ZombieAction::WALK;
			}
		}

		ProcessState();
	}

	void ProcessState()
	{
		if (m_offsetX > 1.0f)
		{
			if (count == 10)
			{
				if (m_direction == Direction::RIGHT && this->GetPositionX() > 960)
				{
					m_direction = Direction::LEFT;
					m_action = ZombieAction::WALK;
				}
				else if (m_direction == Direction::LEFT && this->GetPositionX() < 20)
				{
					m_direction = Direction::RIGHT;
					m_action = ZombieAction::WALK;
				}
				else
				{
					ZombieAction zombieActionRandom = ZombieAction(rand() % 3);
					m_action = zombieActionRandom;

					Direction zombieDirectionRandom = Direction(rand() % 3);
					m_direction = zombieDirectionRandom;

					if (m_action == ZombieAction::FADE || m_action == ZombieAction::IDLE)
						m_action = ZombieAction::WALK;
				}
			}
		}

		if (m_direction == Direction::RIGHT)
		{
			if (m_action == ZombieAction::ATTACK)
			{
				m_offsetY = 0.0f;
			}
			else if (m_action == ZombieAction::IDLE)
			{
				m_offsetX = 0.0f;
				m_offsetY = 0.166f;
			}
			else if (m_action == ZombieAction::WALK)
			{
				m_offsetY = 0.166f * 2;
				Translate(2.0f, 0);
			}
			else if (m_action == ZombieAction::FADE)
			{
				m_offsetY = 0.166f;
			}
		}

		else if (m_direction == Direction::LEFT)
		{
			if (m_action == ZombieAction::ATTACK)
			{
				m_offsetY = 0.166f * 3;
			}
			else if (m_action == ZombieAction::IDLE)
			{
				m_offsetY = 0.166f * 4;
			}
			else if (m_action == ZombieAction::WALK)
			{
				m_offsetY = 0.166f * 5;
				Translate(-2.0f, 0);
			}
			else if (m_action == ZombieAction::FADE)
			{
				m_offsetY = 0.166f * 4;
			}
		}

		count = rand() % 50;
	}

	void Translate(GLfloat x, GLfloat y) {
		m_model = glm::translate(m_model, glm::vec3(x, y, 0));
		m_mvp = m_proj * m_view * m_model;
	}


	bool IsAttacking()
	{
		if (m_action == ZombieAction::ATTACK)
			return true;

		return false;
	}

	void Die(GLfloat knigthPositionXKill)
	{
		this->knigthPositionXKill = knigthPositionXKill;
		m_dying = true;
		m_offsetX = 0;
		m_action = ZombieAction::FADE;
		ProcessState();

		m_respawns += 1;
	}


	void Reset()
	{
		m_proj = glm::ortho(0.0f, 1020.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		m_view = glm::mat4(1.0f);

		if (knigthPositionXKill > 600) {
			m_model = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 70.0f, 0)); // Initial position
			m_direction = Direction::RIGHT;

		}
		else {
			m_model = glm::translate(glm::mat4(1.0f), glm::vec3(970.0f, 70.0f, 0)); // Initial position
		}

		m_mvp = m_proj * m_view * m_model;
		m_alive = true;
		m_dying = false;
	}

	inline void SetOffsetX(GLfloat offsetX_new) { m_offsetX = offsetX_new; }
	inline bool IsDying() { return m_dying; }
	inline GLfloat GetPositionX() { return m_model[3][0]; }
	inline GLfloat GetPositionY() { return m_model[3][1]; }
	inline GLfloat GetOffsetX() { return m_offsetX; }
	inline GLfloat GetOffsetY() { return m_offsetY; }
	inline GLfloat GetWidth() { return 0.1f; }
	inline GLfloat GetHeight() { return 0.166f; }

	bool IsInAttackHitbox(GLfloat knight_x, GLfloat knight_width)
	{
		GLfloat zombie_x = this->GetPositionX();
		GLfloat zombie_width = this->GetWidth();
		GLfloat knight_range = knight_x + knight_width;
		GLfloat zombie_range = zombie_x + zombie_width;

		if (zombie_range > knight_x)
			if ((zombie_x - knight_range) < 90)
				return true;

		if (knight_range > zombie_x)
			if ((knight_x - zombie_range) < 90)
				return true;

		return false;
	}

};
