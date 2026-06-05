#include <codac>
using namespace codac2;

int main()
{
  // Observation Point and Obstacle Segment
  Vector a({1, 1});
  std::vector<Segment> l = {{{1,4}, {2, 3}}, {{2, 3}, {2.5,1}}, {{4, 0.5}, {3.5, -0.5}}};
  Polygon p({{2.5,3}, {2, 2}, {3,1}, {4, 1.5}, {4, 3}});
  
  double epsilon = 0.1;
  IntervalVector X0 ({{-1,6}, {-1,6}});

  // Show the visibility contractor
  Figure2D fig1 ("SepVisible Segments",GraphicOutput::VIBES);
  fig1.set_window_properties({500,50},{500,500});
  fig1.set_axes(axis(0, X0[0]), axis(1, X0[1]));

  fig1.draw_circle(a, 0.05, StyleProperties({Color::dark_green(), Color::green()}, "w:0.025"));
  for (const auto& seg : l) fig1.draw_line(seg[0].mid(), seg[1].mid(), StyleProperties(Color::red(), "w:0.05"));

  fig1.pave(
    X0,
    SepVisible(a, l),
    epsilon
  );

  // Show the non-visibility contractor
  Figure2D fig2 ("SepVisible Polygon",GraphicOutput::VIBES);
  fig2.set_window_properties({50,50},{500,500});
  fig2.set_axes(axis(0, X0[0]), axis(1, X0[1]));

  fig2.draw_circle(a, 0.05, StyleProperties({Color::dark_green(), Color::green()}, "w:0.025"));
  fig2.draw_polygon(p, StyleProperties(Color::red(), "w:0.05"));

  fig2.pave(
    X0,
    SepVisible(a, p),
    epsilon
  );
}