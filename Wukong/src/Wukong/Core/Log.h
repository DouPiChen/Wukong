#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Wukong 
{
	class Log
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

#define WU_CORE_TRACE(...)	::Wukong::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define WU_CORE_INFO(...)	::Wukong::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WU_CORE_WARN(...)	::Wukong::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define WU_CORE_ERROR(...)	::Wukong::Log::GetCoreLogger()->error(__VA_ARGS__)
#define WU_CORE_FATAL(...)	::Wukong::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define WU_TRACE(...)	::Wukong::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WU_INFO(...)	::Wukong::Log::GetClientLogger()->info(__VA_ARGS__)
#define WU_WARN(...)	::Wukong::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WU_ERROR(...)	::Wukong::Log::GetClientLogger()->error(__VA_ARGS__)
#define WU_FATAL(...)	::Wukong::Log::GetClientLogger()->fatal(__VA_ARGS__)