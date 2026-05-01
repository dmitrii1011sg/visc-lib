#include "visc/matrix.hpp"

#include <algorithm>
#include <numeric>
#include <span>
#include <stdexcept>

namespace visc {
Matrix::Matrix(size_t rows, size_t cols, const std::vector<uint8_t>& data)
    : rows_(rows), cols_(cols), data_(data)
{
    if (data.size() != rows * cols) {
        throw std::invalid_argument("Data size does not match matrix dimensions");
    }

    column_indices_.resize(cols_);
    std::iota(column_indices_.begin(), column_indices_.end(), 0);
}

void Matrix::permuteColumns(std::mt19937& rng)
{
    std::shuffle(column_indices_.begin(), column_indices_.end(), rng);
}

std::span<const uint8_t> Matrix::getRowData(size_t row_index) const
{
    return std::span<const uint8_t>(data_.data() + row_index * cols_, cols_);
}

size_t Matrix::getColumnIdx(size_t col_pos) const
{
    return column_indices_[col_pos];
}

std::vector<uint8_t> Matrix::getRow(size_t index) const
{
    if (index >= rows_) throw std::out_of_range("Row index out of bounds");
    auto start = data_.begin() + index * cols_;
    return std::vector<uint8_t>(start, start + cols_);
}
}  // namespace visc