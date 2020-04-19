
#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"


namespace Flush {

	class FLUSH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
// __VA_ARGS__ macro 表明你可以使用任何个数的参数
//// Core log macros
#define Flush_CORE_TRACE(...)    ::Flush::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define Flush_CORE_INFO(...)     ::Flush::Log::GetCoreLogger()->info(__VA_ARGS__)
#define Flush_CORE_WARN(...)     ::Flush::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define Flush_CORE_ERROR(...)    ::Flush::Log::GetCoreLogger()->error(__VA_ARGS__)
#define Flush_CORE_FATAL(...)    ::Flush::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define Flush_TRACE(...)	      ::Flush::Log::GetClientLogger()->trace(__VA_ARGS__)
#define Flush_INFO(...)			  ::Flush::Log::GetClientLogger()->info(__VA_ARGS__)
#define Flush_WARN(...)			  ::Flush::Log::GetClientLogger()->warn(__VA_ARGS__)
#define Flush_ERROR(...)	      ::Flush::Log::GetClientLogger()->error(__VA_ARGS__)
#define Flush_FATAL(...)	      ::Flush::Log::GetClientLogger()->fatal(__VA_ARGS__)

// if dist build
// #def ...