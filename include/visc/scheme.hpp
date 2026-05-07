#pragma once
#include <algorithm>
#include <memory>

#include "matrix.hpp"

namespace visc {
class ColorScheme
{
   public:
    virtual ~ColorScheme() = default;

    virtual size_t getK() const = 0;
    virtual size_t getN() const = 0;
    virtual size_t getM() const = 0;

    virtual size_t getC() const = 0;

    virtual Matrix getMatrixForColor(size_t color_index) const = 0;
};

class TilborgKoutK : public ColorScheme
{
   public:
    TilborgKoutK(size_t k, size_t c);

    size_t getK() const override
    {
        return k_;
    }
    size_t getN() const override
    {
        return k_;
    }
    size_t getM() const override
    {
        return m_;
    }
    size_t getC() const override
    {
        return c_;
    }

    Matrix getMatrixForColor(size_t color_index) const override;

   private:
    size_t k_;
    size_t c_;
    size_t m_;

    std::vector<Matrix> color_matrices_;

    void generateMatrices();
};

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

class GeneralKoutK : public Scheme
{
   public:
    GeneralKoutK(size_t k);

    size_t getK() const override
    {
        return k_;
    }
    size_t getN() const override
    {
        return k_;
    }
    size_t getM() const override
    {
        return m_;
    }

    Matrix getWhiteMatrix() const override;
    Matrix getBlackMatrix() const override;

   private:
    size_t k_;
    size_t m_;
    Matrix m_white_;
    Matrix m_black_;

    void generateMatrices();
};

class GeneralKoutN : public Scheme
{
   public:
    GeneralKoutN(size_t k, size_t n);

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

    Matrix getWhiteMatrix() const override;
    Matrix getBlackMatrix() const override;

   private:
    size_t k_, n_, m_;
    Matrix m_white_, m_black_;
    void generateMatrices();
};
}  // namespace visc