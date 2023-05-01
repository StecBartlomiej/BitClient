#ifndef BITCLIENT_LOG_HPP
#define BITCLIENT_LOG_HPP

#include "spdlog/spdlog.h"

#include <memory>

#define LOG_TRACE(args...) ::BitTorrent::Log::GetClient()->trace(args)
#define LOG_INFO(args...) ::BitTorrent::Log::GetClient()->info(args)
#define LOG_WARN(args...) ::BitTorrent::Log::GetClient()->warn(args)
#define LOG_ERROR(args...) ::BitTorrent::Log::GetClient()->error(args)
#define LOG_CRITICAL(args...) ::BitTorrent::Log::GetClient()->critical(args)

namespace BitTorrent
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetClient() { return clientLogger_; }
    private:
        inline static std::shared_ptr<spdlog::logger> clientLogger_{};
    };

}

#endif //BITCLIENT_LOG_HPP
