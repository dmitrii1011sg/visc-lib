#pragma once
#include <algorithm>
#include <memory>

#include "visc/core/matrix.hpp"
#include "visc/scheme/ischeme.hpp"

namespace visc {

class CombinatorialKoutN : public IScheme
{
   public:
    CombinatorialKoutN(size_t k, size_t n);

    size_t getK() const override
    {
        return k_;
    }
    size_t getN() const override
    {
        return n_;
    }
    size_t getM() const override
    {
        return m_;
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
    size_t k_, n_, m_;
    Matrix m_white_, m_black_;

    void generateMatrices();
};

}  // namespace visc