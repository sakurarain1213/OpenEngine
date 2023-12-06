#pragma once

#include "RenderDriver.h"
#include <any>

namespace OpenEngine {
	enum UniformType
	{
		OE_UNIFROM_BOOL = GL_BOOL,
		OE_UNIFORM_INT = GL_INT,
		OE_UNIFORM_FLOAT = GL_FLOAT,
		OE_UNIFORM_VEC2 = GL_FLOAT_VEC2,
		OE_UNIFORM_VEC3 = GL_FLOAT_VEC3,
		OE_UNIFORM_VEC4 = GL_FLOAT_VEC4,
		OE_UNIFORM_MAT4 = GL_FLOAT_MAT4,
		OE_UNIFORM_SAMPLER2D = GL_SAMPLER_2D
	};

	struct Uniform {
		std::string name;
		UniformType type;
		std::any value;
	};
}