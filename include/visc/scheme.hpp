#pragma once
#include <memory>

#include "matrix.hpp"

namespace visc {
class Scheme
{
   public:
    virtual ~Scheme() = default;
    virtual size_t getK() const = 0;
    virtual size_t getN() const = 0;
    virtual size_t getM() const = 0;

    virtual Matrix getWhiteMatrix() const = 0;
    virtual Matrix getBlackMatrix() const = 0;
};

class Naive2x2 : public Scheme
{
   public:
    size_t getK() const override
    {
        return 2;
    }
    size_t getN() const override
    {
        return 2;
    }
    size_t getM() const override
    {
        return 4;
    }

    Matrix getWhiteMatrix() const override;
    Matrix getBlackMatrix() const override;
};
}  // namespace visc