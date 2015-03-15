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
 * @file exampleAlphaThickSegmentNoisy.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/01/30
 *
 * An example file named exampleAlphaThickSegmentNoisy.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/base/Common.h"
//! [exampleAlphaThickSegementNoisyInclude]
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/helpers/StdDefs.h"
#include <DGtal/io/readers/PointListReader.h>
//! [exampleAlphaThickSegementNoisyInclude]
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main(  )
{
  trace.beginBlock ( "Example exampleAlphaThickSegment" );

  //! [exampleAlphaThickSegementNoisyTypedef]
  typedef  AlphaThickSegmentComputer< Z2i::RealPoint > AlphaThickSegmentComputer2D;
  //! [exampleAlphaThickSegementNoisyTypedef]
  
  Board2D aBoard;
  std::string file = examplesPath + "samples/contourSnoisy.sdp";
  //! [exampleAlphaThickSegementNoisyReadFile]
  std::vector<Z2i::RealPoint> aContour = PointListReader<Z2i::RealPoint>::getPointsFromFile(file);
  //! [exampleAlphaThickSegementNoisyReadFile]

  // displaying contour
  aBoard << SetMode(aContour[0].className(), "Grid"); 
  for (unsigned int i = 0; i< aContour.size(); i++){
      aBoard << aContour[i];
      aBoard.drawLine(aContour[i][0], aContour[i][1], 
                  aContour[(i+1)%aContour.size()][0], aContour[(i+1)%aContour.size()][1]);
  }

  
  //initialisation of an AlphaThickSegmentComputer2D of thickness 10 and forward recognition.
  //! [exampleAlphaThickSegementNoisInitAndReco]
  //! [exampleAlphaThickSegementNoisInit]
  AlphaThickSegmentComputer2D anAlphaSegment;
  anAlphaSegment.init(15);                             
  //! [exampleAlphaThickSegementNoisInit]
  //! [exampleAlphaThickSegementNoisReco]
  std::vector<Z2i::RealPoint>::const_iterator it =  aContour.begin();  
  while (anAlphaSegment.extendFront(*it)) {
    it++;
  }
  //! [exampleAlphaThickSegementNoisReco]
  //! [exampleAlphaThickSegementNoisInitAndReco]

  //! [exampleAlphaThickSegementDisplay]
  aBoard << anAlphaSegment;  
  //! [exampleAlphaThickSegementDisplay]
  AlphaThickSegmentComputer2D anAlphaSegment2;
  //! [exampleAlphaThickSegementNoisInitAndReco2]
  anAlphaSegment2.init(aContour.begin(), 9);
  while (anAlphaSegment2.end() != aContour.end() && 
         anAlphaSegment2.extendFront()) {
  }
  //! [exampleAlphaThickSegementNoisInitAndReco2]

  //! [exampleAlphaThickSegementNoisCustomColor]  
  aBoard << CustomStyle( anAlphaSegment2.className(), new CustomColors( DGtal::Color::Blue, DGtal::Color::None ) );  
  aBoard << anAlphaSegment2;  
  //! [exampleAlphaThickSegementNoisCustomColor]  

  AlphaThickSegmentComputer2D  anAlphaSegment3;
  anAlphaSegment3.init(aContour.begin(), 2);
  while (anAlphaSegment3.end() != aContour.end() && 
         anAlphaSegment3.extendFront()) {
  }
  aBoard  << CustomStyle( anAlphaSegment3.className(), new CustomColors( DGtal::Color::Green, DGtal::Color::None ) );  
  aBoard << anAlphaSegment3;
  

  aBoard.saveEPS("exampleAlphaThickSegmentNoisy.eps");

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
