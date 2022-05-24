/** 
 *  \file
 *  SepCartProd class
 * ----------------------------------------------------------------------------
 *  \date       2022
 *  \author     Quentin Brateau
 *  \copyright  Copyright 2022 Codac Team
 *  \license    This program is distributed under the terms of
 *              the GNU Lesser General Public License (LGPL).
 */

#ifndef __CODAC_SEPCARTPROD_H__
#define __CODAC_SEPCARTPROD_H__

#include "ibex_Sep.h"
#include "ibex_Array.h"
#include "codac_IntervalVector.h"

#include <numeric>
#include <vector>

namespace codac
{
  /**
   * \class SepCartProd
   * \brief Cartesian product of a list of separators
   */
  class SepCartProd : public ibex::Sep
  {
    public:
    
      /**
       * \brief Cartesian product of a list of separators
       *
       * \param args list of separators
       */
      SepCartProd(ibex::Array<ibex::Sep> seps) : Sep(std::accumulate(seps.begin(), seps.end(), 0, [](int &i, const ibex::Sep &s){ return i + s.nb_var;})), m_s(seps) {};

      /**
       * \brief Cartesian product of a list of separators
       *
       * \param args list of separators
       */
      template<typename ...Args>
      SepCartProd(Args &...args) : Sep(dimension_separators(ibex::Array<ibex::Sep>({args...}))), m_s({args...}) {};

      /**
       * \brief \f$\mathcal{S}\big([\mathbf{x}]\big)\f$
       *
       * \param x_in the n-dimensional box \f$[\mathbf{x}]\f$ to be inner-contracted
       * \param x_out the n-dimensional box \f$[\mathbf{x}]\f$ to be outer-contracted
       */
      void separate(IntervalVector& x_in, IntervalVector& x_out);

    protected:
      /**
       * \fn std::size_t dimension_separatos(ibex::Array<ibex::Sep> seps)
       * \brief Compute the dimension of the separators from an ibex::Array of separators
       *
       * \param seps list of separators
       */
      std::size_t dimension_separators(ibex::Array<ibex::Sep> seps);

      ibex::Array<ibex::Sep> m_s; //<! The list of separators
  };

  /**
   * \fn template <typename ...Args> SepCartProd<Args...> cart_prod(Args &...args)
   * \brief Cartesian product of separators
   * 
   * \param args list of separators
   * \return the Cartesian product of the list of separators
   */
  template<typename ...Args>
  SepCartProd cart_prod(Args &...args)
  {
    return SepCartProd(args...);
  }
}

#endif