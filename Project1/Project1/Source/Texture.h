#pragma once

#include <GL/glew.h>
#include <iostream>
#include <stb_image.h>

class Texture {


private:

	std::string m_filepath;
	GLuint m_id;
	unsigned char* m_textureBuffer;
	int m_width;
	int m_height;
	int m_bitsPerPixel;

public:

	Texture()
	{

	}

	Texture(const std::string& filepath) :
		m_id(0),
		m_filepath(filepath),
		m_textureBuffer(nullptr),
		m_width(0),
		m_height(0),
		m_bitsPerPixel(0)
	{
		m_filepath = filepath;
		stbi_set_flip_vertically_on_load(1);
		m_textureBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

		if (!m_textureBuffer)
			std::cout << "Could not open texture: " << filepath.c_str() << std::endl;

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureBuffer);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(m_textureBuffer);
	}

	void Bind() const 
	{ 
		glBindTexture(GL_TEXTURE_2D, m_id); 
	}

	void Unbind() const { 
		glBindTexture(GL_TEXTURE_2D, 0); 
	}

	inline int GetWidth() const 
	{
		return m_width; 
	}

	inline int GetHeight() const
	{ 
		return m_height; 
	}

	inline GLuint GetId() const 
	{ 
		return m_id; 
	}

};