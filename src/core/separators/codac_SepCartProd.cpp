/** 
 *  SepCartProd class
 * ----------------------------------------------------------------------------
 *  \date       2022
 *  \author     Quentin Brateau
 *  \copyright  Copyright 2022 Codac Team
 *  \license    This program is distributed under the terms of
 *              the GNU Lesser General Public License (LGPL).
 */

#include "ibex_Sep.h"
#include "ibex_Array.h"
#include "codac_Interval.h"
#include "codac_IntervalVector.h"
#include "codac_SepCartProd.h"

#include <vector>

namespace codac
{
  std::size_t SepCartProd::dimension_separators(ibex::Array<ibex::Sep> seps) {
    int n = 0;
    for (int k=0; k<seps.size(); ++k) {
      n += seps[k].nb_var;
    }
    return n;
  }

  void SepCartProd::separate(IntervalVector& x_in, IntervalVector& x_out)
  {
    assert(x_in.size() == nb_var);
    assert(x_out.size() == nb_var);

    // Splitting x_in and c_out into subvectors
    std::vector<IntervalVector> a_x_in(0);
    std::vector<IntervalVector> a_x_out(0);
    int index = 0;
    for (ibex::Sep &s: m_s) {
      IntervalVector iv_in(s.nb_var);
      IntervalVector iv_out(s.nb_var);
      for (int k=0; k<s.nb_var; ++k) {
        iv_in[k] = x_in[index];
        iv_out[k] = x_out[index];
        ++index;
      }
      a_x_in.push_back(iv_in);
      a_x_out.push_back(iv_out);
    }

    // Separating subboxes x_in and x_out
    for (int k=0; k<m_s.size(); ++k) {
      IntervalVector sx_in(a_x_in[k]);
      IntervalVector sx_out(a_x_out[k]);
      m_s[k].separate(sx_in, sx_out);
      a_x_in[k] &= sx_in;
      a_x_out[k] &= sx_out;
    }

    // Merging subboxes in x_in
    index = 0;
    IntervalVector intermediate_x_in(IntervalVector::empty(x_in.size()));
    for (int k=0; k<m_s.size(); ++k) {
      IntervalVector sx(x_in);
      for (Interval &i: a_x_in[k]) {
        sx[index] &= i;
        ++index;
      }
      if (!sx.is_flat()) {
        intermediate_x_in |= sx;
      }
    }

    x_in &= intermediate_x_in;

    // Merging subboxes in x_out
    index = 0;
    for (int k=0; k<m_s.size(); ++k) {
      for (Interval &i: a_x_out[k]) {
        x_out[index] &= i;
        ++index;
      }
    }
  }
}