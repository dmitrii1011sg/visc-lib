#pragma once
#include <memory>
#include <vector>

#include "visc/scheme/ischeme.hpp"

namespace visc {

class YangLaihColored : public IScheme
{
   public:
    YangLaihColored(std::shared_ptr<IScheme> base_scheme, size_t num_colors);

    size_t getK() const override
    {
        return base_scheme_->getK();
    }
    size_t getN() const override
    {
        return base_scheme_->getN();
    }
    size_t getM() const override
    {
        return base_m_ * num_colors_;
    }

    Matrix getWhiteMatrix() const override
    {
        return getColorMatrix(0);
    }
    Matrix getBlackMatrix() const override
    {
        return getColorMatrix(num_colors_);
    }

    Matrix getColorMatrix(size_t color_idx) const;
    size_t getNumColors() const
    {
        return num_colors_;
    }

   private:
    std::shared_ptr<IScheme> base_scheme_;
    size_t num_colors_;
    size_t base_m_;
    std::vector<Matrix> color_matrices_;
};

}  // namespace visc