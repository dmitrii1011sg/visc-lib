#include "visc/scheme.hpp"

namespace visc {
TilborgKoutK::TilborgKoutK(size_t k, size_t c) : k_(k), c_(c)
{
    if (k < 2) throw std::invalid_argument("k must be >= 2");
    if (c < 2) throw std::invalid_argument("c must be >= 2");

    m_ = 1;
    for (size_t i = 0; i < k_ - 1; ++i) {
        m_ *= c_;
    }

    generateMatrices();
}

void TilborgKoutK::generateMatrices()
{
    color_matrices_.clear();
    color_matrices_.reserve(c_);

    for (size_t current_color = 0; current_color < c_; ++current_color) {
        std::vector<uint8_t> data(k_ * m_, 0);

        for (size_t col = 0; col < m_; ++col) {
            size_t temp = col;
            long long column_sum = 0;

            for (size_t row = 0; row < k_ - 1; ++row) {
                uint8_t val = temp % c_;
                data[row * m_ + col] = val;

                column_sum += val;
                temp /= c_;
            }

            long long last_val =
                ((current_color - column_sum) % static_cast<long long>(c_) + c_) % c_;

            data[(k_ - 1) * m_ + col] = static_cast<uint8_t>(last_val);
        }

        color_matrices_.emplace_back(k_, m_, data);
    }
}

Matrix TilborgKoutK::getMatrixForColor(size_t color_index) const
{
    if (color_index >= c_) {
        throw std::out_of_range("Color index out of bounds");
    }
    return color_matrices_[color_index];
}

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

inline int popcount(unsigned int n)
{
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

GeneralKoutK::GeneralKoutK(size_t k)
    : k_(k), m_(1 << (k - 1)), m_white_(0, 0, {}), m_black_(0, 0, {})
{
    generateMatrices();
}

void GeneralKoutK::generateMatrices()
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

Matrix GeneralKoutK::getWhiteMatrix() const
{
    return m_white_;
}
Matrix GeneralKoutK::getBlackMatrix() const
{
    return m_black_;
}

GeneralKoutN::GeneralKoutN(size_t k, size_t n)
    : k_(k), n_(n), m_white_(0, 0, {}), m_black_(0, 0, {})
{
    generateMatrices();
}

void GeneralKoutN::generateMatrices()
{
    GeneralKoutK base_scheme(k_);
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

Matrix GeneralKoutN::getWhiteMatrix() const
{
    return m_white_;
}

Matrix GeneralKoutN::getBlackMatrix() const
{
    return m_black_;
}
}  // namespace visc