#include "visc/scheme/naor_shamir_k_k.hpp"

namespace visc {

inline int popcount(unsigned int n)
{
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

NaorShamirKoutK::NaorShamirKoutK(size_t k)
    : k_(k), m_(1 << (k - 1)), m_white_(0, 0, {}), m_black_(0, 0, {})
{
    generateMatrices();
}

void NaorShamirKoutK::generateMatrices()
{
    std::vector<uint8_t> w_data(k_ * m_, 0);
    std::vector<uint8_t> b_data(k_ * m_, 0);

    size_t col_even = 0;
    size_t col_odd = 0;

    for (unsigned int val = 0; val < (1u << k_); ++val) {
        bool is_even = (popcount(val) % 2 == 0);

        for (size_t row = 0; row < k_; ++row) {
            uint8_t bit = (val & (1u << row)) ? 1 : 0;

            if (is_even) {
                w_data[row * m_ + col_even] = bit;
            } else {
                b_data[row * m_ + col_odd] = bit;
            }
        }

        if (is_even)
            col_even++;
        else
            col_odd++;
    }

    m_white_ = Matrix(k_, m_, w_data);
    m_black_ = Matrix(k_, m_, b_data);
}

}  // namespace visc
