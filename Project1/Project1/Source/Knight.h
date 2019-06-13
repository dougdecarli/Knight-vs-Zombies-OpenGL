#pragma once
#include "GameObject.h"

class Knight : GameObject {

private:

	VertexArrayObject m_vao;
	Shader m_shader;
	Texture m_texture;
	GLfloat m_offsetX;
	GLfloat m_offsetY;
	Direction m_direction;
	KnightAction m_action;
	glm::mat4 m_mvp;
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_proj;
	int m_sync;
	bool m_alive;
	bool m_finishedAttacking;
	bool m_dying;

public:

	Knight() :
		m_offsetX(0.0f),
		m_offsetY(0.0f),
		m_direction(Direction::RIGHT),
		m_action(KnightAction::IDLE),
		m_vao(VertexArrayObject()),
		m_shader(Shader()),
		m_alive(true),
		m_finishedAttacking(false),
		m_dying(false)
	{
		CreateData();
	}

	void CreateData()
	{
		GLfloat vertices[] = { 0.0f, 0.0f, 120.0f, 0.0f, 120.0f, 140.0f, 0.0f, 140.0f };
		GLfloat textureCoords[] = { 0.0f, 0.0f, 0.1f, 0.0f, 0.1f, 0.166f, 0.0f, 0.166f };
		GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

		VertexBufferObject vbo1 = VertexBufferObject(vertices, sizeof(vertices));
		VertexBufferObject vbo2 = VertexBufferObject(textureCoords, sizeof(textureCoords));
		VertexBufferObject vbo3 = VertexBufferObject(indices, sizeof(indices), GL_ELEMENT_ARRAY_BUFFER);

		m_vao.AddBuffer(vbo1, 2);
		m_vao.AddBuffer(vbo2, 2);
		m_vao.AddBuffer(vbo3, 3, GL_ELEMENT_ARRAY_BUFFER);

		m_shader.CreateShader("C:\\Users\\i871294\\OneDrive - SAP SE\\GitHub\\Project1\\Project1\\Project1\\resources\\shaders\\Sprite.vert",
			"C:\\Users\\i871294\\OneDrive - SAP SE\\GitHub\\Project1\\Project1\\Project1\\resources\\shaders\\Sprite.frag");

		m_texture = Texture("C:\\Users\\i871294\\OneDrive - SAP SE\\GitHub\\Project1\\Project1\\Project1\\resources\\textures\\Game\\knight.png");

		m_proj = glm::ortho(0.0f, 1020.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		m_view = glm::mat4(1.0f);
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 80.0f, 0)); // Initial position
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

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		if (m_action != KnightAction::IDLE)
		{
			if (m_sync > 12)
				m_sync = 0;

			if (m_sync % 4 == 0)
				m_offsetX += 0.1f;

			m_sync += 1;
		}

