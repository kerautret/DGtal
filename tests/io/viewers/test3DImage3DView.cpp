/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file test3DImage3DView.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/04/29
 *
 * Functions for testing class Viewer3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <QtGui/qapplication.h>
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/readers/PNMReader.h"
#include "DGtal/math/BasicMathFunctions.h"
#include "ConfigTest.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;



///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Viewer3D.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testViewer3D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;  
  trace.beginBlock ( "Testing block ..." );
  nbok += true ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  typedef DGtal::ImageContainerBySTLVector< DGtal::Z3i::Domain, unsigned char>  Image3D;

 QApplication application(argc,argv);
 Viewer3D viewer;
 viewer.setWindowTitle("simpleViewer");
 viewer.show();
 
 
 Point p1( 0, 0, 0 );
 Point p2( 125, 188, 0 );
 Point p3( 30, 30, 30 );
 
 std::string filename =  testPath + "samples/lobsterCroped.vol";
 
 Image3D image3d =  VolReader<Image3D>::importVol(filename); 
 viewer << SetMode3D(image3d.className(), "BoundingBox");
 viewer << image3d;

 // Extract some slice images:
 // Get the 2D domain of the slice:
  DGtal::MinusOneDimensionDomainFunctor<DGtal::Z2i::Point>  invFunctor(2);
  DGtal::Z2i::Domain domain2D((invFunctor.operator()(image3d.domain().lowerBound())),
			      (invFunctor.operator()(image3d.domain().upperBound())));
  
  typedef DGtal::ConstImageAdapter<Image3D, DGtal::Z2i::Domain,  DGtal::AddOneDimensionDomainFunctor< Z3i::Point>,
				    Image3D::Value,  DGtal::DefaultFunctor >  SliceImageAdapter;
  DGtal::DefaultFunctor idV;
  const DGtal::AddOneDimensionDomainFunctor<DGtal::Z3i::Point> aSliceFunctorY(2, 5);
  SliceImageAdapter sliceImageZ(image3d, domain2D, aSliceFunctorY, idV);

  viewer << sliceImageZ;
  viewer <<  DGtal::UpdateImagePosition(6, DGtal::Display3D::zDirection, 0.0, 0.0, -10.0);  
 
 viewer << p1 << p2 << p3;
 viewer << Display3D::updateDisplay;


 bool res = application.exec();
 trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
 trace.endBlock();
 return res ? 0 : 1;


}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
