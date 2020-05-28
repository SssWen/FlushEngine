#pragma once
#include "flushpch.h"

// 暂时不处理平台问题, 如果使用dll,预编译FLUSH_BUILD_DLL
#ifdef FLUSH_PLATFORM_WINDOW
	#if FLUSH_DYNAMIC_LINK
		#ifdef FLUSH_BUILD_DLL 
			#define FLUSH_API __declspec(dllexport)
		#else
			#define FLUSH_API __declspec(dllimport)
		#endif
	#else
	// 使用staticlib,
		#define FLUSH_API 
	#endif 
#else
	#error Flush only supports Winodow
#endif


#define BIT(x) (1 << x)

#define FLUSH_BIND_EVENT_FN(fn) std::bind(&fn, this,std::placeholders::_1)

#ifdef FLUSH_DEBUG
#define FLUSH_ENABLE_ASSERTS
#endif

// 这里if(!(x))中,x需要带上括号,否则容易出错
#ifdef FLUSH_ENABLE_ASSERTS 
	#define FLUSH_ASSERT(x, ... )  {\
		if(!(x)) {\
			FLUSH_ERROR("Assertion failed: {0}",__VA_ARGS__);\
			__debugbreak();\
		}}
	#define FLUSH_CORE_ASSERT(x, ... )  {\
		if(!(x)) {\
			FLUSH_CORE_ERROR("Assertion failed: {0}",__VA_ARGS__);\
			__debugbreak();\
		}}
	
#else
	#define FLUSH_ASSERT(x, ...)
	#define FLUSH_CORE_ASSERT(x, ...)
#endif

namespace Flush {
#ifndef INSTEAD_RAW_POINT
#define INSTEAD_RAW_POINT
	template<typename T>
	using Scope = std::unique_ptr<T>;
	// [mem leak]
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	// [mem leak]
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	// std::make_shared
#endif
}