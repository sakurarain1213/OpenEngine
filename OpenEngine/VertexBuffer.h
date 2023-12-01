#pragma once

#include "IBuffer.h"

namespace OpenEngine::Buffer {
	class VertexBuffer : public IBuffer {
	public:
		VertexBuffer() : IBuffer() {
			glGenBuffers(1, &bufferID);
		}
		void Bind() const{
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		}
		void Unbind() const{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		void Upload(const void* src, GLsizeiptr size) const{
			Bind();
			glBufferData(GL_ARRAY_BUFFER, size, src, GL_STATIC_DRAW);
			Unbind();
		}
		~VertexBuffer() {
			glDeleteBuffers(1, &bufferID);
		}
	};
}
