// Granola - Granola - Texture.h
// Created: 2023.06.20-9:37 PM
// Modified: 2023.06.20-9:37 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Core/Base.h"

namespace Granola
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		[[nodiscard]] virtual uint32_t GetWidth() const = 0;
		[[nodiscard]] virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	// TODO texture factory - create texture based on file extension
	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string &path);
	};
}
