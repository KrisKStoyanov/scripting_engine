#pragma once
#include <memory>
#include "../../Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Cyberspace {
	class CSPACE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Engine logging macros
#define CSPACE_CORE_TRACE(...) ::Cyberspace::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CSPACE_CORE_INFO(...) ::Cyberspace::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CSPACE_CORE_WARN(...) ::Cyberspace::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CSPACE_CORE_ERROR(...) ::Cyberspace::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CSPACE_CORE_FATAL(...) ::Cyberspace::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Game logging macros
#define CSPACE_CLIENT_TRACE(...) ::Cyberspace::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CSPACE_CLIENT_INFO(...) ::Cyberspace::Log::GetClientLogger()->info(__VA_ARGS__)
#define CSPACE_CLIENT_WARN(...) ::Cyberspace::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CSPACE_CLIENT_ERROR(...) ::Cyberspace::Log::GetClientLogger()->error(__VA_ARGS__)
#define CSPACE_CLIENT_FATAL(...) ::Cyberspace::Log::GetClientLogger()->fatal(__VA_ARGS__)


