#pragma once

#include "IBuffer.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

namespace OpenEngine::Buffer{
	class VertexArray : public IBuffer {
	public:
		VertexArray(const VertexBuffer& vertexBuffer, const ElementBuffer& elementBuffer) :
			m_vertexBuffer(vertexBuffer),
			m_elementBuffer(elementBuffer),
			IBuffer() {
			glGenVertexArrays(1, &bufferID);
			Bind();
			m_vertexBuffer.Bind();
			m_elementBuffer.Bind();
			Unbind();
		}
		void Bind() const{
			glBindVertexArray(bufferID);
		}
		void Unbind() const{
			glBindVertexArray(0);
		}
		void BindAttribute(GLuint index, GLint size, GLsizei strode, GLsizeiptr offset) {
			glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, strode, (void*)offset);
		}
		~VertexArray() {
			glDeleteVertexArrays(1, &bufferID);
		}
	private:
		const VertexBuffer& m_vertexBuffer;
		const ElementBuffer& m_elementBuffer;
	};
}
