/** 
 *  \file codac2_norm.h
 * ----------------------------------------------------------------------------
 *  \date       2025
 *  \author     Quentin Brateau
 *  \copyright  Copyright 2025 Codac Team
 *  \license    GNU Lesser General Public License (LGPL)
 */

#pragma once

#include "codac2_Interval.h"
#include "codac2_AnalyticType.h"
#include "codac2_AnalyticExprWrapper.h"
#include "codac2_sqr.h"
#include "codac2_sqrt.h"

namespace codac2
{
  struct NormOp
  {
    static Interval fwd(const IntervalVector& x);
    static ScalarType fwd_natural(const VectorType& x);
    static ScalarType fwd_centered(const VectorType& x);
    static void bwd(const Interval& y, IntervalVector& x);
  };

  // Analytic operator
  // The following function can be used to build analytic expressions.

  inline ScalarExpr
  norm(const VectorExpr& x)
  {
    return { std::make_shared<AnalyticOperationExpr<NormOp,ScalarType,VectorType>>(x) };
  }
  
  // Inline functions

  inline Interval NormOp::fwd(const IntervalVector& x)
  {
    Interval res = Interval(0, 0);
    for(Index i = 0 ; i < x.size() ; i++)
      res += SqrOp::fwd(x(i));
    return SqrtOp::fwd(res);
  }

  inline ScalarType NormOp::fwd_natural(const VectorType& x)
  {
    return {
      fwd(x.a),
      x.def_domain
    };
  }

  inline ScalarType NormOp::fwd_centered(const VectorType& x)
  {
    return {
      fwd(x.m),
      fwd(x.a),
      IntervalMatrix(0,0), // not supported yet for auto diff
      x.def_domain
    };
  }

  inline void NormOp::bwd(const Interval& y, IntervalVector& x)
  {

    if (x.size() == 2)
    {
      Interval z = SqrOp::fwd(x(0)) + SqrOp::fwd(x(1));
      SqrtOp::bwd(y, z);
      Interval z1 = SqrOp::fwd(x(0));
      Interval z2 = SqrOp::fwd(x(1));
      AddOp::bwd(z, z1, z2);
      SqrOp::bwd(z1, x(0));
      SqrOp::bwd(z2, x(1));
    }
    else
    {
      // For higher dimensions, we need to use a different approach
      // This is a placeholder for a future implementation
    }
  }
}