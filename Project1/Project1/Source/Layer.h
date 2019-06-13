#pragma once
#include "Texture.h"

class Layer {

private:

	Texture m_texture;
	GLfloat m_depth;
	GLfloat m_offsetX;
	GLfloat m_rate;

public:

	Layer() 
	{
	}

	Layer(Texture texture, GLfloat depth, GLfloat offsetX) :
		m_texture(texture),
		m_depth(depth),
		m_offsetX(offsetX),
		m_rate(offsetX)
	{
	
	}

	void BindTexture() const
	{ 
		m_texture.Bind(); 
	}

	inline GLfloat GetDepth() const 
	{ 
		return m_depth; 
	}

	inline GLfloat GetOffsetX() const 
	{ 
		return  m_offsetX; 
	}

	inline void ScrollRight() 
	{
		m_offsetX += m_rate; 
	}

	inline void ScrollLeft() 
	{ 
		m_offsetX -= m_rate;  
	}

	inline void HaltScrolling()
	{ 
		m_offsetX = m_offsetX; 
	}

};
