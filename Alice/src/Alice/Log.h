#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace Alice {
	class ALICE_API Log
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

// Core log macros
#define ALICE_CORE_TRACE(...)	::Alice::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define ALICE_CORE_INFO(...)	::Alice::Log::GetCoreLogger()->info(__VA_ARGS__);
#define ALICE_CORE_WARN(...)	::Alice::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define ALICE_CORE_ERROR(...)	::Alice::Log::GetCoreLogger()->error(__VA_ARGS__);
#define ALICE_CORE_FATAL(...)	::Alice::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// Client log macros
#define ALICE_TRACE(...)		::Alice::Log::GetClientLogger()->trace(__VA_ARGS__);
#define ALICE_INFO(...)			::Alice::Log::GetClientLogger()->info(__VA_ARGS__);
#define ALICE_WARN(...)			::Alice::Log::GetClientLogger()->warn(__VA_ARGS__);
#define ALICE_ERROR(...)		::Alice::Log::GetClientLogger()->error(__VA_ARGS__);
#define ALICE_FATAL(...)		::Alice::Log::GetClientLogger()->fatal(__VA_ARGS__);