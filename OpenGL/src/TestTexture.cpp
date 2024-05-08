#include "TestTexture.h"

TestCase::TestTexture::TestTexture(GLFWwindow* window, Shader* shaderProgram, Renderer* renderer, VertexArray* VAO, VertexBuffer* vb, IndexBuffer* ib, VertexBufferLayout* layout) : window(window), shaderProgram(shaderProgram), renderer(renderer), VAO(VAO), vb(vb), ib(ib), layout(layout)
{
	textures.reserve(10);
	int samplers[10] = { 0,1,2,3,4,5,6,7,8,9 };
	shaderProgram->SetUniform1iv("u_Texture", 10, samplers);

	TCHAR path[MAX_PATH + 1] = L"";
	GetCurrentDirectory(MAX_PATH, path);
	std::wstring currentDirectory = path;
	char* szTo = new char[currentDirectory.length() + 1];

	//add terminate 0 at the very end 
	szTo[currentDirectory.size()] = '\0';

	WideCharToMultiByte(CP_UTF8, 0, &currentDirectory[0], -1, szTo, (int)currentDirectory.length(), NULL, NULL);

	strToCurrentDirectory = szTo;
	delete[] szTo;
}

TestCase::TestTexture::~TestTexture()
{
}

void TestCase::TestTexture::onUpdate(float deltaTime)
{
}

void TestCase::TestTexture::onRender()
{
}

void TestCase::TestTexture::onImGuiRender()
{
	float w = ImGui::GetWindowWidth() - 10.0f;
	float h = 40.0f;
	if (ImGui::Button("Upload Texture", ImVec2(w,h)))
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		
		//set all the byte in the memory to 0 
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window(window);
		ofn.lpstrInitialDir = &strToCurrentDirectory[0];
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "Default (*.jpg, *.png)\0*.jpg;*png\0JPG File (*.jpg)\0*.jpg\0PNG File (*.png)\0*.png\0";
		ofn.nFilterIndex = 1; 
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			std::cout << "File path: " << ofn.lpstrFile << std::endl;
			AddTexture(ofn.lpstrFile);
		}
	}
	ImGui::Spacing();

	for (int i = 0; i < textures.size(); i++)
	{
		std::string label = "Texture " + std::to_string(i);
		ImGui::Text(label.c_str());
		ImGui::Spacing();
		ImGui::Image((void*)(intptr_t)textures[i].GetTextureId(), ImVec2(400, 400), ImVec2(0,1), ImVec2(1,0));
	}

}

void TestCase::TestTexture::AddTexture(const std::string& path)
{
	if (textures.size() >= 10)
	{
		std::cout << "Maximum number of textures achieved!" << std::endl;
		return;
	}

	textures.emplace_back(path, textures.size());
}
