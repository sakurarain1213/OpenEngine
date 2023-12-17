#pragma once

#include "IBuffer.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

namespace OpenEngine::Buffer{
	class VertexArray : public IBuffer {
	public:
		VertexArray() :
			IBuffer() {
			glGenVertexArrays(1, &bufferID);
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
	};
}
