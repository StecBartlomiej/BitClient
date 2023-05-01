

# spdlog lib
set(
        SPDLOG_BUILD_EXAMPLE            OFF
        SPDLOG_BUILD_SHARED             OFF
        SPDLOG_DISABLE_DEFAULT_LOGGER   OFF
        SPDLOG_ENABLE_PCH               OFF
)
set(spdlog_DIR lib/spdlog/build)
list(APPEND CMAKE_PREFIX_PATH lib/spdlog)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()