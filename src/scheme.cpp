#include "visc/scheme.hpp"

namespace visc {
Matrix Naive2x2::getWhiteMatrix() const
{
    std::vector<uint8_t> data = {1, 0, 1, 0, 1, 0, 1, 0};
    return Matrix(2, 4, data);
}

Matrix Naive2x2::getBlackMatrix() const
{
    std::vector<uint8_t> data = {1, 0, 1, 0, 0, 1, 0, 1};
    return Matrix(2, 4, data);
}
}  // namespace visc