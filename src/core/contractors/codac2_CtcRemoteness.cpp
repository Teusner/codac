/** 
 *  codac2_CtcRemoteness.cpp
 * ----------------------------------------------------------------------------
 *  \date       2025
 *  \author     Quentin Brateau
 *  \copyright  Copyright 2025 Codac Team
 *  \license    GNU Lesser General Public License (LGPL)
 */

#include "codac2_CtcRemoteness.h"
#include "codac2_det.h"
#include "codac2_div.h"
#include "codac2_abs.h"
#include "codac2_sub.h"
#include "codac2_norm.h"


using namespace std;
using namespace codac2;


// Contractor for the distance between the box [x] and the line (a, b) in 2D
void contractor_distance_line(Interval &y, IntervalVector& x, const IntervalVector& a, const IntervalVector& b)
{
  // forward
  IntervalVector ab = b - a;
  IntervalVector ax = x - a;
  Interval n = norm(ab);
  Interval d = det(ab, ax);
  y &= (d / n);

  // backward
  DivOp::bwd(y, d, n);
  DetOp::bwd(d, ab, ax);
  SubOp::bwd(ax, x, a);
}

// Contractor for the directional distance along u between the box [x] and the line (a, b) in 2D
void contractor_directional_distance_line(Interval &y, IntervalVector& x, IntervalVector &u, const IntervalVector& a, const IntervalVector& b)
{
  // forward
  IntervalVector ab = b - a;
  IntervalVector ax = x - a;
  Interval d1 = det(ab, ax);
  Interval d2 = det(ab, u);
  IntervalVector ad1 = abs(d1);
  IntervalVector ad2 = abs(d2);
  y &= (ad1 / ad2);

  // backward
  DivOp::bwd(y, ad1, ad2);
  AbsOp::bwd(ad1, d1);
  AbsOp::bwd(ad2, d2);
  DetOp::bwd(d1, ab, ax);
  DetOp::bwd(d2, ab, u);
  SubOp::bwd(ax, x, a);
}

// Contractor for the chi constraint: if a < 0 then r = b else r = c
void contractor_chi(Interval &r, Interval &a, Interval &b, Interval &c)
{
  // forward
  if (a.ub() < 0) {
    r &= b;
    b &= r;
  } else if (a.lb() > 0) {
    r &= c;
    c &= r;
  }

  // backward
  if (r.is_disjoint(b)) {
    a &= Interval(0, oo);
  }
  if (r.is_disjoint(c)) {
    a &= Interval(-oo, 0);
  }
  r = (r & b) | (r & c);
}


void CtcRemoteness::contract(IntervalVector& x) const
{
  // [x] = <x, y, ux1, uy1, ux2, uy2, r, ax, ay, bx, by>

  // Getting inputs
  IntervalVector m({x[0], x[1]});
  Interval x = in[0];
  Interval y = in[1];
  IntervalVector u1({x[2], x[3]});
  IntervalVector u2({x[4], x[5]});
  Interval r = in[6];
  IntervalVector a({x[7], x[8]});
  IntervalVector b({x[9], x[10]});

  // Forward evaluation
  // 1
  IntervalVector ab = b - a;
  IntervalVector ma = a - m;
  IntervalVector mb = b - m;
  Interval z1 = DetOp::fwd(ab, ma);
  contractor_chi(r, z1, r, Interval(oo));

  // 2
  Interval z2, z3, z4, z5;
  ScalarOp::fwd(z2, ab, ma);
  ScalarOp::fwd(z3, ab, mb);
  ScalarOp::fwd(z4, u1, ab);
  ScalarOp::fwd(z5, u2, ab);

  // 3
  Interval rh(0, oo), lh;
  contractor_distance_line(lh, m, a, b);
  contractor_chi(rh, z2, lh, Interval(oo));
  contractor_chi(rh, z3, Interval(oo), rh);
  contractor_chi(rh, z4, rh, Interval(oo));
  contractor_chi(rh, z5, Interval(oo), rh);

  // 4
  Interval z6, z7;
  DetOp::fwd(z6, u1, ma);
  DetOp::fwd(z7, u2, ma);

  // 5
  Interval ra(0, oo), nax(0, oo);
  NormOp::fwd(nax, ma);
  contractor_chi(ra, z6, nax, Interval(oo));
  contractor_chi(ra, z7, ra, Interval(oo));

  // 6
  Interval z8, z9;
  DetOp::fwd(z8, u1, mb);
  DetOp::fwd(z9, u2, mb);

  // 7
  Interval rb(0, oo), nbx(0, oo);
  NormOp::fwd(nbx, mb);
  contractor_chi(rb, z8, Interval(oo), nbx);
  contractor_chi(rb, z9, Interval(oo), rb);

  // 8/9/10
  Interval rh1(0, oo), rh2(0, oo);
  contractor_directional_distance_line(rh1, m, u1, a, b);
  contractor_directional_distance_line(rh2, m, u2, a, b);

  // 11
  Interval r1 = min(rh, ra);
  Interval r2 = min(r1, rb);
  Interval r3 = min(r2, rh1);
  Interval r4 = min(r3, rh2);
  contractor_chi(r, z1, r4, Interval(oo));

  // Backward evaluation
  // 11
  MinOp::bwd(r4, r3, rh2);
  MinOp::bwd(r3, r2, rh1);
  MinOp::bwd(r2, r1, rb);
  MinOp::bwd(r1, rh, ra);
  
  // 8/9/10
  // CdistanceDirSegment(rh1, m, u1, a, b, -1);
  // CdistanceDirSegment(rh2, m, u2, a, b, -1);

  // 7
  contractor_chi(rb, z9, Interval(oo), rb);
  contractor_chi(rb, z8, Interval(oo), nbx);
  NormOp::bwd(nbx, mb);

  // 6
  DetOp::bwd(z9, u2, mb);
  DetOp::bwd(z8, u1, mb);

  // 5
  contractor_chi(ra, z7, ra, Interval(oo));
  contractor_chi(ra, z6, nax, Interval(oo));
  NormOp::bwd(nax, ma);

  // 4
  DetOp::bwd(z7, u2, ma);
  DetOp::bwd(z6, u1, ma);

  // 3
  contractor_chi(rh, z5, Interval(oo), rh);
  contractor_chi(rh, z4, rh, Interval(oo));
  contractor_chi(rh, z3, Interval(oo), rh);
  contractor_chi(rh, z2, lh, Interval(oo));
  contractor_distance_line(lh, m, a, b);

  // 2
  ScalarOp::bwd(z5, u2, ab);
  ScalarOp::bwd(z4, u1, ab);
  ScalarOp::bwd(z3, ab, mb);
  ScalarOp::bwd(z2, ab, ma);

  // 1
  contractor_chi(r, z1, r, Interval(oo));
  DetOp::bwd(z1, ab, ma);
  SubOp::bwd(mb, b, m);
  SubOp::bwd(ma, a, m);
}