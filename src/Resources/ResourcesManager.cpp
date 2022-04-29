#include "ResourcesManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

ResourcesManager::ResourcesManager(const string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

string ResourcesManager::GetFileString(const string& relativeFilePath) const
{
	ifstream f;
	f.open(m_path + "/" + relativeFilePath.c_str(), ios::in | ios::binary);
	if (!f.is_open())
	{
		cerr << "Feiled to open file: " << relativeFilePath << endl;
		return string{};
	}

	stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

shared_ptr<Renderer::ShaderProgram> ResourcesManager::loadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath)
{
	string vertexString = GetFileString(vertexPath);
	if (vertexString.empty())
	{
		cerr << "No vertex shader|" << endl;
		return nullptr;
	}

	string fragmentString = GetFileString(fragmentPath);
	if (fragmentString.empty())
	{
		cerr << "No fragment shader|" << endl;
		return nullptr;
	}

	shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, make_shared< Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}

	cerr << "Can`t load shader program:\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << endl;

	return nullptr;
}

shared_ptr<Renderer::ShaderProgram> ResourcesManager::getShaderPrograms(const string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	cerr << "Can`t Find the shader programs: " << shaderName << endl;
	return nullptr;
}