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
 * @file testAlphaThickSegmentComputer.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/01/07
 *
 * Functions for testing class AlphaThickSegmentComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/io/readers/PointListReader.h"
#include <DGtal/io/boards/Board2D.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class AlphaThickSegmentComputer.
///////////////////////////////////////////////////////////////////////////////

/**
 * Test the convexhull and box of a the alpha thick segment computer.
 */
bool testAlphaThickSegmentConvexHullAndBox()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  Board2D aBoard;
  typedef  AlphaThickSegmentComputer< Z2i::Point > AlphaThickSegmentComputer2D;
  trace.beginBlock ( "Testing convexhull and boxes of alphaThick segment on noisy discrete contour." );
  std::vector<Z2i::Point> aContour;
  std::string fileContour = testPath + "samples/contourNoiseSample.sdp";
  aContour = PointListReader<Z2i::Point>::getPointsFromFile(fileContour);
  bool res = true;
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer;
  anAlphaThickSegmentComputer.init(aContour.begin(),5);
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer2;
  anAlphaThickSegmentComputer2.init(aContour.begin(), 10);
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer3;
  anAlphaThickSegmentComputer3.init(aContour.begin(), 2);
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer4;
  anAlphaThickSegmentComputer4.init(aContour.begin(), 1);
  
  
  while (anAlphaThickSegmentComputer.end() != aContour.end() && 
         anAlphaThickSegmentComputer.extendFront()){}  
  while (anAlphaThickSegmentComputer2.end() != aContour.end() &&
         anAlphaThickSegmentComputer2.extendFront() ){}
  while (anAlphaThickSegmentComputer3.end() != aContour.end() && 
         anAlphaThickSegmentComputer3.extendFront()){}
  while (anAlphaThickSegmentComputer4.end() != aContour.end() &&
         anAlphaThickSegmentComputer4.extendFront()){}

    
  // Display convexhull
  std::vector<Z2i::Point> aVect = anAlphaThickSegmentComputer.getConvexHull();
  aBoard.setLineWidth(5);
  aBoard.setPenColor(DGtal::Color::Purple);
  for (unsigned int i = 0; i < aVect.size(); i++){
    aBoard.drawLine(aVect.at(i)[0], aVect.at(i)[1], 
                    aVect.at((i+1)%aVect.size())[0],
                    aVect.at((i+1)%aVect.size())[1]);    
  } 

  
  // Display boundingbox
  aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid"); 
  aBoard << CustomStyle( anAlphaThickSegmentComputer2.className(),
                         new CustomColors( DGtal::Color::Green, DGtal::Color::None ) );  
  aBoard << anAlphaThickSegmentComputer2; 
  aBoard << CustomStyle( anAlphaThickSegmentComputer.className(), 
                         new CustomColors( DGtal::Color::Blue, DGtal::Color::None ) );      
  aBoard << anAlphaThickSegmentComputer;
  aBoard << CustomStyle( anAlphaThickSegmentComputer3.className(), 
                         new CustomColors( DGtal::Color::Yellow, DGtal::Color::None ) );  
  aBoard << anAlphaThickSegmentComputer3;
  aBoard << CustomStyle( anAlphaThickSegmentComputer4.className(), 
                         new CustomColors( DGtal::Color::Magenta, DGtal::Color::None ) );  
  aBoard << anAlphaThickSegmentComputer4;
  

  // Display the input curve
  aBoard << SetMode((*aContour.begin()).className(), "Grid");
  for (std::vector<Z2i::Point>::const_iterator it = aContour.begin(); 
       it != aContour.end(); it++){
    aBoard << *it;
    if (it+1 != aContour.end()){
      Z2i::Point next = *(it+1);
      aBoard.setPenColor(DGtal::Color::Gray);
      aBoard.drawLine((*it)[0], (*it)[1], next[0], next[1]);
    }
  }
  
  aBoard.saveEPS("testAlphaThickSegmentComputer_Convexhull.eps"); 
  trace.info() << " Alpha Thick with alpha 5, size (awaited be 41) = " << anAlphaThickSegmentComputer.getNumberSegmentPoints();
  res = anAlphaThickSegmentComputer.getNumberSegmentPoints()==41;
  nbok += res ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  
  trace.beginBlock("Testing access to extremity points");
  trace.info() << "First extremity point: " << anAlphaThickSegmentComputer.getExtremityPoints().first << 
    " ( should be " << *(aContour.begin())<<  ")" << std::endl;
  trace.info() << "Second extremity point: " << anAlphaThickSegmentComputer.getExtremityPoints().second << 
    " ( should be (80, 18) )" << std::endl;
  
  res = anAlphaThickSegmentComputer.getExtremityPoints().first == *(aContour.begin())&&
        anAlphaThickSegmentComputer.getExtremityPoints().second == Z2i::Point(80,18);
  nbok += res ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();


  trace.beginBlock("Testing access to anti podal points");
  std::pair<std::pair<Z2i::Point, Z2i::Point>, 
            Z2i::Point> pairAntipodal =  anAlphaThickSegmentComputer.getAntipodalLeaningPoints();
  
  Z2i::Point p = pairAntipodal.first.first; 
  Z2i::Point q = pairAntipodal.first.second; 
  Z2i::Point s = pairAntipodal.second;   
  aBoard.setPenColor(DGtal::Color::Red);
  aBoard.drawLine(p[0], p[1], q[0], q[1]);
  aBoard.fillCircle(s[0], s[1], 0.2);
  aBoard.saveEPS("testAlphaThickSegmentComputer_ConvexhullAntipodal.eps"); 
    
  trace.info() << "Antipodal pair: p " << p << ", q:" << q << ", s: "<< s << std::endl; 
  trace.info() << "Should be  " << Z2i::Point(78,16) << " " << Z2i::Point(79,6) << Z2i::Point(83,13) <<std::endl;

  res = p==Z2i::Point(78,16) && q==Z2i::Point(79,6) && s == Z2i::Point(83,13);
  nbok += res ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  
  
  trace.beginBlock("Testing getter of segment parameters");
  Z2i::RealPoint  normalDir =   anAlphaThickSegmentComputer4.getNormal();
  double mu = anAlphaThickSegmentComputer4.getMu();
  double nu = anAlphaThickSegmentComputer4.getNu();
  
  trace.info() << "Segment4 params: normal: " << normalDir<< ",mu: " << mu << ", nu: "<< nu << std::endl; 
  trace.info() << "Should be: normal  " << Z2i::RealPoint(1,-1) << ",mu: " <<  72 << ", nu: "<< 1 <<std::endl;

  res = normalDir == Z2i::RealPoint(1,-1) && mu==72 && nu==1;
  nbok += res ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  return nbok == nb;
}



