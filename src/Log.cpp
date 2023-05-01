#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace BitTorrent
{
    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        clientLogger_ = spdlog::stdout_color_mt("Console");
        clientLogger_->set_level(spdlog::level::trace);
    }
}