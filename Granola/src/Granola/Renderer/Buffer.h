// Granola - Granola - Buffer.h
// Created: 2023.06.14-2:47 PM
// Modified: 2023.06.14-2:47 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

namespace Granola
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		static VertexBuffer *Create(const float *vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		[[nodiscard]] virtual uint32_t GetCount() const = 0;
		static IndexBuffer *Create(const uint32_t *indices, uint32_t count);
	};
}
