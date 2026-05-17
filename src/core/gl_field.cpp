#include "visc/core/gl_field.hpp"

#include <stdexcept>

namespace visc::core {

GaloisField::GaloisField(size_t q) : q_(q), field_size_(1ULL << q), poly_(0)
{
    if (q_ < 3 || q_ > 8) {
        throw std::invalid_argument("Supported GF(2^q) degrees are 3 to 8");
    }

    uint8_t poly = 0;
    if (q_ == 3)
        poly = 0x0B;  // x^3 + x + 1
    else if (q_ == 4)
        poly = 0x13;  // x^4 + x + 1
    else if (q_ == 5)
        poly = 0x25;  // x^5 + x^2 + 1
    else if (q_ == 6)
        poly = 0x43;  // x^6 + x + 1
    else if (q_ == 7)
        poly = 0x89;  // x^7 + x^3 + 1
    else if (q_ == 8)
        poly = 0x11D;  // x^8 + x^4 + x^3 + x^2 + 1
}

uint8_t GaloisField::mul(uint8_t a, uint8_t b) const
{
    uint8_t res = 0;
    uint8_t temp_a = a;
    uint8_t temp_b = b;

    while (temp_b > 0) {
        if (temp_b & 1) res ^= temp_a;
        if (temp_a & (1 << (q_ - 1))) {
            temp_a = (temp_a << 1) ^ poly_;
        } else {
            temp_a <<= 1;
        }
        temp_b >>= 1;
    }
    return res & (field_size_ - 1);
}

uint8_t GaloisField::pow(uint8_t base, int exp) const
{
    if (exp == 0) return 1;
    if (base == 0) return 0;
    uint8_t res = 1;
    uint8_t tmp = base;
    while (exp > 0) {
        if (exp & 1) res = mul(res, tmp);
        tmp = mul(tmp, tmp);
        exp >>= 1;
    }
    return res;
}

}  // namespace visc::core