#include "TestWrapper.h"

TestWrapper::TestWrapper(GLFWwindow* window, std::string shaderFilePath, std::string title) : m_RunTest(SelectedTest::NONE), context(ImGui::CreateContext()), shaderProgram(shaderFilePath), vb(nullptr, NULL), ib(nullptr, NULL), m_TextureTest(window, &shaderProgram, &renderer, &VAO, &vb, &ib, &layout), m_ProjectionTest(&shaderProgram), m_DrawQuadTest(&shaderProgram, &renderer, &vb, &ib, &layout, &m_TextureTest, &m_ProjectionTest, 8), m_Title(title)
{
    //Setting vertex attributes and layout
    //positions
    layout.PushVertexAttribute<float>(0, 2);

    //color 
    layout.PushVertexAttribute<float>(1, 4);

    //texture coordinates
    layout.PushVertexAttribute<float>(2, 2);

    //texture sampler index 
    layout.PushVertexAttribute<float>(3, 1);

    //model matrix position
    layout.PushVertexAttribute<float>(4, 2);

    //set attribute pointers
    VAO.AddBufferWithLayout(vb, layout);

    //set new size for vertex buffer 
    GLCall(glBufferData(GL_ARRAY_BUFFER, (8 * 4 * layout.getStride()), nullptr, GL_DYNAMIC_DRAW));

    ib.SetCount(48);

    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (ib.GetCount() * sizeof(unsigned int)), defaultIndices, GL_DYNAMIC_DRAW));

    //ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImFontConfig config;
    config.SizePixels = 20;
    io.Fonts->AddFontDefault(&config);

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init("#version 130");
}

TestWrapper::~TestWrapper()
{
    std::cout << "Test terminated!" << std::endl;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void TestWrapper::AddButton(const char* label)
{
   m_Buttons.emplace_back(label);
}

void TestWrapper::Render()
{
    //Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin(m_Title.c_str());

    float margin = (context->Style.WindowPadding.x) * 2.0f;
    float w = ImGui::GetWindowWidth() - margin;
    float h = 40.0f;

    const ImVec2 spc = ImVec2(7.0f, 16.0f);

    ImGuiIO& io = ImGui::GetIO();

    switch (m_RunTest)
    {
    case SelectedTest::TEST_CLEAR_COLOR:
        runningTest[0] = true;
        m_ClearColorTest.onRender();
        m_ClearColorTest.onImGuiRender();
        if (ImGui::Button("BACK", ImVec2(w, h)))
        {
            m_RunTest = SelectedTest::NONE;
            m_ClearColorTest.Reset();
        }
        break;

    case SelectedTest::TEST_DRAW_QUAD:
        runningTest[1] = true;
        m_DrawQuadTest.onRender();
        m_DrawQuadTest.onImGuiRender();
        if (ImGui::Button("Generate Quad", ImVec2(w, h)))
        {
            m_DrawQuadTest.generateQuad();
        }
        ImGui::Spacing();
        if (ImGui::Button("BACK", ImVec2(w, h)))
        {
            m_RunTest = SelectedTest::NONE;
            //m_ClearColorTest.Reset();
        }
        ImGui::Spacing();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        break;

    case SelectedTest::TEST_TEXTURE:
        runningTest[2] = true;
        if (runningTest[1]) m_DrawQuadTest.onRender();
        m_TextureTest.onImGuiRender();
        if (ImGui::Button("BACK", ImVec2(w, h)))
        {
            m_RunTest = SelectedTest::NONE;
        }
        break;

    case SelectedTest::TEST_PROJECTION:
        runningTest[3] = true;
        if (runningTest[1]) m_DrawQuadTest.onRender();
        m_ProjectionTest.onImGuiRender();
        if (ImGui::Button("BACK", ImVec2(w, h)))
        {
            m_RunTest = SelectedTest::NONE;
        }
        break;

    default:
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, spc);
        int counter = 1;
        for (std::string ButtonLabel : m_Buttons)
        {
            if (ImGui::Button(ButtonLabel.c_str(), ImVec2(w,h)))
            {
                m_RunTest = static_cast<SelectedTest>(counter);
                break;
            }
            counter++;
        }
        ImGui::PopStyleVar(1);

        if (ImGui::Checkbox("Enable Texture", &enableTexture))
        {
            shaderProgram.SetUniform1i("u_EnableTexture", enableTexture ? 1 : 0);
        }
        ImGui::Spacing();
     
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Spacing();

        if (runningTest[0])
        {
            m_ClearColorTest.onRender();
            m_ClearColorTest.onImGuiRender();
        }
        if (runningTest[1])
        {
            m_DrawQuadTest.onRender();
            m_DrawQuadTest.onImGuiRender();
        }
    }

    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void TestWrapper::Clear()
{
    renderer.Clear();
}
