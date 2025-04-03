/** 
 *  \file codac2_scalar.h
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

namespace codac2
{
  struct ScalarOp
  {
    static Interval fwd(const IntervalVector& x1, const IntervalVector& x2);
    static ScalarType fwd_natural(const VectorType& x1, const VectorType& x2);
    static ScalarType fwd_centered(const VectorType& x1, const VectorType& x2);
    static void bwd(const Interval& y, IntervalVector& x1, IntervalVector& x2);
  };

  // Analytic operator
  // The following function can be used to build analytic expressions.

  inline ScalarExpr
  scalar(const VectorExpr& x1, const VectorExpr& x2)
  {
    return { std::make_shared<AnalyticOperationExpr<ScalarOp,ScalarType,VectorType,VectorType>>(x1, x2) };
  }
  
  // Inline functions

  inline Interval ScalarOp::fwd(const IntervalVector& x1, const IntervalVector& x2)
  {
    assert_release(x1.size() == x2.size() && "scalar product only computable for pairs of vectors of same size");
    Interval res = Interval(0, 0);
    for(Index i = 0 ; i < x1.size() ; i++)
      res += x1(i)*x2(i);
    return res;
  }

  inline ScalarType ScalarOp::fwd_natural(const VectorType& x1, const VectorType& x2)
  {
    return {
      fwd(x1.a, x2.a),
      x1.def_domain && x2.def_domain
    };
  }

  inline ScalarType ScalarOp::fwd_centered(const VectorType& x1, const VectorType& x2)
  {
    return {
      fwd(x1.m, x2.m),
      fwd(x1.a, x2.a),
      IntervalMatrix(0,0), // not supported yet for auto diff
      x1.def_domain && x2.def_domain
    };
  }

  inline void ScalarOp::bwd(const Interval& y, IntervalVector& x1, IntervalVector& x2)
  {
    assert_release(x1.size() == x2.size() && "scalar product only computable for pairs of vectors of same size");

    if (x1.size() == 2)
    {
      Interval z1 = x1(0)*x2(0), z2 = x1(1)*x2(1);
      AddOp::bwd(y, z1, z2);
      MulOp::bwd(z1, x1(0), x2(0));
      MulOp::bwd(z2, x1(1), x2(1));
    }
    else
    {
      // For higher dimensions, we need to use a different approach
      // This is a placeholder for a future implementation
    }
  }
}