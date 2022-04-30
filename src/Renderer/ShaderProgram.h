#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const string& vertexShader, const string& fragmentShader);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setInt(const string& name, const GLint value);

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	private:
		bool createShader(const string& source, const GLenum shaderType, GLuint& shaderID);

		bool m_isCompiled = false;
		GLuint M_ID = 0;
	};
}