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

#ifndef __CODAC_DOMCN_INTERVAL_H__
#define __CODAC_DOMCN_INTERVAL_H__

#include "codac_DomCN.h"
#include "codac_Interval.h"

namespace codac
{
  class DomCN_Interval : virtual public DomCN
  {
    public:

      DomCN_Interval(const Interval& i)
      {

      }

      DomCN_Interval(Interval& i)
      {

      }

  };
}

#endif