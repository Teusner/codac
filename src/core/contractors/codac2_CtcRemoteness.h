/** 
 *  \file codac2_CtcRemoteness.h
 * ----------------------------------------------------------------------------
 *  \date       2025
 *  \author     Quentin Brateau
 *  \copyright  Copyright 2024 Codac Team
 *  \license    GNU Lesser General Public License (LGPL)
 */

 #pragma once

 #include "codac2_Ctc.h"
 #include "codac2_IntervalVector.h"
 
 namespace codac2
 {
   class CtcRemoteness : public Ctc<CtcRemoteness,IntervalVector>
   {
     public:
 
       CtcRemoteness(const IntervalVector& a, const IntervalVector& b, const IntervalVector& u1, const IntervalVector& u2)
         : Ctc<CtcRemoteness,IntervalVector>(2), _a(a), _b(b), _u1(u1), _u2(u2)
       {
         assert_release(a.size() == 2 && b.size() == 2 && "only 2d segments are supported");
       }
 
       void contract(IntervalVector& x) const;
 
     protected:
 
       const IntervalVector _a, _b, _u1, _u2;
   };
 }