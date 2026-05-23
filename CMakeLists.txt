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
    src/scheme/yang_laih_colored.cpp
    src/encoder.cpp
    src/c_api.cpp
)

if(EMSCRIPTEN)
    message(STATUS "WebAssembly build (Emscripten)")

    add_executable(visc ${SOURCES})

    target_link_options(visc PRIVATE
        "-sWASM=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sMODULARIZE=1"
        "-sEXPORT_ES6=1"
        "-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap','HEAPU8','HEAP32']"
        "-sEXPORTED_FUNCTIONS=['_malloc','_free','_visc_create_encoder','_visc_destroy_encoder','_visc_get_m','_visc_get_n','_visc_encode','_visc_create_colored_encoder','_visc_encode_color']"
    )

    set_target_properties(visc PROPERTIES SUFFIX ".js")
else()
    message(STATUS "Native build (Shared Library)")

    find_package(OpenMP REQUIRED)
    
    add_library(visc SHARED ${SOURCES})
    
    target_link_libraries(visc PRIVATE OpenMP::OpenMP_CXX)

    set_target_properties(visc PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1
    )
endif()

target_include_directories(visc PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
