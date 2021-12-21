/** 
 *  \file
 *  
 * ----------------------------------------------------------------------------
 *  \date       2022
 *  \author     Simon Rohou
 *  \copyright  Copyright 2021 Codac Team
 *  \license    This program is distributed under the terms of
 *              the GNU Lesser General Public License (LGPL).
 */

#ifndef __CODAC_ABSTRACTCTC_H__
#define __CODAC_ABSTRACTCTC_H__

#include <type_traits>
#include <vector>
#include "codac_Interval.h"
#include "codac_IntervalVector.h"
#include "codac_IntervalMatrix.h"
#include "codac_Tube.h"

namespace codac
{
  template<class T, class... Ts>
  struct is_any_base_of : std::disjunction<std::is_base_of<T, Ts>...> {};
  template<class T, class... Ts>
  struct are_base_of : std::conjunction<std::is_base_of<T, Ts>...> {};
  template<class T, class... Ts>
  struct is_any : std::disjunction<std::is_same<T, Ts>...> {};
  template<class T, class... Ts>
  struct are_same : std::conjunction<std::is_same<T, Ts>...> {};

  template<typename... DomainTypes>
  class AbstractCtc
  {
    static_assert(is_any_base_of<DynamicalItem,DomainTypes...>()
      || is_any<Interval,DomainTypes...>() // IBEX types
      || is_any<IntervalVector,DomainTypes...>()
      || is_any<IntervalMatrix,DomainTypes...>(),
      "provided classes names are not valid domain types");

    public:

      AbstractCtc();
      virtual void contract(DomainTypes&... x) = 0;
      virtual bool is_temporal() const;
  };

  class AbstractCtcPolar : public AbstractCtc<IntervalVector>
  {
    public:

      AbstractCtcPolar();
      void contract(IntervalVector& x);

  };

  class AbstractCtcEval : public AbstractCtc<Interval,IntervalVector,TubeVector,TubeVector>
  {
    public:

      AbstractCtcEval();
      //void contract(Tube& x);
      void contract(Interval& x1, IntervalVector& x2, TubeVector& x3, TubeVector& x4);

  };
}

#endif