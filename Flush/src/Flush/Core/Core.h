#pragma once
#include "flushpch.h"

// ��ʱ������ƽ̨����, ���ʹ��dll,Ԥ����FLUSH_BUILD_DLL
#ifdef FLUSH_PLATFORM_WINDOW
	#if FLUSH_DYNAMIC_LINK
		#ifdef FLUSH_BUILD_DLL 
			#define FLUSH_API __declspec(dllexport)
		#else
			#define FLUSH_API __declspec(dllimport)
		#endif
	#else
	// ʹ��staticlib,
		#define FLUSH_API 
	#endif 
#else
	#error Flush only supports Winodow
#endif
// HZ_PLATFORM_WINDOW

#define BIT(x) (1 << x)

#define FLUSH_BIND_EVENT_FN(fn) std::bind(&fn, this,std::placeholders::_1)

#ifdef FLUSH_DEBUG
#define FLUSH_ENABLE_ASSERTS
#endif

// ����if(!(x))��,x��Ҫ��������,�������׳���
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
#ifndef SCOPE_REF
#define SCOPE_REF
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
#endif
}