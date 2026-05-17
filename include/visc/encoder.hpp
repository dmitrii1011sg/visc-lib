#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>
// #include "scheme.hpp"
#include "visc/scheme/ischeme.hpp"

namespace visc {
class Encoder
{
   public:
    Encoder(std::shared_ptr<IScheme> scheme);

    std::vector<std::vector<uint8_t>> encodeBW(const std::vector<uint8_t>& input_pixels, int width,
                                               int height);

   private:
    std::shared_ptr<IScheme> scheme_;
    std::mt19937 rng_;
};
}  // namespace visc