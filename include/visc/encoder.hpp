#pragma once
#include <cstdint>
#include <vector>

#include "scheme.hpp"

namespace visc {
class Encoder
{
   public:
    Encoder(std::shared_ptr<Scheme> scheme);

    Encoder(std::shared_ptr<ColorScheme> color_scheme);

    std::vector<std::vector<uint8_t>> encodeBW(const std::vector<uint8_t>& input_pixels, int width,
                                               int height);

    std::vector<std::vector<uint8_t>> encodeColor(const std::vector<uint8_t>& input_indices,
                                                  int width, int height);

   private:
    std::shared_ptr<Scheme> scheme_;
    std::shared_ptr<ColorScheme> color_scheme_;
    std::mt19937 rng_;
};
}  // namespace visc