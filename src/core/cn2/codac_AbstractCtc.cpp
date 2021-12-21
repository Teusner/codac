/** 
 *  
 * ----------------------------------------------------------------------------
 *  \date       2022
 *  \author     Simon Rohou
 *  \copyright  Copyright 2021 Codac Team
 *  \license    This program is distributed under the terms of
 *              the GNU Lesser General Public License (LGPL).
 */

#include "codac_DynamicalItem.h"
#include "codac_AbstractCtc.h"

using namespace std;

namespace codac
{
  template<typename... DomainType>
  AbstractCtc<DomainType...>::AbstractCtc()
  {

  }

  template<typename... DomainType>
  bool AbstractCtc<DomainType...>::is_temporal() const
  {
    if constexpr(is_any_base_of<DynamicalItem,DomainType...>())
      return true;
    return false;
  }

  AbstractCtcPolar::AbstractCtcPolar()
  {

  }

  void AbstractCtcPolar::contract(IntervalVector& x)
  {

  }

  AbstractCtcEval::AbstractCtcEval()
  {

  }

  void AbstractCtcEval::contract(Interval& x1, IntervalVector& x2, TubeVector& x3, TubeVector& x4)
  {

  }
}