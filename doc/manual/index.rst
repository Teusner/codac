Codac manual
============

Welcome to the Codac website.
**This manual is currently under construction.** We are actively working on it and appreciate your patience as we build a comprehensive guide.



Contributors
^^^^^^^^^^^^

This list is in alphabetical order by surname.

.. hlist::
  :columns: 4

  * Auguste Bourgois
  * `Cyril Bouvier <http://www.lirmm.fr/~bouvier/index.en.html>`_
  * `Quentin Brateau <https://teusner.github.io>`_
  * Gilles Chabert
  * `Julien Damers <http://damers.org>`_
  * Benoît Desrochers
  * `Peter Franek <http://www.cs.cas.cz/~franek>`_
  * `Maël Godard <https://godardma.github.io>`_
  * `Nuwan Herath M. <https://members.loria.fr/NHerathMudiyanselage>`_
  * `Luc Jaulin <https://www.ensta-bretagne.fr/jaulin>`_
  * `Fabrice Le Bars <https://www.ensta-bretagne.fr/lebars>`_
  * `Morgan Louédec <https://morgan-louedec.fr>`_
  * Damien Massé
  * `Bertrand Neveu <http://imagine.enpc.fr/~neveub>`_
  * Verlein Radwan
  * `Andreas Rauh <https://www.interval-methods.de>`_
  * `Simon Rohou <http://simon-rohou.fr/research>`_
  * `Joris Tillet <https://perso.ensta-paris.fr/~tillet/>`_
  * `Gilles Trombettoni <https://www.lirmm.fr/~trombetton>`_
  * `Christophe Viel <https://www.ensta-bretagne.fr/viel/>`_
  * `Raphael Voges <https://raphael-voges.de>`_

We appreciate all contributions, whether they are code, documentation, bug reports, or suggestions. If you believe you should be listed here and are not, please contact us to update the list.


Provisional Plan
^^^^^^^^^^^^^^^^

Below is a provisional plan for the structure of this manual.
Some pages are already available.
Please note that some sections may change or be added as we continue to develop the content.

|

Overview of Codac
-----------------

* Intervals and constraints
* The Codac framework
* Target audience

User manual
-----------

* :ref:`sec-install`
   * :ref:`sec-install-py`
   * :ref:`sec-install-cpp`
   * :ref:`sec-install-matlab`

* :ref:`sec-intervals`
   * What is an interval?
   * :ref:`sec-intervals-class`
   * Boolean intervals

* Linear algebra
   * Vector, Matrix
   * IntervalVector, IntervalMatrix
   * Matrix operations and basic linear solving
   * Reliable inversions of matrices
   * C++: efficient matrix operations using Eigen

* :ref:`sec-functions`
   * :ref:`sec-functions-analytic`
      * :ref:`sec-functions-analytic-class`
      * :ref:`sec-functions-analytic-operators`
      * Extension to custom expressions
      * Temporal functions
   * Set-membership functions
      * The class SetMembershipFunction
      * Extension to custom expressions

* Tubes
   * What is a tube?
   * Temporal domains
   * The Tube classes
   * The Trajectory classes
   * Increasing performances using views

* Contractors
   * What are contractors?
   * The Ctc class
   * Basic contractors
      * CtcIdentity
      * CtcEmpty
      * CtcLazy
      * CtcFixpoint
   * Linear contractors
      * CtcGaussElim
      * CtcGaussSeidel
      * CtcLinearPrecond
   * Set contractors
      * CtcUnion
      * CtcInter
      * CtcQInter
      * CtcCartProd
      * CtcProj
      * CtcNot
      * CtcAction
   * Analytic contractors
      * Directed operators
      * CtcInverse
      * CtcInverseNotIn
   * Geometric contractors
      * CtcDist
      * CtcPolar
      * CtcSegment
      * CtcPolygon
      * CtcEllipse
      * :ref:`sec-ctccross`
   * Shape contractors
      * CtcCtcBoundary
      * CtcWrapper
      * CtcImage
      * CtcDiscreteSet
   * Temporal contractors
      * Using static contractors on tubes
      * CtcDeriv
      * CtcEval
      * CtcDelay
      * CtcLinobs
      * CtcLohner
      * CtcPicard
      * CtcChain
      * CtcDiffInclusion

