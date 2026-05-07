#ifndef VISC_C_API_H
#define VISC_C_API_H

#include <stdint.h>

#if defined(_WIN32)
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

typedef struct visc_color_encoder_t visc_color_encoder_t;

VISC_API visc_color_encoder_t* visc_create_color_encoder(int k, int n, int c);

VISC_API void visc_encode_color(visc_color_encoder_t* encoder, const uint8_t* input_indices,
                                int width, int height, uint8_t** output_shares);

VISC_API void visc_destroy_color_encoder(visc_color_encoder_t* encoder);

VISC_API int visc_color_get_m(visc_color_encoder_t* handle);
VISC_API int visc_color_get_n(visc_color_encoder_t* handle);

#ifdef __cplusplus
}
#endif

#endif