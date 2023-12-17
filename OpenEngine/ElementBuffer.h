#pragma once

#include "IBuffer.h"

namespace OpenEngine::Buffer {
	class ElementBuffer : public IBuffer {
	public:
		ElementBuffer() : IBuffer() {
			glGenBuffers(1, &bufferID);
		}
		void Bind() const{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
		}
		void Unbind() const{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		void Upload(const void* src, GLsizeiptr size) const {
			Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, src, GL_STATIC_DRAW);
		}
		~ElementBuffer() {
			glDeleteBuffers(1, &bufferID);
		}
	};
}
