
project(rask-core)

option(BUILD_SHARED_LIBS "build as shared library" ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(${PROJECT_NAME}
    raskcore.h
)