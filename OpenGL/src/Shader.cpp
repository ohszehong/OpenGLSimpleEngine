#include "Shader.h"

#include <iostream>

Shader::Shader(const std::string& filepath)
{
	ShaderProgramSource sourceCode = ParseShader(filepath);
	shaderProgramId = CreateShader(sourceCode.VertexSource, sourceCode.FragmentSource);
	Bind();

	std::cout << sourceCode.VertexSource << "\n" << std::endl;
	std::cout << sourceCode.FragmentSource << std::endl;
}

Shader::~Shader()
{
	std::cout << "Shader deleted!" << std::endl;
	GLCall(glDeleteProgram(shaderProgramId));
}

void Shader::SetUniform4F(int location, float first, float second,  float third, float fourth) const
{
	GLCall(glUniform4f(location, first, second, third, fourth));
}

void Shader::SetUniform4F(const std::string& name, float first, float second, float third, float fourth) 
{
	GLCall(glUniform4f(GetUniformLocation(name), first, second, third, fourth));
}

void Shader::SetUniform1i(const std::string& name, int first)
{
	GLCall(glUniform1i(GetUniformLocation(name), first));
}

void Shader::SetUniform1iv(const std::string& name, int count, int* data)
{
	GLCall(glUniform1iv(GetUniformLocation(name), count, data));
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(shaderProgramId, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform is not used in the shader code..." << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(shaderProgramId));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}
