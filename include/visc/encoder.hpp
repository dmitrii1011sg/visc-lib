#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

#include "visc/scheme/ischeme.hpp"
#include "visc/scheme/yang_laih_colored.hpp"

namespace visc {
class Encoder
{
   public:
    Encoder(std::shared_ptr<IScheme> scheme);

    std::vector<std::vector<uint8_t>> encodeBW(const std::vector<uint8_t>& input_pixels, int width,
                                               int height);
    std::vector<std::vector<uint8_t>> encodeColor(const std::vector<uint8_t>& input_indices,
                                                  int width, int height);

   private:
    std::shared_ptr<IScheme> scheme_;
    std::mt19937 rng_;
};
}  // namespace visc