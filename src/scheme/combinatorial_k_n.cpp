#include "visc/scheme/combinatorial_k_n.hpp"

#include "visc/scheme/naor_shamir_k_k.hpp"

namespace visc {

CombinatorialKoutN::CombinatorialKoutN(size_t k, size_t n)
    : k_(k), n_(n), m_white_(0, 0, {}), m_black_(0, 0, {})
{
    generateMatrices();
}

void CombinatorialKoutN::generateMatrices()
{
    NaorShamirKoutK base_scheme(k_);
    Matrix base_white = base_scheme.getWhiteMatrix();
    Matrix base_black = base_scheme.getBlackMatrix();
    size_t base_m = base_scheme.getM();

    std::vector<bool> v(n_, false);
    std::fill(v.begin(), v.begin() + k_, true);

    std::vector<std::vector<size_t>> combs;
    do {
        std::vector<size_t> comb;
        for (size_t i = 0; i < n_; ++i) {
            if (v[i]) {
                comb.push_back(i);
            }
        }
        combs.push_back(comb);
    } while (std::prev_permutation(v.begin(), v.end()));

    m_ = combs.size() * base_m;

    std::vector<uint8_t> w_data(n_ * m_, 1);
    std::vector<uint8_t> b_data(n_ * m_, 1);

    size_t col_offset = 0;
    for (const auto& comb : combs) {
        for (size_t i = 0; i < k_; ++i) {
            size_t row = comb[i];
            std::vector<uint8_t> base_w_row = base_white.getRow(i);
            std::vector<uint8_t> base_b_row = base_black.getRow(i);

            for (size_t c = 0; c < base_m; ++c) {
                w_data[row * m_ + col_offset + c] = base_w_row[c];
                b_data[row * m_ + col_offset + c] = base_b_row[c];
            }
        }
        col_offset += base_m;
    }

    m_white_ = Matrix(n_, m_, w_data);
    m_black_ = Matrix(n_, m_, b_data);
}

}  // namespace visc
