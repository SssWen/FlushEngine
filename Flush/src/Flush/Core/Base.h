#pragma once

#include <memory>

namespace Flush {

	void InitializeCore();
	void ShutdownCore();

}


#include "Assert.h"

// Pointer wrappers
namespace Flush {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	using byte = unsigned char;

}