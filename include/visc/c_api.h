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

visc_encoder_t* visc_create_encoder(int k, int n);

void visc_encode(visc_encoder_t* encoder, const uint8_t* input, int width, int height,
                 uint8_t** output_shares);

void visc_destroy_encoder(visc_encoder_t* encoder);

VISC_API int visc_get_m(visc_encoder_t* handle);
VISC_API int visc_get_n(visc_encoder_t* handle);

#ifdef __cplusplus
}
#endif

#endif