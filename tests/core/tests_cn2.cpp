#include "catch_interval.hpp"
#include "codac_CN.h"
#include "codac_DomCN_Interval.h"
#include "codac_AbstractCtc.h"
#include "vibes.h"

using namespace Catch;
using namespace Detail;
using namespace std;
using namespace codac;

#define VIBES_DRAWING 0

TEST_CASE("CN simple")
{
  SECTION("Most simple case")
  {
    //CN cn;
    //Interval intv;
    //DomCN_Interval dom(intv);
    //cn.add({ intv });

    //AbstractCtc<Interval> ctc_test;
    AbstractCtcPolar ctc_test_polar;
    cout << "CtcPolar " << ctc_test_polar.is_temporal() << endl;
    AbstractCtcEval ctc_test_eval;
    cout << "CtcEval " << ctc_test_eval.is_temporal() << endl;

  }
}