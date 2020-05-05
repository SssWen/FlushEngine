
#pragma once



#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // to make a user-defined type formattable see\ https://fmt.dev/latest/api.html#formatting-user-defined-types


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
#define FLUSH_CORE_ERROR(...)    ::Flush::Log::GetCoreLogger()->error(__VA_ARGS__)
#define Flush_CORE_CRITICAL(...) ::Flush::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FLUSH_TRACE(...)	      ::Flush::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FLUSH_INFO(...)			  ::Flush::Log::GetClientLogger()->info(__VA_ARGS__)
#define FLUSH_WARN(...)			  ::Flush::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FLUSH_ERROR(...)	      ::Flush::Log::GetClientLogger()->error(__VA_ARGS__)
#define FLUSH_CRITICAL(...)       ::Flush::Log::GetClientLogger()->critical(__VA_ARGS__)

// if dist build
// #def ...
