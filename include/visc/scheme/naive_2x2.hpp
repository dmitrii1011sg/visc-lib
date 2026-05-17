#pragma once
#include <algorithm>
#include <memory>

#include "visc/core/matrix.hpp"
#include "visc/scheme/ischeme.hpp"

namespace visc {

class Naive2x2 : public IScheme
{
   public:
    Naive2x2();

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

    Matrix getWhiteMatrix() const
    {
        return m_white_;
    };
    Matrix getBlackMatrix() const
    {
        return m_black_;
    };

   private:
    Matrix m_white_, m_black_;
};

}  // namespace visc
