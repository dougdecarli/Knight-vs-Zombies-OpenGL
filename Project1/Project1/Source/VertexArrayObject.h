#pragma once

#include "VertexBufferObject.h"

class VertexArrayObject {

private:

	GLuint m_id;
	GLuint m_numberOfVBOs;

public:

	VertexArrayObject()
	{
		m_numberOfVBOs = 0;
		glGenVertexArrays(1, &m_id);
	}

	void AddBuffer(VertexBufferObject& vbo, GLuint size, GLuint type = GL_ARRAY_BUFFER)
	{
		Bind();
		vbo.Bind();

		glBindBuffer(type, vbo.GetId());
		glEnableVertexAttribArray(m_numberOfVBOs);
		glVertexAttribPointer(m_numberOfVBOs, size, GL_FLOAT, GL_FALSE, 0, nullptr);

		m_numberOfVBOs += 1;
	}

	void Bind() const
	{
		glBindVertexArray(m_id);
	}

	void Unbind() const
	{
		glBindVertexArray(0);
	}

};