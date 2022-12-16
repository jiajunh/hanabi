#pragma once
#ifndef HANABI_LOG_H
#define HANABI_LOG_H

#include "Core/base.h"
#include "pch.h"

namespace Hanabi {
    class Log {
    public:
        static void Init();

        static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        static Ref<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define HANABI_CORE_TRACE(...) ::Hanabi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HANABI_CORE_INFO(...) ::Hanabi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HANABI_CORE_WARN(...) ::Hanabi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HANABI_CORE_ERROR(...) ::Hanabi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HANABI_CORE_CRITICAL(...) ::Hanabi::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HANABI_TRACE(...) ::Hanabi::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HANABI_INFO(...) ::Hanabi::Log::GetClientLogger()->info(__VA_ARGS__)
#define HANABI_WARN(...) ::Hanabi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HANABI_ERROR(...) ::Hanabi::Log::GetClientLogger()->error(__VA_ARGS__)
#define HANABI_CRITICAL(...) ::Hanabi::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif