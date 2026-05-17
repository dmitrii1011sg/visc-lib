#pragma once

#include "encoder.hpp"
#include "visc/core/gl_field.hpp"
#include "visc/core/matrix.hpp"
#include "visc/scheme/combinatorial_k_n.hpp"
#include "visc/scheme/naive_2x2.hpp"
#include "visc/scheme/naor_shamir_k_k.hpp"
#include "visc/scheme/naor_shamir_phf_k_n.hpp"

namespace visc {

inline const char* get_version()
{
    return "0.0.2";
}

}  // namespace visc