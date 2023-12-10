#pragma once

#include "ServiceLocator.h"

namespace OpenEngine {
	std::unordered_map<size_t, std::any> ServiceLocator::__SERVICE_LOCATOR_MAP;
}