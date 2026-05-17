#include "visc/scheme/naor_shamir_phf_k_n.hpp"

#include "visc/scheme/naor_shamir_k_k.hpp"

namespace visc {

NaorShamirPHFKoutN::NaorShamirPHFKoutN(size_t k, size_t n)
    : k_(k), n_(n), m_white_(0, 0, {}), m_black_(0, 0, {})
{
    if (k_ < 2 || n_ < k_) {
        throw std::invalid_argument("Invalid k or n parameters");
    }
    generateMatrices();
}

std::vector<std::vector<size_t>> NaorShamirPHFKoutN::getCombinations(size_t n, size_t k) const
{
    std::vector<std::vector<size_t>> combs;
    std::vector<bool> v(n, false);
    std::fill(v.begin(), v.begin() + k, true);

    do {
        std::vector<size_t> comb;
        for (size_t i = 0; i < n; ++i) {
            if (v[i]) comb.push_back(i);
        }
        combs.push_back(comb);
    } while (std::prev_permutation(v.begin(), v.end()));

    return combs;
}

std::vector<std::vector<size_t>> NaorShamirPHFKoutN::generatePHF() const
{
    auto unseparated_combs = getCombinations(n_, k_);
    std::vector<std::vector<size_t>> phf;

    std::mt19937 gen(42);
    std::uniform_int_distribution<size_t> dist(0, k_ - 1);

    while (!unseparated_combs.empty()) {
        std::vector<size_t> h(n_);
        for (size_t i = 0; i < n_; ++i) {
            h[i] = dist(gen);
        }

        std::vector<std::vector<size_t>> remaining_combs;
        bool useful_function = false;

        for (const auto& comb : unseparated_combs) {
            std::vector<bool> seen(k_, false);
            bool separated = true;

            for (size_t participant : comb) {
                if (seen[h[participant]]) {
                    separated = false;
                    break;
                }
                seen[h[participant]] = true;
            }

            if (separated) {
                useful_function = true;
            } else {
                remaining_combs.push_back(comb);
            }
        }

        if (useful_function) {
            phf.push_back(h);
            unseparated_combs = remaining_combs;
        }
    }

    return phf;
}

void NaorShamirPHFKoutN::generateMatrices()
{
    std::vector<std::vector<size_t>> phf = generatePHF();

    NaorShamirKoutK base_scheme(k_);
    Matrix base_w = base_scheme.getWhiteMatrix();
    Matrix base_b = base_scheme.getBlackMatrix();
    size_t base_m = base_scheme.getM();

    m_ = phf.size() * base_m;
    std::vector<uint8_t> w_data(n_ * m_, 0);
    std::vector<uint8_t> b_data(n_ * m_, 0);

    size_t col_offset = 0;
    for (const auto& h : phf) {
        for (size_t participant = 0; participant < n_; ++participant) {
            size_t mapped_row = h[participant];
            std::vector<uint8_t> base_w_row = base_w.getRow(mapped_row);
            std::vector<uint8_t> base_b_row = base_b.getRow(mapped_row);

            for (size_t c = 0; c < base_m; ++c) {
                w_data[participant * m_ + col_offset + c] = base_w_row[c];
                b_data[participant * m_ + col_offset + c] = base_b_row[c];
            }
        }
        col_offset += base_m;
    }

    m_white_ = Matrix(n_, m_, w_data);
    m_black_ = Matrix(n_, m_, b_data);
}

}  // namespace visc
