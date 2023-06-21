// Granola - Granola - OpenGLTexture.h
// Created: 2023.06.20-9:44 PM
// Modified: 2023.06.20-9:44 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Renderer/Texture.h"

#include <glad/glad.h>

namespace Granola
{
	class OpenGLTexture2D final : public Texture2D
	{
	public:
		explicit OpenGLTexture2D(const std::string &path);
		virtual ~OpenGLTexture2D() override;

		[[nodiscard]] virtual uint32_t GetWidth() const override { return m_Width; }
		[[nodiscard]] virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}
