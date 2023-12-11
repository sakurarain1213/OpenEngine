#pragma once

#include "RenderDriver.h"

namespace OpenEngine {

	enum TestFunc {
		OE_TEST_ALWAYS = GL_ALWAYS,
		OE_TEST_NEVER = GL_NEVER,
		OE_TEST_LESS = GL_LESS,
		OE_TEST_EQUAL = GL_EQUAL,
		OE_TEST_LEQUAL = GL_LEQUAL,
		OE_TEST_GREATER = GL_GREATER,
		OE_TEST_NOTEQUAL = GL_NOTEQUAL,
		OE_TEST_GEQUAL = GL_GEQUAL,
	};

	enum TestOperation {
		OE_TEST_KEEP = GL_KEEP,
		OE_TEST_ZERO = GL_ZERO,
		OE_TEST_REPLACE = GL_REPLACE,
		OE_TEST_INCR = GL_INCR,
		OE_TEST_INCR_WRAP = GL_INCR_WRAP,
		OE_TEST_DECR = GL_DECR,
		OE_TEST_DECR_WRAP = GL_DECR_WRAP,
		OE_TEST_INVERT = GL_INVERT
	};

	enum BlendFunc {
		OE_BLEND_ZERO = GL_ZERO,
		OE_BLEND_ONE = GL_ONE,
		OE_BLEND_SRC_COLOR = GL_SRC_COLOR,
		OE_BLEND_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
		OE_BLEND_DST_COLOR = GL_DST_COLOR,
		OE_BLEND_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
		OE_BLEND_SRC_ALPHA = GL_SRC_ALPHA,
		OE_BLEND_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		OE_BLEND_DST_ALPHA = GL_DST_ALPHA,
		OE_BLEND_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
		OE_BLEND_CONSTANT_COLOR = GL_CONSTANT_COLOR,
		OE_BLEND_ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
		OE_BLEND_CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
		OE_BLEND_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA
	};

	enum UniformBindingPoint {
		OE_UNIFORM_GLOBALUBO = 0
	};
}