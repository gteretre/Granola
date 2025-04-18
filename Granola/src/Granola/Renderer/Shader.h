﻿// Granola - Granola - Shader.h
// Created: 2023.06.11-8:09 PM
// Modified: 2023.06.11-8:09 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Granola
{
	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// In the future, we will want to cache uniforms
		/*virtual void SetInt(const std::string &name, int value) = 0;
		virtual void SetIntArray(const std::string &name, int *values, uint32_t count) = 0;
		virtual void SetFloat(const std::string &name, float value) = 0;
		virtual void SetFloat2(const std::string &name, const glm::vec2 &value) = 0;
		virtual void SetFloat3(const std::string &name, const glm::vec3 &value) = 0;
		virtual void SetFloat4(const std::string &name, const glm::vec4 &value) = 0;
		virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;*/

		static Shader *Create(const std::string &vertexSource, const std::string &fragmentSource);
		static Shader *Create(const std::string &filepath);
	};
}
