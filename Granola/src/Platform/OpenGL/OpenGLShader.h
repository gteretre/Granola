// Granola - Granola - OpenGLShader.h
// Created: 2023.06.20-6:39 PM
// Modified: 2023.06.20-6:39 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include <glm/glm.hpp>
#include "Granola/Renderer/Shader.h"

using GLenum = unsigned int; // TODO: Remove, forced to put here because dynamic cast in SandboxApp.cpp
namespace Granola
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource);
		explicit OpenGLShader(const std::string &filepath);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string &name, const int &values) const;
		void UploadUniformIntArray(const std::string &name, const int *values, uint32_t count) const;

		void UploadUniformFloat4(const std::string &name, const glm::vec4 &values) const;
		void UploadUniformFloat3(const std::string &name, const glm::vec3 &values) const;
		void UploadUniformFloat2(const std::string &name, const glm::vec2 &values) const;
		void UploadUniformFloat(const std::string &name, const float &values) const;

		void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) const;
		void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) const;

		[[nodiscard]] uint32_t GetRendererID() const { return m_RendererID; }

	private:
		[[nodiscard]] static std::string ReadFile(const std::string &filepath);
		[[nodiscard]] static std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
		void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);

		uint32_t m_RendererID;
		std::unordered_map<GLenum, std::string> m_ShaderSources;
	};
}
