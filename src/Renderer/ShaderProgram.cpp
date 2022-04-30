#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;
using namespace glm;

namespace Renderer 
{
	ShaderProgram::ShaderProgram(const string& vertexShader, const string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			cerr << "VERTEX SHADER compile-time error\n";

			return;
		} 

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			cerr << "FRAGMENT SHADER compile-time error" << endl;
			glDeleteShader(vertexShaderID);

			return;
		}

		M_ID = glCreateProgram();
		glAttachShader(M_ID, vertexShaderID);
		glAttachShader(M_ID, fragmentShaderID);
		glLinkProgram(M_ID);

		GLint succes;
		glGetProgramiv(M_ID, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(M_ID, 1024, nullptr, infoLog);
			cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << endl;
		}
		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint succes;
		glGetProgramiv(shaderID, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << endl;
			return false;
		}
		return true;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(M_ID);
	}

	void ShaderProgram::use() const
	{
		glUseProgram(M_ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(M_ID);
		M_ID = shaderProgram.M_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.M_ID = 0;
		shaderProgram.m_isCompiled = false;
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		M_ID = shaderProgram.M_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.M_ID = 0;
		shaderProgram.m_isCompiled = false;
	}

	void ShaderProgram::setInt(const string& name, const GLint value)
	{
		glUniform1i(glGetUniformLocation(M_ID, name.c_str()), value);
	}

	void ShaderProgram::setMatrix4(const string& name, mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(M_ID, name.c_str()), 1, GL_FALSE, value_ptr(matrix));
	}

}