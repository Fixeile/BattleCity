#pragma once

#include <string>
#include <memory>
#include <map>

using namespace std;

namespace Renderer {
	class ShaderProgram;
	class Texture2D;
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
	shared_ptr<Renderer::Texture2D> loadTexture(const string& textureName, const string& texturePath);
	shared_ptr<Renderer::Texture2D> getTexture(const string& textureName);

private:
	string GetFileString(const string& relativeFilePath) const;


	typedef map<const string, shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	typedef map<const string, shared_ptr<Renderer::Texture2D>>TextureMap;
	TextureMap m_texture;

	string m_path;
};