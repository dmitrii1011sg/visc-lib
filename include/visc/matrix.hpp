#pragma once
#include <cstdint>
#include <random>
#include <span>
#include <vector>

namespace visc {
class Matrix
{
   public:
    Matrix(size_t rows, size_t cols, const std::vector<uint8_t>& data);

    void permuteColumns(std::mt19937& rng);

    std::vector<uint8_t> getRow(size_t index) const;

    std::span<const uint8_t> getRowData(size_t row_index) const;

    size_t getColumnIdx(size_t col_pos) const;

    size_t getRows() const
    {
        return rows_;
    }
    size_t getCols() const
    {
        return cols_;
    }

   private:
    size_t rows_;
    size_t cols_;
    std::vector<uint8_t> data_;
    std::vector<size_t> column_indices_;
};
}  // namespace visc