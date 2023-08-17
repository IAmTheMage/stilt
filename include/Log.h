#include "spdlog/spdlog.h"
#include "memory"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifndef LOG_H
#define LOG_H
class Log {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
            return s_CoreLogger;
        }
    

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
};


#define STILT_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define STILT_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define STILT_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define STILT_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define STILT_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)
#endif