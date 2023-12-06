#pragma once

#include "IBuffer.h"
#include <memory>

namespace OpenEngine::Buffer {
	class UniformBuffer : public IBuffer {
	public:
		UniformBuffer(GLsizeiptr size, GLuint binding_point) : IBuffer() {
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
			glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STREAM_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glBindBufferRange(GL_UNIFORM_BUFFER, binding_point, bufferID, 0, size);
		}
		void Bind() const {
			glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
		}
		void Unbind() const {
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		template<typename T>
		void SetSubData(const T& data, GLsizeiptr offset) {
			Bind();
			glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(T), std::addressof(data));
			Unbind();
		}
		~UniformBuffer() {
			glDeleteBuffers(1, &bufferID);
		}
	};
}
