#include "visc/encoder.hpp"

#include <chrono>
#include <iostream>

namespace visc {
Encoder::Encoder(std::shared_ptr<Scheme> scheme) : scheme_(scheme)
{
    std::random_device rd;
    rng_ = std::mt19937(rd());
}

std::vector<std::vector<uint8_t>> Encoder::encodeBW(const std::vector<uint8_t>& input_pixels,
                                                    int width, int height)
{
    auto start = std::chrono::high_resolution_clock::now();
    size_t n = scheme_->getN();
    size_t m = scheme_->getM();

    int scale_w = static_cast<int>(std::sqrt(m));
    while (m % scale_w != 0 && scale_w > 1) {
        scale_w--;
    }
    int scale_h = m / scale_w;

    int new_width = width * scale_w;
    int new_height = height * scale_h;

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

                for (int sub_idx = 0; sub_idx < m; ++sub_idx) {
                    int dx = sub_idx % scale_w;
                    int dy = sub_idx / scale_w;

                    size_t out_idx = (y * scale_h + dy) * new_width + (x * scale_w + dx);
                    shares[i][out_idx] = (row[sub_idx] == 1 ? 0 : 255);
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "visc: encoding time: " << diff.count() << " s" << std::endl;

    return shares;
}
}  // namespace visc