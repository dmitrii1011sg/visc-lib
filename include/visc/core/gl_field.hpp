#pragma once
#include <cstddef>
#include <cstdint>

namespace visc::core {

class GaloisField
{
   public:
    explicit GaloisField(size_t q);

    uint8_t add(uint8_t a, uint8_t b) const
    {
        return a ^ b;
    }
    uint8_t mul(uint8_t a, uint8_t b) const;
    uint8_t pow(uint8_t base, int exp) const;

    size_t getSize() const
    {
        return field_size_;
    }
    size_t getQ() const
    {
        return q_;
    }

   private:
    size_t q_;
    size_t field_size_;
    uint8_t poly_;
};

}  // namespace visc::core