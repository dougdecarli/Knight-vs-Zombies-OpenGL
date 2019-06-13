#pragma once

#include <GL/glew.h>

class VertexBufferObject {

private:

	GLuint m_id;

public:

	VertexBufferObject(const void* data, GLuint size, GLuint type = GL_ARRAY_BUFFER) :
		m_id(0)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(type, m_id);
		glBufferData(type, size, data, GL_STATIC_DRAW);
	}

	void Bind(GLuint type = GL_ARRAY_BUFFER) const 
	{
		glBindBuffer(type, m_id);
	}

	inline GLuint GetId() const 
	{ 
		return m_id; 
	}
	
};