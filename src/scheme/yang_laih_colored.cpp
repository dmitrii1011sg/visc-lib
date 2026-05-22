#include "visc/scheme/yang_laih_colored.hpp"

#include <stdexcept>

namespace visc {

YangLaihColored::YangLaihColored(std::shared_ptr<IScheme> base, size_t num_colors)
    : base_scheme_(base), num_colors_(num_colors), base_m_(base->getM())
{
    Matrix b0 = base->getWhiteMatrix();
    Matrix b1 = base->getBlackMatrix();
    size_t n = getN();
    size_t m_total = getM();
    uint8_t black_val = static_cast<uint8_t>(num_colors);

    for (size_t i = 0; i < num_colors; ++i) {
        std::vector<uint8_t> data(n * m_total);

        for (size_t slot = 0; slot < num_colors; ++slot) {
            const Matrix& base_mat = (slot == i) ? b0 : b1;
            uint8_t slot_color = static_cast<uint8_t>(slot);

            for (size_t row = 0; row < n; ++row) {
                auto row_vec = base_mat.getRow(row);
                for (size_t col = 0; col < base_m_; ++col) {
                    uint8_t bit = row_vec[col];
                    uint8_t val = (bit == 0) ? slot_color : black_val;
                    data[row * m_total + slot * base_m_ + col] = val;
                }
            }
        }
        color_matrices_.emplace_back(n, m_total, data);
    }
}

Matrix YangLaihColored::getColorMatrix(size_t color_idx) const
{
    if (color_idx >= num_colors_) throw std::out_of_range("Color index out of bounds");
    return color_matrices_[color_idx];
}

}  // namespace visc