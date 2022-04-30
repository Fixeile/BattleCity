#include "Texture2D.h"

using namespace std;

namespace Renderer {
	Texture2D::Texture2D(const GLuint Width, GLuint Height,
		const unsigned char* data,
		const unsigned int channel,
		const GLenum filter,
		const GLenum wrapMode)
		: m_Width(Width)
		, m_Height(Height)
	{
		switch (channel)
		{
		case 4:
			m_mode = GL_RGBA;
			break;
		case 3:
			m_mode = GL_RGB;
			break;
		default:
			m_mode = GL_RGBA;
			break;
		}

		glGenTextures(1, &M_ID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, M_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D& Texture2D::operator = (Texture2D&& texture2d)
	{
		glDeleteTextures(1, &M_ID);
		M_ID = texture2d.M_ID;
		texture2d.M_ID = 0;
		m_mode = texture2d.m_mode;
		m_Width = texture2d.m_Width;
		m_Height = texture2d.m_Height;
		return *this;
	}

	Texture2D::Texture2D(Texture2D&& texture2d) noexcept
	{
		M_ID = texture2d.M_ID;
		texture2d.M_ID = 0;
		m_mode = texture2d.m_mode;
		m_Width = texture2d.m_Width;
		m_Height = texture2d.m_Height;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &M_ID);
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, M_ID);
	}
}