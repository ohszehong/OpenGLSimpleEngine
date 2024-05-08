#pragma once

#include <Windows.h>
#include <commdlg.h>

#include "Test.h"
#include "Texture.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


namespace TestCase
{
	class TestTexture : Test
	{
	private:
		std::vector<Texture> textures;
		GLFWwindow* window;
		Shader* shaderProgram;
		Renderer* renderer;
		VertexArray* VAO;
		VertexBuffer* vb;
		IndexBuffer* ib;
		VertexBufferLayout* layout;
		std::string strToCurrentDirectory;

	public:
		TestTexture(GLFWwindow* window, Shader* shaderProgram, Renderer* renderer, VertexArray* VAO, VertexBuffer* vb, IndexBuffer* ib, VertexBufferLayout* layout);
		~TestTexture();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;

		void AddTexture(const std::string& path);

		inline std::vector<Texture>& GetTextures()
		{
			return textures;
		}
	};
}