		if (m_action == KnightAction::FADE)
		{
			if (m_offsetX > 1.0f)
			{
				m_alive = false;
			}
			else if (m_offsetX <= 1.0f)
			{
				m_alive = true;
			}
		}
		else if (m_action == KnightAction::ATTACK)
		{
			if (m_offsetX > 1.0f)
			{
				m_finishedAttacking = true;
				m_offsetX = 0.0f;
				m_offsetY = 0.125f;
				m_action = KnightAction::IDLE;
			}
			else if (m_offsetX <= 1.0f)
			{
				m_finishedAttacking = false;
			}
		}
	}

	void ProcessInput(int key)
	{
		if (key == GLFW_KEY_R)
		{
			Reset();
		}

		if (key == GLFW_KEY_D)
		{
			m_direction = Direction::RIGHT;
			m_action = KnightAction::WALK;
		}
		else if (key == GLFW_KEY_A)
		{
			m_direction = Direction::LEFT;
			m_action = KnightAction::WALK;
		}
		else if (key == GLFW_KEY_SPACE)
		{
			m_action = KnightAction::ATTACK;
		}

		else if (key == GLFW_KEY_F)
		{
			m_action = KnightAction::FADE;
		}

		else
		{
			m_action = KnightAction::IDLE;
		}

		ProcessState();
	}

	void ProcessState()
	{
		m_alive = true;

		if (m_direction == Direction::RIGHT)
		{
			if (m_action == KnightAction::WALK)
			{
				m_offsetY = 0.0f;
				Translate(2.0f, 0);
			}
			else if (m_action == KnightAction::ATTACK)
			{
				m_offsetY = 0.166f;
			}
			else if (m_action == KnightAction::IDLE)
			{
				m_offsetX = 0.0f;
				m_offsetY = 0.166f * 2;
			}
			else if (m_action == KnightAction::FADE)
			{
				m_offsetY = 0.166 * 2;
			}
		}
		else if (m_direction == Direction::LEFT)
		{
			if (m_action == KnightAction::WALK)
			{
				m_offsetY = 0.166f * 3;
				Translate(-2.0f, 0);
			}
			else if (m_action == KnightAction::ATTACK)
			{
				m_offsetY = 0.166f * 4;
			}
			else if (m_action == KnightAction::IDLE)
			{
				m_offsetX = 0.0f;
				m_offsetY = 0.166f * 5;
			}
			else if (m_action == KnightAction::FADE)
			{
				m_offsetY = 0.166 * 5;
			}
		}
	}

	void Reset()
	{
		m_proj = glm::ortho(0.0f, 1020.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		m_view = glm::mat4(1.0f);
		m_model = glm::mat4(1.0f);
		m_model = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 80.0f, 0)); // Initial position
		m_mvp = m_proj * m_view * m_model;
		m_alive = true;
		m_action = KnightAction::IDLE;
		m_dying = false;
	}

	void Translate(GLfloat x, GLfloat y)
	{
		m_model = glm::translate(m_model, glm::vec3(x, y, 0));
		m_mvp = m_proj * m_view * m_model;
	}

	void Die()
	{
		m_dying = true;
		m_offsetX = 0;
		m_action = KnightAction::FADE;
		ProcessState();
	}

	bool IsAttacking()
	{
		if (m_action == KnightAction::ATTACK)
		{
			return true;
		}

		return false;
	}

	bool IsWalking()
	{
		if (m_action == KnightAction::WALK)
			return true;

		return false;
	}

	inline bool IsDying() { return m_dying; }
	inline bool IsAlive() { return m_alive; }
	inline bool FinishedAttacking() { return m_finishedAttacking; }
	inline GLfloat GetPositionX() { return m_model[3][0]; }
	inline GLfloat GetPositionY() { return m_model[3][1]; }
	inline GLfloat GetOffsetX() { return m_offsetX; }
	inline GLfloat GetOffsetY() { return m_offsetY; }
	inline GLfloat GetWidth() { return 0.1f; }
	inline GLfloat GetHeight() { return 0.166f; }
	inline KnightAction GetCurrentAction() { return m_action; }

	bool IsInAttackHitbox(GLfloat zombie_x, GLfloat zombie_width)
	{
		GLfloat knight_x = this->GetPositionX();
		GLfloat knight_width = this->GetWidth();
		GLfloat knight_range = knight_x + knight_width;
		GLfloat zombie_range = zombie_x + zombie_width;
		int left_bias, right_bias = 0;


		// When the knight is approaching from the left
		if (m_direction == Direction::LEFT)
			left_bias = 60;
		else
			left_bias = 30;

		if (zombie_range > knight_x)
			if ((zombie_x - knight_range) < left_bias)
				return true;

		// When the knight is approaching from the right
		if (m_direction == Direction::RIGHT)
			right_bias = 60;
		else
			right_bias = 30;

		if (knight_range > zombie_x)
			if ((knight_x - zombie_range) < right_bias)
				return true;

		return false;
	}

};
