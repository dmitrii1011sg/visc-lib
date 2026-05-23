#ifndef VISC_C_API_H
#define VISC_C_API_H

#include <stdint.h>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#define VISC_API EMSCRIPTEN_KEEPALIVE
#elif defined(_WIN32)
#define VISC_API __declspec(dllexport)
#else
#define VISC_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct visc_encoder_t visc_encoder_t;

VISC_API visc_encoder_t* visc_create_encoder(int k, int n);

VISC_API void visc_encode(visc_encoder_t* encoder, const uint8_t* input, int width, int height,
                          uint8_t** output_shares);

VISC_API void visc_destroy_encoder(visc_encoder_t* encoder);

VISC_API int visc_get_m(visc_encoder_t* handle);
VISC_API int visc_get_n(visc_encoder_t* handle);

VISC_API visc_encoder_t* visc_create_colored_encoder(int k, int n, int num_colors);
VISC_API void visc_encode_color(visc_encoder_t* handle, const uint8_t* input, int width, int height,
                                uint8_t** output_shares);

#ifdef __cplusplus
}
#endif

#endif