// Granola - Granola - OpenGLContext.h
// Created: 2023.06.10-8:39 PM
// Modified: 2023.06.10-8:39 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Granola
{
	class OpenGLContext final : public GraphicsContext
	{
	public:
		explicit OpenGLContext(GLFWwindow *windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow *m_WindowHandle{};
	};
}
