#include "grlpch.h"
#include "OpenGLVertexArray.h"


namespace Granola
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		GRL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		uint32_t index = 0;
		const auto &layout = vertexBuffer->GetLayout();
		for (const auto &element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
								  static_cast<GLint>(element.GetComponentCount()),
								  ShaderDataTypeToOpenGLBaseType(element.Type),
								  element.Normalized ? GL_TRUE : GL_FALSE,
								  static_cast<GLsizei>(layout.GetStride()),
								  reinterpret_cast<const void*>(element.Offset));
			++index;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}
