#include "visc/encoder.hpp"

namespace visc {
Encoder::Encoder(std::shared_ptr<Scheme> scheme) : scheme_(scheme)
{
    std::random_device rd;
    rng_ = std::mt19937(rd());
}

std::vector<std::vector<uint8_t>> Encoder::encodeBW(const std::vector<uint8_t>& input_pixels,
                                                    int width, int height)
{
    size_t n = scheme_->getN();
    size_t m = scheme_->getM();

    int scale = static_cast<int>(std::sqrt(m));
    int new_width = width * scale;
    int new_height = height * scale;

    // std::vector<std::vector<uint8_t>> shares(n);
    // for (auto& share : shares) {
    //     share.reserve(input_pixels.size() * m);
    // }

    std::vector<std::vector<uint8_t>> shares(n, std::vector<uint8_t>(new_width * new_height));

    Matrix m_white = scheme_->getWhiteMatrix();
    Matrix m_black = scheme_->getBlackMatrix();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint8_t pixel = input_pixels[y * width + x];
            bool is_white = (pixel > 128);

            Matrix current_matrix = is_white ? m_white : m_black;
            current_matrix.permuteColumns(rng_);

            for (size_t i = 0; i < n; ++i) {
                std::vector<uint8_t> row = current_matrix.getRow(i);

                // Раскладываем строку субпикселей (row) в блок scale x scale
                for (int sub_idx = 0; sub_idx < m; ++sub_idx) {
                    int dx = sub_idx % scale;
                    int dy = sub_idx / scale;

                    // Вычисляем финальный индекс в плоском массиве доли
                    size_t out_idx = (y * scale + dy) * new_width + (x * scale + dx);

                    shares[i][out_idx] = (row[sub_idx] == 1 ? 0 : 255);
                }
            }
        }
    }

    // for (uint8_t pixel : input_pixels) {
    //     bool is_white = (pixel > 128);

    //     Matrix current_matrix = is_white ? m_white : m_black;

    //     current_matrix.permuteColumns(rng_);

    //     for (size_t i = 0; i < n; ++i) {
    //         std::vector<uint8_t> row = current_matrix.getRow(i);
    //         for (uint8_t val : row) {
    //             shares[i].push_back(val == 1 ? 0 : 255);
    //         }
    //     }
    // }

    return shares;
}
}  // namespace visc