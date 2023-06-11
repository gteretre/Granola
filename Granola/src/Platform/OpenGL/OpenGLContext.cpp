#include "grlpch.h"
#include "OpenGLContext.h"
#include "Granola/Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Granola
{
	OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle)
	{
		GRL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		GRL_CORE_ASSERT(status, "Failed to initialize Glad!");
		GRL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GRL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GRL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
