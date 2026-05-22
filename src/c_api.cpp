#include "visc/c_api.h"

#include "visc/core.hpp"

struct visc_encoder_t {
    std::shared_ptr<visc::IScheme> scheme;
    std::unique_ptr<visc::Encoder> encoder;
};

extern "C" {
visc_encoder_t* visc_create_encoder(int k, int n)
{
    auto handle = new visc_encoder_t();

    if (k == 2 && n == 2) {
        handle->scheme = std::make_shared<visc::Naive2x2>();
    } else if (k == n && k > 2) {
        handle->scheme = std::make_shared<visc::NaorShamirKoutK>(k);
    } else {
        handle->scheme = std::make_shared<visc::NaorShamirPHFKoutN>(k, n);
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

visc_encoder_t* visc_create_colored_encoder(int k, int n, int num_colors)
{
    auto handle = new visc_encoder_t();
    std::shared_ptr<visc::IScheme> base;

    if (k == 2 && n == 2)
        base = std::make_shared<visc::Naive2x2>();
    else if (k == n)
        base = std::make_shared<visc::NaorShamirKoutK>(k);
    else
        base = std::make_shared<visc::NaorShamirPHFKoutN>(k, n);

    handle->scheme = std::make_shared<visc::YangLaihColored>(base, num_colors);
    handle->encoder = std::make_unique<visc::Encoder>(handle->scheme);
    return handle;
}

void visc_encode_color(visc_encoder_t* handle, const uint8_t* input, int width, int height,
                       uint8_t** output_shares)
{
    std::vector<uint8_t> pixels(input, input + (width * height));
    auto result = handle->encoder->encodeColor(pixels, width, height);

    for (size_t i = 0; i < result.size(); ++i) {
        std::copy(result[i].begin(), result[i].end(), output_shares[i]);
    }
}
}