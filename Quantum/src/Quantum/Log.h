#pragma once
#include"Core.h"
#include<memory>
#include<spdlog/spdlog.h>
#include<spdlog/logger.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include<spdlog/fmt/ostr.h>
namespace Quantum {
	class QUANTUM_API Log
	{
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() {
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() {
			return s_ClientLogger;
		}
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

//-----------------core logger macros------------------------
#define QT_CORE_TRACE(...)	 ::Quantum::Log::getCoreLogger()->trace(__VA_ARGS__)
#define QT_CORE_INFO(...)	 ::Quantum::Log::getCoreLogger()->info(__VA_ARGS__)
#define QT_CORE_WARN(...)	 ::Quantum::Log::getCoreLogger()->warn(__VA_ARGS__)
#define QT_CORE_ERROR(...)	 ::Quantum::Log::getCoreLogger()->error(__VA_ARGS__)
#define QT_CORE_FATAL(...)	 ::Quantum::Log::getCoreLogger()->fatal(__VA_ARGS__)
//-----------------core logger macros for objects------------

//-----------------client logger macros------------------------
#define QT_CLIENT_TRACE(...) ::Quantum::Log::getClientLogger()->trace(__VA_ARGS__)
#define QT_CLIENT_INFO(...)	 ::Quantum::Log::getClientLogger()->info(__VA_ARGS__)
#define QT_CLIENT_WARN(...)  ::Quantum::Log::getClientLogger()->warn(__VA_ARGS__)
#define QT_CLIENT_ERROR(...) ::Quantum::Log::getClientLogger()->error(__VA_ARGS__)
#define QT_CLIENT_FATAL(...) ::Quantum::Log::getClientLogger()->fatal(__VA_ARGS__)
//