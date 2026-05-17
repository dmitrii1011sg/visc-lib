cmake_minimum_required(VERSION 3.10)

project(visc VERSION 0.0.2 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/core/matrix.cpp
    src/core/gl_field.cpp
    src/scheme/combinatorial_k_n.cpp
    src/scheme/ischeme.cpp
    src/scheme/naive_2x2.cpp
    src/scheme/naor_shamir_k_k.cpp
    src/scheme/naor_shamir_phf_k_n.cpp
    src/scheme/verheul_tilborg_k_n.cpp
    src/encoder.cpp
    src/c_api.cpp
)

find_package(OpenMP REQUIRED)

add_library(visc SHARED ${SOURCES})

target_link_libraries(visc PRIVATE OpenMP::OpenMP_CXX)

target_include_directories(visc PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(visc PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
)
