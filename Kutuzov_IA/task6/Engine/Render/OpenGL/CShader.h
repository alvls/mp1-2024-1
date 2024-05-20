#pragma once
#include <string>
#include <unordered_map>

class CShader
{
	std::string FilePath;
	unsigned int RendererID;
	// caching for uniforms
	std::unordered_map<std::string, int> UniformLocationCache;

public:
	CShader(const std::string& InFilePath);
	~CShader();

	void Bind() const;
	void UnBind() const;

	// Setting uniforms
	void SetUniform4f(const std::string& Name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& Name, int v);

private:
	unsigned int CompileShader(unsigned int Type, const std::string& Source);
	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	void ParseShader(const std::string FilePath, std::string& OutVertexShader, std::string& OutFragmentShader);
	int GetUniformLocation(const std::string& Name);
};