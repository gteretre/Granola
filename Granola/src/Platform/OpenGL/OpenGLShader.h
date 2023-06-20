// Granola - Granola - OpenGLShader.h
// Created: 2023.06.20-6:39 PM
// Modified: 2023.06.20-6:39 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Renderer/Shader.h"

namespace Granola
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string &name, const int &values) const;

		void UploadUniformFloat4(const std::string &name, const glm::vec4 &values) const;
		void UploadUniformFloat3(const std::string &name, const glm::vec3 &values) const;
		void UploadUniformFloat2(const std::string &name, const glm::vec2 &values) const;
		void UploadUniformFloat(const std::string &name, const float &values) const;

		void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) const;
		void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) const;

		// In the future, we will want to cache uniforms
		/*
		 * virtual void SetInt(const std::string &name, int value) = 0;
		 * virtual void SetIntArray(const std::string &name, int *values, uint32_t count) = 0;
		 * virtual void SetFloat(const std::string &name, float value) = 0;
		 * virtual void SetFloat2(const std::string &name, const glm::vec2 &value) = 0;
		 * virtual void SetFloat3(const std::string &name, const glm::vec3 &value) = 0;
		 * virtual void SetFloat4(const std::string &name, const glm::vec4 &value) = 0;
		 * virtual void SetMat4(const std::string &name, const glm::mat4 &value) = 0;
		*/


		[[nodiscard]] uint32_t GetRendererID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID;
	};
}
