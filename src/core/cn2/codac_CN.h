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

#ifndef __CODAC_CN_H__
#define __CODAC_CN_H__

//#include "codac_CtcCN.h"
#include <vector>
#include "codac_DomCN.h"
#include "codac_DomCN_Interval.h"

namespace codac
{
  class CN
  {
    public:

      CN();
      void add(/*CtcCN& ctc, */const std::vector<DomCN>& v_domains);

  };
}

#endif