#pragma once

#include <string>
#include <memory>
#include <map>

using namespace std;

namespace Renderer {
	class ShaderProgram;
}

class ResourcesManager {
public:
	ResourcesManager(const string& executablePath);
	~ResourcesManager() = default;
	
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	ResourcesManager& operator=(ResourcesManager&&) = delete;
	ResourcesManager(ResourcesManager&&) = delete;

	shared_ptr<Renderer::ShaderProgram> loadShaders(const string& shaderName, const string& vertexPath, const string& fragmentPath);
	shared_ptr<Renderer::ShaderProgram> getShaderPrograms(const string& shaderName);

private:
	string GetFileString(const string& relativeFilePath) const;


	typedef map<const string, shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	string m_path;
};