* Separators
   * What are separators?
   * The Sep class
   * Basic separators
      * SepCtcPair
   * Set separators
      * SepUnion
      * SepInter
      * SepQInter
      * SepCartProd
      * SepProj
      * SepNot
      * SepAction
   * Analytic separators
      * SepInverse
      * SepTransform
   * Geometrical separators
      * SepPolarCart or SepCartPolar
      * SepPolygon
      * SepEllipse
      * SepCross
   * Shape separators
      * SepCtcBoundary
      * SepWrapper
      * SepImage
   * Contractors obtained from separators
      * CtcInnerOuter
   * Towards thick separators

* Pavers
   * The SIVIA algorithm
   * Pavers for contractors and separators
   * Paving structures
      * RegularPaving
      * NonRegularPaving

* Contractor Networks
   * What is a CN?
   * The ContractorNetwork class

* Geometry
   * Geometrical tools
   * Polygons and convex polygons
   * Polyhedron

* :ref:`sec-ellipsoids`
   * :ref:`sec-ellipsoids-intro`
   * :ref:`sec-ellipsoids-class`

* Topology
   * Extract connected subsets from pavings
   * Topological degree: verify zeros of an inclusion function

* :ref:`sec-graphics`
   * :ref:`sec-graphics-2d-figures`
   * :ref:`sec-graphics-functions`
   * :ref:`sec-graphics-colors`
   * :ref:`sec-graphics-vibes`
   * :ref:`sec-graphics-ipe`
   * :ref:`sec-graphics-3d`

* :ref:`sec-tools`
   * Serialization tools
   * :ref:`sec-tools-registration`

* Codac extensions
   * CAPD (rigorous numerics in dynamical systems)
   * Interface with the IBEX library
   * Sympy (symbolic computation)

* :ref:`sec-seealso`
   * Frequently Asked Questions
   * :ref:`sec-seealso-performances`
   * Low-level interval library

* References
   * Related papers
   * Contributors
   * How to cite Codac


How-to guides
-------------

* Robotics
   * Non-linear state estimation
   * State estimation by solving data association
   * Range-only SLAM
   * Explored area
   * Loop detections and verifications

* Geometry
   * 2d shape registration

* Dynamical systems
   * Lie symmetries for guaranteed integration
   * Solving a discrete Lyapunov equation
   * Stability analysis of a non-linear system

Development
-----------

* :ref:`sec-dev-info`
* Changelog
* C++ API






.. .. toctree::
..    :hidden:
..    :caption: Overview of Codac
..    :maxdepth: 3
.. 
..    Intervals and constraints
..    The Codac framework
..    Target audience


.. toctree::
   :hidden:
   :caption: User manual
   :maxdepth: 2

   manual/installation/index.rst
   manual/intervals/index.rst
   manual/functions/index.rst
   manual/ellipsoids/index.rst
   manual/visualization/index.rst
   manual/tools/index.rst
   manual/extensions/index.rst
   manual/seealso/index.rst
   
..    linear/index.rst
..    functions/index.rst
..    tubes/index.rst

.. .. toctree::
..    :hidden:
..    :maxdepth: 3
.. 
..    contractors/index.rst
..    separators/index.rst

.. .. toctree::
..    :hidden:
..    :maxdepth: 2
.. 
..    pavers/index.rst
..    cn/index.rst
..    geometry/index.rst
..    topology/index.rst
..    references/index.rst


.. .. toctree::
..    :hidden:
..    :caption: How-to guides
..    :maxdepth: 3
.. 
..    howto/robotics/index.rst
..    howto/geometry/index.rst
..    howto/dynamical/index.rst


.. toctree::
   :hidden:
   :caption: Development
   :maxdepth: 3

   development/info_dev.rst
.. 
..    Changelog
..    C++ API
