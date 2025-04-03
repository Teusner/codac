.. _sec-ellipsoids-class:

CtcCross & CtcNoCross
=====================

The :cpp:class:`CtcCross` and :cpp:class:`CtcNoCross` classes are contracting sets relative to the cross constraint between an obstacle segment and a sensor measurement segment.

Consider a robot is placed inside a mapped room, and equipped with a time-of-flight distance sensor. The set of compatible positions for the robot can be contracted using the measurement and the fact that there is no obstacles crossing the measurement segment.