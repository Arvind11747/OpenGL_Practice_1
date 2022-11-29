#include "TestClearColor.h"

#include "GL/glew.h"
#include "imgui/imgui.h"

#include "GLErrorHandle.h" 


namespace Tests
{
	TestClearColor::TestClearColor() :
		m_ClearColor {0.2f, 0.5f, 0.5f, 1.0f}
	{

	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}


	void TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender(std::string windowName)
	{
		ImGui::Begin((windowName.c_str()));
		ImGui::ColorEdit4("BG Color", m_ClearColor);
		ImGui::End();
	}
}

