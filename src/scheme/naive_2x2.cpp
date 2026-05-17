#include "visc/scheme/naive_2x2.hpp"

namespace visc {

Naive2x2::Naive2x2()
    : m_white_(2, 4, std::vector<uint8_t>{1, 0, 1, 0, 1, 0, 1, 0}),
      m_black_(2, 4, std::vector<uint8_t>{1, 0, 1, 0, 0, 1, 0, 1})
{
}

}  // namespace visc
