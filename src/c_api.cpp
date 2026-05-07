#include "visc/c_api.h"

#include "visc/core.hpp"

struct visc_encoder_t {
    std::shared_ptr<visc::Scheme> scheme;
    std::unique_ptr<visc::Encoder> encoder;
};

struct visc_color_encoder_t {
    std::shared_ptr<visc::ColorScheme> scheme;
    std::unique_ptr<visc::Encoder> encoder;
};

extern "C" {

// default encoder
visc_encoder_t* visc_create_encoder(int k, int n)
{
    auto handle = new visc_encoder_t();

    if (k == 2 && n == 2) {
        handle->scheme = std::make_shared<visc::Naive2x2>();
    } else if (k == n && k > 2) {
        handle->scheme = std::make_shared<visc::GeneralKoutK>(k);
    } else {
        handle->scheme = std::make_shared<visc::GeneralKoutN>(k, n);
    }

    handle->encoder = std::make_unique<visc::Encoder>(handle->scheme);
    return handle;
}

void visc_encode(visc_encoder_t* handle, const uint8_t* input, int width, int height,
                 uint8_t** output_shares)
{
    std::vector<uint8_t> pixels(input, input + (width * height));

    auto result = handle->encoder->encodeBW(pixels, width, height);

    for (size_t i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), output_shares[i]);
    }
}

void visc_destroy_encoder(visc_encoder_t* handle)
{
    delete handle;
}

int visc_get_m(visc_encoder_t* handle)
{
    return static_cast<int>(handle->scheme->getM());
}

int visc_get_n(visc_encoder_t* handle)
{
    return static_cast<int>(handle->scheme->getN());
}

// color encoder
visc_color_encoder_t* visc_create_color_encoder(int k, int n, int c)
{
    auto handle = new visc_color_encoder_t();
    if (k == n) {
        handle->scheme = std::make_shared<visc::TilborgKoutK>(k, c);
    }

    handle->encoder = std::make_unique<visc::Encoder>(handle->scheme);
    return handle;
}

void visc_encode_color(visc_color_encoder_t* handle, const uint8_t* input_indices, int width,
                       int height, uint8_t** output_shares)
{
    std::vector<uint8_t> pixels(input_indices, input_indices + (width * height));

    auto result = handle->encoder->encodeColor(pixels, width, height);

    for (size_t i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), output_shares[i]);
    }
}

void visc_destroy_color_encoder(visc_color_encoder_t* handle)
{
    delete handle;
}

int visc_color_get_m(visc_color_encoder_t* handle)
{
    return static_cast<int>(handle->scheme->getM());
}

int visc_color_get_n(visc_color_encoder_t* handle)
{
    return static_cast<int>(handle->scheme->getN());
}
}