/**
 * Test alpha thick segment with floating points.
 */
bool testAlphaThickSegmentComputerFloatingPointContour()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Board2D aBoard;
  typedef  AlphaThickSegmentComputer< Z2i::RealPoint> AlphaThickSegmentComputer2D;
  typedef  AlphaThickSegmentComputer< Z2i::RealPoint>::Primitive Primitive;

  trace.beginBlock ( "Testing alpha thick segment on contour composed of floating coords ..." );
  std::vector<Z2i::RealPoint> aContour;
  std::string fileContour = testPath + "samples/contourNoiseSample2.sdp";
  aContour = PointListReader<Z2i::RealPoint>::getPointsFromFile(fileContour);
  
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer;
  anAlphaThickSegmentComputer.init(aContour.begin()+10, 2);
  
  while (anAlphaThickSegmentComputer.end()!= aContour.end() && 
         anAlphaThickSegmentComputer.extendFront()){
  }

  
  // Display alpha thick segment 
  aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid"); 
  aBoard << anAlphaThickSegmentComputer;
  
   
  // Test primitive of parallelStrip and display the input curve
  Primitive pStrip = anAlphaThickSegmentComputer.primitive();
  unsigned int nbInStrip = 0;
  
  aBoard << SetMode((*aContour.begin()).className(), "Grid");
  for (std::vector<Z2i::RealPoint>::const_iterator it = aContour.begin(); 
       it != aContour.end(); it++){
    if (it+1 != aContour.end()){
      Z2i::RealPoint next = *(it+1);
      aBoard.setLineWidth(2);
      aBoard.setPenColor(DGtal::Color::Gray);
      aBoard.drawLine((*it)[0], (*it)[1], next[0], next[1]);
    }
    if (pStrip(*it)){
      nbInStrip++;
      aBoard << *it; 
    }    
  }
  trace.info() << "Nb contour points in the segment parallel strip (awaited 36)  = " << nbInStrip << std::endl;

  nbok += nbInStrip==36;
  nb++;
  
  nbok += anAlphaThickSegmentComputer.getNumberSegmentPoints()==35 ? 1 : 0; 
  nb++;
 
  trace.info() << "Segment size (awaited 35): " << anAlphaThickSegmentComputer.getNumberSegmentPoints() << std::endl;  
  aBoard.saveEPS("testAlphaThickSegmentComputer_FloatingPt.eps"); 
  
  nbok += anAlphaThickSegmentComputer.getNumberSegmentPoints()==35 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock(); 
  return nbok == nb;
}





/**
 * Test  alpha thick segment computer on Freeman Chain.
 */
