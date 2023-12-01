#pragma once

#include "RenderDriver.h"

namespace OpenEngine::Buffer {
	class IBuffer {
	public:
		IBuffer() : bufferID(0) {}
		virtual void Bind() const{}
		virtual void Unbind() const{}
		virtual ~IBuffer() {}
	protected:
		GLuint bufferID;
	};
}