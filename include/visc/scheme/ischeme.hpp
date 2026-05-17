#pragma once
#include <cstddef>

#include "visc/core/matrix.hpp"

namespace visc {

class IScheme
{
   public:
    virtual ~IScheme() = default;

    virtual size_t getK() const = 0;
    virtual size_t getN() const = 0;
    virtual size_t getM() const = 0;

    virtual Matrix getWhiteMatrix() const = 0;
    virtual Matrix getBlackMatrix() const = 0;
};

}  // namespace visc