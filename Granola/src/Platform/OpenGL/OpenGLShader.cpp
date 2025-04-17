#include "grlpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Granola
{
	static GLenum ShaderTypeFromString(const std::string &type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		GRL_CORE_ASSERT(false, "Unknown Shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string &filepath)
	{
		const std::string source = ReadFile(filepath);
		const auto shaderSources = PreProcess(source);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string &vertexSource, const std::string &fragmentSource)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string &filepath)
	{
		std::string result{};
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (!in)
		{
			GRL_CORE_ERROR("Could not open file '{0}'", filepath);
			return "";
		}
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(result.data(), static_cast<long long>(result.size()));
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const auto typeToken = "#type";
		const size_t typeTokenLength = strlen(typeToken);
		size_t position = source.find(typeToken, 0);
		while (position != std::string::npos)
		{
			const size_t endOfLine = source.find_first_of("\r\n", position);
			GRL_CORE_ASSERT(endOfLine != std::string::npos, "Syntax error");
			const size_t begin = position + typeTokenLength + 1;
			const std::string type = source.substr(begin, endOfLine - begin);
			GRL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			const size_t nextLinePos = source.find_first_not_of("\r\n", endOfLine);
			GRL_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			position = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = (position == std::string::npos)
															? source.substr(nextLinePos)
															: source.substr(nextLinePos, position - nextLinePos);
		}

		return shaderSources;
	}


	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string &name, const int &values) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, values);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string &name, const int *values, const uint32_t count) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, static_cast<int>(count), values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string &name, const float &values) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, values);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &values) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &values) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &values) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) const
	{
		const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(matrix));
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources)
	{
		const GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSources.size());
		for (const auto &[fst, snd] : shaderSources)
		{
			const GLenum type = fst;
			const std::string &source = snd;

			//const GLuint shader = glCreateShader(GL_VERTEX_SHADER);
			const GLuint shader = glCreateShader(type);

			const GLchar *sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, nullptr);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

				glDeleteShader(shader);
				GRL_CORE_ERROR("{0}", infoLog.data());
				GRL_ASSERT(false, "Shader compilation failed!")
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

		glLinkProgram(program);
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (const auto id : glShaderIDs)
				glDeleteShader(id);

			GRL_CORE_ERROR("{0}", infoLog.data());
			GRL_ASSERT(false, "Shader link failed!")
			return;
		}

		for (const auto id : glShaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}
}
