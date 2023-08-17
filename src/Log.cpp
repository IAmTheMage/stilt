#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;



void Log::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt("Stilt");
    s_CoreLogger->set_level(spdlog::level::trace);

    STILT_INFO("Logger initialized");
}