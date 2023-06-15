// Granola - Granola - VertexArray.h
// Created: 2023.06.15-3:42 PM
// Modified: 2023.06.15-3:42 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Buffer.h"

namespace Granola
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
		virtual void AddIndexBuffer(const Ref<IndexBuffer> &indexBuffer) = 0;

		static VertexArray *Create();
	};
}
