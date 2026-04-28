#include "visc/matrix.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace visc {
Matrix::Matrix(size_t rows, size_t cols, const std::vector<uint8_t>& data)
    : rows_(rows), cols_(cols), data_(data)
{
    if (data.size() != rows * cols) {
        throw std::invalid_argument("Data size does not match matrix dimensions");
    }
}

void Matrix::permuteColumns(std::mt19937& rng)
{
    std::vector<size_t> col_indices(cols_);
    std::iota(col_indices.begin(), col_indices.end(), 0);
    std::shuffle(col_indices.begin(), col_indices.end(), rng);

    std::vector<uint8_t> new_data(rows_ * cols_);
    for (size_t r = 0; r < rows_; ++r) {
        for (size_t c = 0; c < cols_; ++c) {
            new_data[r * cols_ + c] = data_[r * cols_ + col_indices[c]];
        }
    }
    data_ = std::move(new_data);
}

std::vector<uint8_t> Matrix::getRow(size_t index) const
{
    if (index >= rows_) throw std::out_of_range("Row index out of bounds");
    auto start = data_.begin() + index * cols_;
    return std::vector<uint8_t>(start, start + cols_);
}
}  // namespace visc