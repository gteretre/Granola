// Granola - Granola - Shader.h
// Created: 2023.06.11-8:09 PM
// Modified: 2023.06.11-8:09 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include <string>

namespace Granola
{
	class Shader
	{
	public:
		Shader(const std::string &vertexSource, const std::string &fragmentSource);
		~Shader();

		void Bind() const;
		static void Unbind();

	private:
		uint32_t m_RendererID;
	};
}
