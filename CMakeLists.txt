cmake_minimum_required(VERSION 3.10)

project(visc VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/matrix.cpp
    src/scheme.cpp
    src/encoder.cpp
    src/c_api.cpp
)

add_library(visc SHARED ${SOURCES})

target_include_directories(visc PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# set_target_properties(visc PROPERTIES
#     CXX_VISIBILITY_PRESET hidden
#     VISIBILITY_INLINES_HIDDEN 1
# )
