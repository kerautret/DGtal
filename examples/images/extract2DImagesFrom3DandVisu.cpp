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
 * @file extract2DImagesFrom3D.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/04/24
 *
 * An example file named extract2DImagesFrom3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageHelper.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "ConfigExamples.h"


#include <QtGui/qapplication.h>
#include "DGtal/io/viewers/Viewer3D.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{


  QApplication application(argc,argv);
  Viewer3D viewer;
  viewer.setWindowTitle("simpleViewer");
  viewer.show();


  typedef ImageSelector < Z3i::Domain, unsigned char>::Type Image3D;
  typedef ImageSelector < Z2i::Domain, unsigned char>::Type Image2D;
  typedef DGtal::ConstImageAdapter<Image3D, Image2D::Domain, DGtal::AddOneDimensionDomainFunctor< Z3i::Point>,
   				   Image3D::Value,  DGtal::DefaultFunctor >  SliceImageAdapter;
  DGtal::MinusOneDimensionDomainFunctor<DGtal::Z2i::Point>  invFunctor(2);
  // Importing a 3D image 
  std::string filename = examplesPath + "samples/lobster.vol";
  Image3D image = VolReader<Image3D>::importVol( filename ); 
    
  DGtal::Z2i::Domain domain((invFunctor.operator()(image.domain().lowerBound())), 
			    (invFunctor.operator()(image.domain().upperBound())));
  DGtal::DefaultFunctor idV;
    
  trace.beginBlock ( "Example extract2DImagesFrom3D" );
   
  // Extracting 2D slices ... and visualisation on 3DViewer
  unsigned int pos=0;
  for (unsigned int i=0; i<30; i+=5){
    DGtal::AddOneDimensionDomainFunctor<DGtal::Z3i::Point> aSliceFunctor(2, i);
    SliceImageAdapter sliceImageZ(image, domain, aSliceFunctor, idV);
    viewer << sliceImageZ; 
    viewer << DGtal::UpdateImagePosition(pos, Display3D::zDirection,  i*20, i*20, i*20 );
    pos++;
  }

  viewer << DGtal::Display3D::updateDisplay;
    

  application.exec();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////