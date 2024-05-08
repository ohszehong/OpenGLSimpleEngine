#pragma once

//STL
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

//internal 
#include "DebugUtilities.h"

//vendor 
#include "glm/glm.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int shaderProgramId; 

    //some caching 
    std::unordered_map<std::string, int> m_UniformLocationCache;

    static ShaderProgramSource ParseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath);

        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        //std::stringstream ss[2];
        std::string ss[2];

        ShaderType type = ShaderType::NONE;

        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                if (type == ShaderType::NONE)
                    continue;

                //ss[(int)type] << line << "\n";
                ss[(int)type].append(line + "\n");
            }
        }

        return { ss[0], ss[1] };
    }

    static unsigned int CompileShader(unsigned int type, const std::string& source)
    {
        GLCall(unsigned int id = glCreateShader(type));
        const char* src = source.c_str();
        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        //Query if anything is wrong from the compilation 
        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (!result)
        {
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)_malloca(length * sizeof(char));

            GLCall(glGetShaderInfoLog(id, length, &length, message));

            std::cout << "Failed to compile shader!\n" << "Type of shader: " << (type == GL_VERTEX_SHADER ? "Vertex shader" : "Fragment shader");
            std::cout << message << std::endl;

            GLCall(glDeleteShader(id));

            ASSERT(false);
            return 0;
        }

        return id;
    }

    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLCall(unsigned int program = glCreateProgram());

        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        GLCall(glAttachShader(program, vs));
        GLCall(glAttachShader(program, fs));
        GLCall(glLinkProgram(program));
        GLCall(glValidateProgram(program));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return program;
    }

public:
	Shader(const std::string& filepath);
	~Shader();

    inline unsigned int GetShaderProgram() const
    {
        return shaderProgramId;
    }

    void SetUniform4F(int location, float first, float second, float third,  float fourth) const;

    void SetUniform4F(const std::string& name, float first, float second, float third, float fourth);

    void SetUniform1i(const std::string& name, int first);

    void SetUniform1iv(const std::string& name, int count, int* data);

    void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

    int GetUniformLocation(const std::string& name);

    void Bind() const;
    void UnBind() const;
};

struct Material
{
    Shader* shader;

    Material() : shader(nullptr) {}
    Material(Shader* shader) : shader(shader) {}
    virtual void ApplyMaterial() = 0;

    void Bind() const
    {
        shader->Bind();
    }

    void UnBind() const
    {
        shader->UnBind();
    }
};

struct Color : Material
{
    float color[4];

    Color(Shader* shader) : Material(shader), color{0,0,0,0} {}

    void Supply(float r, float g, float b, float a)
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        color[3] = a;
    }

    void ApplyMaterial() override
    {
        shader->SetUniform4F(shader->GetUniformLocation("u_Color"), color[0], color[1], color[2], color[3]);
    }
};