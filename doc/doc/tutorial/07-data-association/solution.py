# tubex-lib - Examples
# Set-membership state estimation by solving data association 
# ----------------------------------------------------------------------------
# Example from the paper "Set-membership state estimation by solving data association"
# Simon Rohou, Benoît Desrochers, Luc Jaulin
# ICRA 2020, Paris

from pyibex import *
from tubex_lib import *
import math
import sys # only for checking if this example still works


class myCtc(Ctc):

  def __init__(self, map_):
    Ctc.__init__(self, 2)
    self.map = map_

  def contract(self, x):
    envelope = IntervalVector(2,Interval.EMPTY_SET)
    for m in self.map:
      envelope |= x & m
    x = envelope
    return x


# =========== CREATING DATA ===========

dt = 0.05 # tube timestep
tdomain = Interval(0,6)

# Truth (analytic function)

x_truth = TrajectoryVector(tdomain, TFunction("( \
  10*cos(t)+t ; \
  5*sin(2*t)+t ; \
  atan2((10*cos(2*t)+1),(-10*sin(t)+1)) ; \
  sqrt((-10*sin(t)+1)^2+(10*cos(2*t)+1)^2))")) # actual trajectory

# Continuous measurements coming from the truth
measured_psi = x_truth[2].sample(dt).make_continuous()
#measured_psi += RandTrajectory(tdomain, dt, Interval(-0.01,0.01)) # adding some noise
measured_speed = x_truth[3].sample(dt);
#measured_speed += RandTrajectory(tdomain, dt, Interval(-0.01,0.01)) # adding some noise

# Sets of trajectories

x_truth[2].sample(dt).make_continuous()

x = TubeVector(tdomain, dt, 4)                    # 4d tube for state vectors
v = TubeVector(tdomain, dt, 4)                    # 4d tube for derivatives of the states
u = TubeVector(tdomain, dt, 2)                    # 2d tube for inputs of the system

x[2] = Tube(measured_psi, dt)#.inflate(0.01)       # measured_psi is a set of measurements
x[3] = Tube(measured_speed, dt)#.inflate(0.01)

# Sets of observations

# Creating random map of landmarks
nb_landmarks = 150
#map_area = IntervalVector(2, [-20,20])
map_area = IntervalVector(x_truth.codomain().subvector(0,1)).inflate(2)
v_map = DataLoader.generate_landmarks_boxes(map_area, nb_landmarks)

# Generating observations obs=(t,range,bearing) of these landmarks
max_nb_obs = 50
visi_range = Interval(0,4) # [0m,75m]
visi_angle = Interval(-math.pi/4,math.pi/4) # frontal sonar
v_obs = DataLoader.generate_observations(x_truth, v_map, max_nb_obs, True, visi_range, visi_angle)

# Adding uncertainties on the measurements
for obs in v_obs:
  obs[1].inflate(0.1) # range
  obs[2].inflate(0.04) # bearing

# Association set
m = [IntervalVector(2) for _ in v_obs] # unknown association


# =========== CUSTOM-BUILT CONTRACTORS ===========

ctc_plus = CtcFunction(Function("a", "b", "c", "a-(b+c)")) # algebraic constraint a=b+c
ctc_minus = CtcFunction(Function("a", "b", "c", "a-(b-c)")) # algebraic constraint a=b-c
ctc_constell = myCtc(v_map) # constellation constraint

ctc_f = CtcFunction(
  Function("v[4]", "x[4]", "u[2]",
           "(v[0]-x[3]*cos(x[2]) ; v[1]-x[3]*sin(x[2]) ; v[2]-u[0] ; v[3]-u[1])"))


# =========== CONTRACTOR NETWORK ===========

cn = ContractorNetwork()

cn.add(ctc_f, [v, x, u])   # adding the f constraint

for i in range(0,len(v_obs)):
  
  # Measurement i
  t  = Interval(v_obs[i][0]) # time
  y1 = Interval(v_obs[i][1]) # range
  y2 = Interval(v_obs[i][2]) # bearing

  # Intermediate variables:
  a = cn.create_dom(Interval())
  d = cn.create_dom(IntervalVector(2))
  p = cn.create_dom(IntervalVector(4))
  
  cn.add(ctc_constell, [m[i]])
  cn.add(ctc_minus, [d, m[i], cn.subvector(p,0,1)])
  cn.add(ctc_plus, [a, p[2], y2])
  cn.add(ctc.polar, [d, y1, a])
  cn.add(ctc.eval, [t, p, x, v])

cn.contract(True)


# =========== GRAPHICS ===========

beginDrawing()

fig_map = VIBesFigMap("Map")
fig_map.set_properties(1450, 50, 1000, 600)
fig_map.add_tube(x, "x", 0, 1)
fig_map.add_trajectory(x_truth, "x*", 0, 1, 2)
fig_map.add_observations(v_obs, x_truth)
for b in v_map:
  fig_map.add_beacon(b.inflate(0.1))
fig_map.smooth_tube_drawing(True)
fig_map.show(1)
#fig_map.axis_limits(-20, 20, -1, 1, True)

endDrawing()

# Checking if this example still works:
sys.exit(0 if x.contains(x_truth) == BoolInterval.YES else 1)