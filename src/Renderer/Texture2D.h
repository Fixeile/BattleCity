#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

namespace Renderer {
	class Texture2D
	{
	public:
		Texture2D(const GLuint Width, GLuint Height, 
					const unsigned char* data,
					const unsigned int channel = 4,
					const GLenum filter = GL_LINEAR,
					const GLenum wrapMode = GL_CLAMP_TO_EDGE);

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator = (const Texture2D&) = delete;
		Texture2D& operator = (Texture2D&& texture2d);
		Texture2D(Texture2D&& texture2d);
		~Texture2D();

		void bind() const;

	private:
		GLuint M_ID;
		GLenum m_mode;
		unsigned int m_Width;
		unsigned int m_Height;
	};
}