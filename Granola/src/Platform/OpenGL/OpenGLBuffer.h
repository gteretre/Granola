// Granola - Granola - OpenGLBuffer.h
// Created: 2023.06.14-3:37 PM
// Modified: 2023.06.14-3:37 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Renderer/Buffer.h"

namespace Granola
{
	class OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		explicit OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(const float *vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout &layout) override { m_Layout = layout; }
		[[nodiscard]] virtual const BufferLayout &GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID{};
		BufferLayout m_Layout{};
	};

	class OpenGLIndexBuffer final : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t *indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		[[nodiscard]] virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID{};
		const uint32_t m_Count{};
	};
}