bool testAlphaThickSegmentFreeman()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef FreemanChain<Z2i::Space::Integer>::ConstIterator FCConstIterator;
  typedef  AlphaThickSegmentComputer< Z2i::Point, FCConstIterator > AlphaThickSegmentComputer2D;

  Board2D aBoard;



  trace.beginBlock ( "Testing AlphaThickSegmentComputer2D on Freeman chain ..." );  

  // Reading input contour
  std::string freemanChainFilename = testPath + "samples/klokan.fc";
  fstream fst;
  fst.open (freemanChainFilename.c_str(), ios::in);
  FreemanChain<Z2i::Space::Integer> fc(fst);
  fst.close();
  aBoard << fc;
  
  
  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer;
  anAlphaThickSegmentComputer.init(fc.begin(),  70.0);
  while (anAlphaThickSegmentComputer.end() != fc.end() && 
         anAlphaThickSegmentComputer.extendFront()){
  }

  
  // Display segment 
  aBoard << SetMode((*anAlphaThickSegmentComputer.begin()).className(), "Grid"); 
  aBoard << anAlphaThickSegmentComputer;
  trace.info() << "Segment size (awaited 642): " << anAlphaThickSegmentComputer.getNumberSegmentPoints() << std::endl;  
  nbok += anAlphaThickSegmentComputer.getNumberSegmentPoints()==642 ? 1 : 0; 
  nb++;  
  
  // Display points inside the parallel strip
  unsigned int nbInStrip = 0;
  AlphaThickSegmentComputer2D::Primitive parallelStrip = anAlphaThickSegmentComputer.primitive();
  
  for(FCConstIterator it  = fc.begin(); it != fc.end(); it++){
    if(parallelStrip(*it)){
      aBoard.setPenColor(DGtal::Color::Blue);
      aBoard.drawCircle( (*it)[0],(*it)[1], 1.0) ;
      nbInStrip++;
    }
  }
  aBoard.setPenColor(DGtal::Color::Green);
  aBoard.fillCircle( (*(fc.begin()))[0],(*(fc.begin()))[1], 1.0) ;
      
  trace.info() << "Nb contour points in the segment parallel strip  (awaited 766)  = " << nbInStrip << std::endl;


  nbok +=  nbInStrip==766 ? 1 : 0; 
  nb++;
  
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();
  aBoard.saveEPS("testAlphaThickSegmentComputer_Freeman.eps"); 
  
  return nbok == nb; 

}





/**
 * Test the segment initialisation (in particular init from 3 points)
 */
bool testAlphaThickSegmentInitialisation()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  Board2D aBoard;
  typedef  AlphaThickSegmentComputer< Z2i::Point > AlphaThickSegmentComputer2D;
  trace.beginBlock ( "Testing segment initialisation from 3 points." );
  bool res = true;
  std::vector<Z2i::Point> v; 
  v.push_back(Z2i::Point(17,12));
  v.push_back(Z2i::Point(18,13));
  v.push_back(Z2i::Point(19,12));
  v.push_back(Z2i::Point(20,12));


  AlphaThickSegmentComputer2D anAlphaThickSegmentComputer;
  anAlphaThickSegmentComputer.init(v.begin(), 1.5);
  
  unsigned int nbPtAdded = 0;
  while (anAlphaThickSegmentComputer.end() != v.end() && 
         anAlphaThickSegmentComputer.extendFront()){nbPtAdded++;}  
  
  std::pair<std::pair<Z2i::Point, Z2i::Point>, 
            Z2i::Point> pairAntipodal =  anAlphaThickSegmentComputer.getAntipodalLeaningPoints();
  Z2i::Point p = pairAntipodal.first.first; 
  Z2i::Point q = pairAntipodal.first.second; 
  Z2i::Point s = pairAntipodal.second;   
  
  trace.info() << "pair antipodal p:" << p << std::endl;
  trace.info() << "pair antipodal q:" << q << std::endl;
  trace.info() << "pair antipodal S:" << s << std::endl;

  trace.info()<< "Nb points added to the segment: "<< anAlphaThickSegmentComputer.getNumberSegmentPoints() << "(should be 4)" << std::endl;
  trace.info()<< anAlphaThickSegmentComputer<< std::endl; 
  res = anAlphaThickSegmentComputer.getNumberSegmentPoints() == 4;
  nbok += res ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  trace.endBlock();

  return nbok == nb;
}





///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class AlphaThickSegmentComputer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testAlphaThickSegmentConvexHullAndBox() & testAlphaThickSegmentComputerFloatingPointContour() 
    & testAlphaThickSegmentFreeman() & testAlphaThickSegmentConvexHullAndBox() &
    testAlphaThickSegmentInitialisation();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;

  
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
