// Granola - Granola - OpenGLVertexArray.h
// Created: 2023.06.15-5:38 PM
// Modified: 2023.06.15-5:38 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Renderer/Buffer.h"
#include "Granola/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace Granola
{
	static GLenum ShaderDataTypeToOpenGLBaseType(const ShaderDataType type) // TODO temporary here; move to RendererAPI
	{
		switch (type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		case ShaderDataType::None:
			break;
		}

		GRL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	class OpenGLVertexArray final : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

		[[nodiscard]] virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}

		[[nodiscard]] virtual const Ref<IndexBuffer> &GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID{};
		std::vector<Ref<VertexBuffer>> m_VertexBuffers{};
		Ref<IndexBuffer> m_IndexBuffer{};
	};
}
