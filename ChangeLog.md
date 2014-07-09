# DGtal 0.8


## New Features / Critical Changes

- *Base*
 - This Changelog has been ported to MarkDown (David Coeurjolly,
   [#846](https://github.com/DGtal-team/DGtal/pull/846))

 - Global refactoring of base functors (David Coeurjolly,
   [#861](https://github.com/DGtal-team/DGtal/pull/861))
    - BasicFunctor functors have been moved to functors:: namespace.
    - DefaultFunctor has been renamed functors::Identity.
    - xxxFunctor have been renamed to xxx.
    

- *Geometry Package*
 - Add digital nD Voronoi Covariance Measure support, as well as
  digital geometric estimators based on it. Add tests and examples of
  feature detection with VCM. (Jacques-Olivier Lachaud,
  [#803](https://github.com/DGtal-team/DGtal/pull/803))

 - Various geometric predicates are now available in order to test the
  orientation of three points in the planes. Most classes are template
  classes parametrized by a type for the points (or its coordinates)
  and an integral type for the computations. They always return an
  exact value (or sign), provided that the integral type used for the
  computations is well chosen with respect to the coordinates of the
  points. Some implementations do not increase the size of the input
  integers during the computations. (Tristan Roussillon,
  [#755](https://github.com/DGtal-team/DGtal/pull/755))

  - Logarithmic construction of an arithmetical DSS of minimal
    parameters from a bounding DSL and two end points (ctor of
    ArithmeticalDSS) (Tristan Roussillon,
    [#819](https://github.com/DGtal-team/DGtal/pull/819))

- *Math Package*

    - New classes to compute nD eigen decomposition of symmetric
      matrix (class EigenDecomposition).  Add tests. (Jacques-Olivier
      Lachaud, #803)
    - Simple Linear Regression tool added (backport from
      imagene). (David
      Coeurjolly, [#794](https://github.com/DGtal-team/DGtal/pull/794))

- *Kernel package*
  - BasicPointFunctors functors have been moved in the functors::
    namespace (David Coeurjolly,
    [#863](https://github.com/DGtal-team/DGtal/pull/863))

- *For developpers*
     - Google Benchmark can be enabled to allow micro-benchmarking in
         some DGtal unit tests (https://github.com/google/benchmark)
         (David Coeurjolly,
         [#790](https://github.com/DGtal-team/DGtal/pull/790))



## Changes

- *Base Package*
 - Add comparison operators in variants of CountedPtr. Improve
   coverage of these classes and fix compilation problem
   (Jacques-Olivier Lachaud)
 - XXXOutputRangeYYY classes are now called
   XXXRangeWithWritableIteratorYYY (Tristan Roussillon,
   [#850](https://github.com/DGtal-team/DGtal/pull/850)).

- *Geometry Package*
 - Fix and add concept of CSurfelLocalEstimator and related ground
  truth estimators for implicit polynomial shapes
  (TrueDigitalSurfaceLocalEstimator). (Jacques-Olivier Lachaud,
  [#803](https://github.com/DGtal-team/DGtal/pull/803))
 - Add Integral Invariant estimators so that they meet the concept of
  surface local estimator. Add geometric functors to define easily all
  the geometric estimators that can be built from the volume and
  coariance matrix. (Jeremy Levallois, Jacques-Olivier Lachaud,
  [#803](https://github.com/DGtal-team/DGtal/pull/803) [#856](https://github.com/DGtal-team/DGtal/pull/856))
 - Random-access iterators added in ArithmeticalDSL. (Tristan
   Roussillon, [#801](https://github.com/DGtal-team/DGtal/pull/801))
 - CubicalSudivision has been renamed SpatialCubicalSubdivision and
   moved to "geometry/tools" (David Coeurjolly,
   [#862](https://github.com/DGtal-team/DGtal/pull/862))
 
- *IO Package*
  - Better handling of materials in Board3D and OBJ exports. (David
    Coeurjolly,
    [#784](https://github.com/DGtal-team/DGtal/pull/784))
  - New 'basic' display mode for surfels (oriented or not), useful for
    large digital surface displays (quads instead of 3D prism)
    (Bertrand Kerautret,
    [#783](https://github.com/DGtal-team/DGtal/pull/783))
  - New clear() method to subclasses of Display3D (Viewer3D and
    Board3D) to clear the current drawning buffer. (Kacper Pluta,
    [#807](https://github.com/DGtal-team/DGtal/pull/807))
  - New draw() method for 3D display models (Viewer3D and Board3D) to
    display surfels with prescribed normal vectors (David Coeurjolly,
    [#802](https://github.com/DGtal-team/DGtal/pull/802)).
  - When exporting an 3D visualization to OBJ, a new option will
    rescale the geometry to fit in [-1/2,1/2]^3. (David Coeurjolly,
    [#820](https://github.com/DGtal-team/DGtal/pull/820))

- *Shapes Package*
  - Shape concepts have been moved to concepts:: namespace (David
  Coeurjolly, [#871](https://github.com/DGtal-team/DGtal/pull/871))


## Bug Fixes


- *Base Package*

  - Fixing issue on Circulator/IteratorFunctions (related to #770 on
    MacOS).

- *Kernel Package*
  - BinaryPointPredicate is now specialized for DGtal::AndBoolFct2 and
    DGtal::OrBoolFct2 in order to guarantee that the second computation
    is not performed when the first point predicate return false (resp. true)
    with DGtal::AndBoolFct2 (resp. DGtal::OrBoolFct2) (Tristan Roussillon
    [#852](https://github.com/DGtal-team/DGtal/pull/852)).

- *Geometry Package*
  - Bug fix in PowerMap construction. (David Coeurjolly,
    [#814](https://github.com/DGtal-team/DGtal/pull/814))
  - Bug fix in 3d display of StandardDSS6Computer (Tristan Roussillon
    [#854](https://github.com/DGtal-team/DGtal/pull/854))

- *Topology Package*
  - small fix in ImplicitDigitalSurface. (Jacques-Olivier Lachaud,
    [#803](https://github.com/DGtal-team/DGtal/pull/803))
  - New methods to fill the interior/exterior of digital contours (in the Surface class of topology/helpers).     [#827](https://github.com/DGtal-team/DGtal/pull/827))


- *Image Package*
  - Fixing template types in ImageAdapter (David Coeurjolly,
    [#835](https://github.com/DGtal-team/DGtal/pull/835))
  - Fixing image thresholders which require CConstImage instead of
    CImage (David Coeurjolly,
    [#843](https://github.com/DGtal-team/DGtal/pull/843))
    
- *IO*
  - Bug fix for reading PGM(P2) 3D. (Kacper Pluta,
   [#853](https://github.com/DGtal-team/DGtal/pull/853))
  - Renaming BasicColorToScalarFunctors namespace to functors:: (David
    Coeurjolly,  [#857](https://github.com/DGtal-team/DGtal/pull/857))
    
=== DGtal 0.7 ===

*General*

    - Unit tests build is now disabled by default (to turn it on, run cmake with "-DBUILD_TESTING=on")

    - The "boost program option library" dependency was removed.

    - DGtal needs boost >= 1.46.

    - Thanks to new compiler warning option (-Wdocumentation), the doxygen documentation has been considerably improved.

*Base Package*

    - Complete rewriting of Clone, Alias and ConstAlias
      classes. Parameter passing is now documented with a standardized
      method to determine parameters unambiguously. Associated classed
      CowPtr, CountedPtrOrPtr and CountedConstPtrOrConstPtr are now used
      in conjunction with the previous classes.

    - Few improvments in Clock and Trace base classes.

*Kernel Package*

    - Two initialisation methods (initRemoveOneDim and initAddOneDim)
      for the Projector Functor from the BasicPointFunctors class in
      order to simplify the slice images (with example and test in 2D
      slice image extraction from 3D volume file).

    - New basic functors:
	- SliceRotator2D: to rotate 2D Slice images from 3D volume.
	- Point2DEmbedderIn3D: a simple functor to embed in 3d a 2d points (useful to extract 2D image from 3D volume).

    - Sets have been updated to own their domain with a copy-on-write pointer, in order to avoid some inconsistencies.

*Topology Package*

    - Fixing bugs in Object::isSimple for some digital
      topologies. Speed of Object::isSimple has been improved. Homotopic
      thinning is much faster (even without a precomputed simplicity
      table).

    - Objects have been updated to use Clone services.

*Geometry Package*

    - New classes to deal with arithmetical digital straight segments.
      Now the representation of the primitives and their recognition
      along a discrete structure are separated. The unique class ArithmeticalDSS,
      which was a segment computer, has been replaced by mainly three classes:
      ArithmeticalDSL, ArithmeticalDSS and ArithmeticalDSSComputer.
      This is described in a doc page of the geometry package.
      Note that Backward/Forward suffixes have been renamed into Back/Front.
      Moreover, get prefixes for data members accessors have been removed.

    - Generic adapter to transform a metric (model of CMetric) with
      monotonic (see doc) properties to a separable metric (model of
      CSeparableMetric) which can be used in
      VoronoiMap/DistanceTransformation algorithms.

    - New possibility to access the 3 2D ArithmeticDSS object within an
      ArithmeticDSS3d.

    - New local estimator adapter to make easy implementation of locally defined differential
      estimator on digital surfaces.

    - New documentation on local estimators from digital surface
      patches and surfel functors. New normal vector estimator from
      weighted sum of elementary surfel normal vectors added.

    - With an optional binding with CGAL and Eigen3, new curvature and
      normal vector estimators have been added. For instance, you can
      now estimate curvature from polynomial surface fitting (Jet
      Fitting) and Monge forms.

    - Minor improvements in the spherical accumulator.

    - Improvement of integral invariant estimators (better memory footprint, ...).
      They also allow to estimate principal curvatures using Covariance matrix.
      Covariance matrix is also "masks" based, so the computation is efficient.

    - New algorithms to compute the minimal characteristics of a
      Digital Straight Line subsegment in logarithmic time using local
      convex hulls or Farey Fan. Also works when the DSL
      characteristics are not integers.

    - Chord algorithm for (naive) plane recognition and width computation.

    - New organization for computing primitives. Introduction of the concept
      of PrimitiveComputer and specialization. COBA algorithm and Chord algorithm
      are now models of AdditivePrimitiveComputer.

    - Introduction of the primitive ParallelStrip, computed by COBA and Chord algorithms

    - New documentation for planarity decision, plane recognition and width computation.
      Quantitative and qualitative evaluation of COBA and Chord algorithm.

    - Bug fix in COBA algorithm when extending an empty computer with a group of points.

    - add standard plane recognition with adapter classes both for COBA and Chord algorithm.

*Shape Package*

    - The class MeshFromPoints was transformed into Mesh (more from
      shapes/fromPoints to shapes/ directory), iterators on mesh
      points and mesh face.

*Topology Package*

    - The class SCellToMidPoint is now deprecated. Use CanonicSCellEmbedder instead
      to map a signed cell to its corresponding point in the Euclidean space

*IO Package*

    - Complete refactoring of 3D viewers and boards (Viewer3D, Board3DTo2D).
    - New Board3D to export 3D displays to OBJ 3D vector format.
    - A new display of 2D and 3D image in Viewer3D.
    - New reader: HDF5 file with 2D image dataset(s) (8-bit with palette and 24-bit truecolor with INTERLACE_PIXEL).
    - New GenericReader and Generic Writer for both 2D, 3D and ND images.
    - Adding a Table Reader to extract objets given in a specific column from a text file.
    - Adding missing PPM Reader.
    - Adding missing DICOM reader (with ITK library)
    - Adding ITK reader and ITK writer
    - OpenInventor (SOQT/Coin3D) based viewer has been removed (please consider release <=0.6 if interested).

*Image Package*

    - New concepts : CImageFactory to define the concept describing an
      image factory and CImageCacheReadPolicy/CImageCacheWritePolicy
      to define the concept describing cache read/write policies.

    - New classes : ImageFactoryFromImage to implement a factory to
      produce images from a "bigger/original" one according to a given
      domain, ImageCache to implement an images cache with 'read and
      write' policies, TiledImageFromImage to implement a tiled image
      from a "bigger/original" one.

    - ImageContainerByITKImage complies with CImage.
      The container has been moved from the DGtal::experimental namespace to
      the main DGtal namespace.

*Graph Package*

    - New graph visitor, which allows to visit a graph according to
      any distance object (like the Euclidean distance to some point).

*Math Package*

    - add Histogram class and CBinner concept.
    - add math concepts diagram.


=== DGtal 0.6 ===

 *General*
    - Multithread capabilities via OpenMP are now detected during DGtal
      build. Example of usage can be found in the Volumetric module.

 *Documentation*
    - update documentation for boost concepts, so that subconcepts are
      displayed and html reference pages are pointed.
    - package/module documentation files are now in their associated
      package folder (e.g. kernel/doc/ for kernel package related
      documentation pages). The "make doc" command (or "make dox", see
      below) generates the documentation in the "html/" sub-folder of your
      current build folder.
    - latex citations within doxygen documents are now working

 *Base Package*
    - correct concept checks for some range concepts.
    - Statistic class moved to math package

 *Kernel Package*
    - digital sets are now also point predicates, update of
      DigitalSetDomain accordingly. As a consequence, SetPredicate is
      now deprecated.
    - exposed Compare template parameter of underlying std::set in
      DigitalSetBySTLSet class.

    - new documentation for module digital sets.

 *Arithmetic Package*
    - new class for representing lattice polytopes in 2D (with cut
      operations)
    - bugfix in LighterSternBrocot::Fraction
    - bugfix in ArithmeticalDSS (thanks, Kacper)

 *Image Package*
    - Update on image writers (no colormap required for scalar only writers).
      Documentation updated.
    - New image adapters to adapt both domains and values of an image (ImageAdapter
      and ConstImageAdapter).
    - several enhancements of the main image concept and its image
      container models

 *Geometry Package*
    - New primitives for digital plane recognition. Naive planes, and
      more generally planes with arbitrary axis-width can be detected
      and recognized incrementally. Based on a COBA algorithm
      implementation, which uses 2D lattice polytopes.
    - Fréchet segment computer added to compute bounded simplifications of
      digital curves for instance.
    - Complete rewritting of volumetric tools by separable processes:
      new generic algorithms (VoronoiMap, PowerMap) and metric
      concepts hierarchy (l_2, l_p, ...p) to efficiently compute
      DistanceTransformation, ReverseDistanceTransformation and
      preliminary medial axis extraction.
    - Separable volumetric tools are now multithread using OpenMP.
    - New curvature estimator in 2D/3D based on integral invariants
      (both mean and gaussian curvatures in 3D).

 *Shape Package*
    - New operators available on digital and Euclidean shapes (Union,
      Intersection, Minus)

 *Topology Package*
    - update documentation for digital surfaces and digital surface
      containers so as to emphasize the fact that the ranges are only
      single-pass.

 *Graph Package*
    - New package gathering graph related structures and algorithms
      (visitors, graph concepts, ...)
    - Add concepts for graph visitors
    - Add boost::graph support for DigitalSurface
    - Add documentation for graph package.

 *Math Package*
    - Exact exponentiation x^p by squaring on O(log p) added
      (BasicMathFunctions::power).

 *For developers*
    - new "make dox" target to only build dox file documentation
      ("make doc" for complete documentation build)


=== DGtal 0.5.1 ===
Posted on June, 6th, 2012 by David Coeurjolly

    - New way to cite package/module authors in the documentation
    - Improvement of DGtal::GridCurve ranges
    - Improvement of package concepts  in the  documentation
    - new documentation for DGTal build on MSWindows
    - arithmetic is now a main package (previously in math)
    - Specialized classes for classical metric adjacencies


=== DGtal 0.5 ===
Posted on May, 9th, 2012 by David Coeurjolly

Many changes have been pushed to this release with a lot of nice
tools.  Before going into details component by component, we would
like to focus on a couple of new cool features:

  - new arithmetic package (fractions, models of fraction,
    Stern-Brocot, continued fraction,...)
  - new nD DigitalSurface model (collections of (n-1) topological cells
    with many tools/utilities to track surface elements)
  - update of the build system to make easier the use of DGtal in your
    projects.
  - DGtal and DGtalTools
  - many bugfixes..

* Overall  Project

  - In previous DGtal releases, tools were given in the source
    "tools/" folder. In this release, we have chosen to move the
    tools to another GitHub project
    (http://github.com/DGtal-team/DGtalTools) with a specific
    development process. Please have a look to this project to get
    nice tools built upon the DGtal library.

  - cmake scripts and DGtalConfig have been widely updated to make
    easier the use of the library in your own code

  - We are debugging both the code and the scripts to make it compile
    on windows. We still have couple of issues but most of DGtal
    compiles.

  - Again, efforts have been done on the documentation.


* Package Topology:

 - Creation of the graph concept (see Doxygen documentation)

 - Graph tools have been added: breadth first visitor for any model of
   graph

 - Creation of high-level classes to represent several kinds of
   digital surfaces. Surfaces are n-1 dimensional objetcs and may be
   open or closed. There are several models of digital surface
   containers: boundary of a set of points, explicit set of surfels,
   boundary of a digital object defined by a predicate, frontier
   between two regions, light containers that are discovered on
   traversal but not stored explicitly, etc.

 - All these digital surfaces can be manipulated through the same
   object (DigitalSurface), whichever the container.

 - DigitalSurface is a model of a graph whose vertices are the surfels
   and whose arcs are the connections between surfels.

 - Definition of umbrellas over digital surfaces, that forms faces on
   the surface graph.

 - In 3D, digital surface form combinatorial 2-manifolds with boundary

 - Digital surface can be exported in OFF format

 - Several examples using digital surfaces are provided, like
   extracting isosurfaces from images or volume files defining
   surfaces in labelled images.

* Package Algebraic (new package)

 - Definition of n-variate polynomial as a one-dimensional polynomial
   whose coefficients are n-1-variate polynomials. Coefficient ring
   and dimension are templated.

 - Creation of a reader that can transform a string representation of
   multivariate polynomial into such polynomial object. Use
   boost::spirit.

 - Example using package Topology to extract and display implicit
   polynomial surfaces in 3D.

* Package Arithmetic (new package)

 - Standard arithmetic computations are provided: greatest common
   divisor, Bézout vectors, continued fractions,  convergent.

 - Several representations of irreducible fractions are provided. They
   are based on the Stern-Brocot tree structure. With these fractions,
   amortized constant time operations are provided for computing
   reduced fractions.

 - An implementation of patterns and subpatterns is provided, based on
   the irreducible fractions.
 - A representation of digital standard line in the first quadrant is
   provided, as well as fast algorithms to recognize digital straight
   subsegments.


* Package Image

  - Complete refactoring of Images and ImageContainers (more
    consistent design)

  - Documentation added

  - Graph of concepts added in the documentation


* Package Geometry

  - New SegmentComputer (a.k.a. geometrical primitives to use for
    recognition, curve decomposition,...) : ArithDSS3D (3D DSS), DCA
    (Digital Circular Arcs), CombinatorialDSSS, ...

  - New normal vector field estimation based on elementary normal
    vector convolution in n-D

  - Distance Transformation by Fast Marching Method added.

* Package IO

  - Complete refactoring of the way a DGtal object is displayed in
    boards/viewers.

  - New 2D board  backend: you can export your drawning in TikZ for
    latex includes.


=== DGtal 0.4 ===
Posted on September 26, 2011 by David Coeurjolly

	* Global changes:
	   - A better decomposition of DGtal algorithms and
	data structures into packages.
	   - By default, DGtal is built with minimal dependencies.
	   - Concepts and concept checking mechanism have been
	considerably improved.

	* Kernel Package: refactoring of Integer types considered in
	DGtal.

	* Topology Package: Interpixel/cellular topological model,
	boundary tracking tools, ...

	* Geometry Package:
	  - many things have been added in the 1D contour analysis module:
	multi-modal representation of 1D contours and curves (GridCurve facade),
	decomposition/segmentation into primitives, many differential
	estimators added, helpers for multigrid comparison of estimators
	  - multigrid digital set generators from implicit and parametric
	shapes in dimension 2.

	* I/O Package: refactoring/enhancements of DGtal boards and
	viewers,  enhancement of 2D boards with libcairo and a new
	Board3Dto2D board has been added.


	* Tools: multigrid shapeGenerator/contourGenerator added,
	lengthEstimator/estimatorComparator  added for differential
	estimator multigrid comparison, connected components extraction in
	3D, ...

	* Documentation: User guide has been improved thanks to a
	decomposition of the library into packages.

=== DGtal 0.3.1 ===
Posted on April 4, 2011 by David Coeurjolly

	* Quick release due to a build problem on linux. No more feature
	added.
	* Preliminary cellular grid documentation added.
	* Documentation cleanup.




=== DGtal 0.3.0 ===
Posted on April 1, 2011 by David Coeurjolly

Beside the DGtal presentation at DGCI 2011, we are pleased to announce a new DGtal release 0.3.0.

New features:

    User-guide added (based on doxygen system)
    Kernel: new concepts and controls to enhance the Interger type management, new iterators (Range/SubRange) on HyperRectDomains.
    Topology: interpixel model added (cells, boundary tracking mechanisms,…)
    Geometry 2D: 2D curve primitive decomposition, tangential cover, convexity/concavity decomposition.
    Geometry nD: reverse Euclidean distance transformation
    Visualisation: stream mechanism to visualize 3D DGtal objects with libQGLViewer (optional)
    Shape generator factory added in nD

BugFixes, enhancements:

    Many bugs have been fixed for this release.
    cmake DGtal dependency checking process is more stable now

Known problems:

    For technical reasons, we haven’t be able to verify that this release also compile on Windows Visual Studio systems (see ticket #87). A new release will fix this problem as soon as possible.
    All open tickets





=== Older Releases ===





2011-04-01 dcoeurjo
	* Release 0.3.0
	* Kernel: global enhancement of different Integer types and
	associated concepts.
	* Topology: interpixel topology, cells, surface tracking
	* Geometry2D: contour primitive decomposition, tangential cover,
	convexity/concavity decomposition.
	* GeometrynD: Reverse DT transformation (Euclidean)
	* Infrastructure: 3D visualisation of DGtal objects with
	libQGLViewer, shape factory
	* IO: PointListReader added
	* Documentation: first DGtal user-guide


2010-01-12 dcoeurjo
	* Release 0.2
	* Kernel: DGtalBoard mechanism for 2D drawing of DGtal objects, ..
	* Geometry package
	   - Volumetric: distance transformation with separable	metric
	(l2, l1 and linfinity) in arbitrary dimension
	   - 2D: Arithmetical DSS, Greedy decomposition of a contour into
	primitives, FreemanChain code iterators
	* Topolopy package: Set, Adjacencies, Object, border extraction,
	connected components computation, ...
	* IO: 2D file formats with Magick++, Vol/Raw format in 3D, Raw
	format in n-D (non-portable)
	* Misc: Compiles on linux, MacOS and VisualStudio 2008


2010-21-05 dcoeurjo
	* Iterators added to PointVector
  * Debug methods removed in Trace class
  * Many bug fixes for VS compatibility

2010-05-15 dcoeurjo
  * Assert.h: added macro ASSERT() added based on the boost/assert.hpp (TODO: implement a nice callback)
  * Point and Vector templated classes added
  * Space.*: skeleton of a DGtal::Space added

2010-03-03 dcoeurjo
	* math/MeasureOfStraightLines: new class to compute the measure of a set of Straight lines defined as a polygon in the (a,b) parameter space.
	* test_measure: added

2010-02-17 dcoeurjo
  * Trace: new class models for output streams in Trace class.
  * TraceWriter/TraceWriterTerm/TraceWriterFile: added

2010-02-12 dcoeurjo
  * models: bug fix  in INLINE commands
  * Trace/Clock: minor edit and bug report

2010-01-05 dcoeurjo
  * Trace can be initialized on diffrent output stream (e.g. std::cerr or a file stream)
  * test_trace: update to test the new API

2010-01-04 dcoeurjo
  * Clock: no more static variables and methods (in order to have several running clocks)
  * Trace: new interface and the endBlock displays and returns the ellapsed time within the block

2009-12-28 dcoeurjo
  * Trace: a new class to trace out messages to the standard output. Four type of messages are possible: info, debug, error and "emphased". On color linux terminal, messages appears with an appropriate color foreground.
  * test_trace: an illustration of the Trace interface

2009-12-14 dcoeurjo
  * CMakeLists, test_clock updates to ensure compatibility with VisualStudio
  * New cmake options
    - OPTION(BUILD_SHARED_LIBS "Build shared libraries." ON)
    - OPTION(BUILD_TESTS "Build tests." ON)

2009-12-11 dcoeurjo
	* CMakeLists scripts and first backport from imagene (Clock class)

2009-12-11 dcoeurjo
	* Repository cleanup:
		  - Modeles and genereateClass.sh removed
      - JOL scripts & templates added


2009-12-03 dcoeurjo
	* Modeles: class templates added with generateClass.sh script
