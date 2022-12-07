include(FetchContent)

FetchContent_Declare(
        geogram
        GIT_REPOSITORY https://github.com/BrunoLevy/geogram.git
        GIT_TAG v1.8.2
)
FetchContent_MakeAvailable(geogram)

include_directories(${geogram_SOURCE_DIR}/src/lib/)

