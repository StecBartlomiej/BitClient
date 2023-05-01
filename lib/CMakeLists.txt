

# spdlog lib
set(
        SPDLOG_BUILD_EXAMPLE            OFF
        SPDLOG_BUILD_SHARED             OFF
        SPDLOG_DISABLE_DEFAULT_LOGGER   OFF
        SPDLOG_ENABLE_PCH               ON
)

add_subdirectory(lib/spdlog)
