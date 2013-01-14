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
 * @file test3DTriangularMeshFrom2DPoints.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2012/07/02
 *
 * Functions for testing class 3DTriangularMeshFrom2DPoints.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/fromPoints/TriangularMeshFrom2DPoints.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"

#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class TriangularMeshFrom2DPoints.
///////////////////////////////////////////////////////////////////////////////

/**
 * Test on various intern fonctions
 *
 */
bool testTriangularMeshFrom2DPointsFct()
{
  trace.beginBlock ( "Testing TriangularMeshFrom2DPoints  functions ..." );
  TriangularMeshFrom2DPoints<Point> aMesh (Point (0,0), Point(100,100));
  aMesh.addPointInsideMesh(Point(80,80));
  aMesh.addPointInsideMesh(Point(80,90));
  aMesh.addPointInsideMesh(Point(50,90));
  aMesh.addPointInsideMesh(Point(30,40));
  aMesh.addPointInsideMesh(Point(50,20));
  aMesh.addPointInsideMesh(Point(60,60));
  Board2D aBoard;
  aBoard << aMesh;
  
  for (unsigned int i =0; i < 10000 ; i++){
    unsigned int x = rand()%100;
    unsigned int y = rand()%100;
    Point p(x,y);
    if(aMesh.isInCircle(aMesh.getNumTriangles()-1, p)){
      aBoard<< p; 
    }    
  } 
  aBoard.saveEPS("testMeshFromTriangleFct.eps");  
  return aMesh.isInCircle(4, Point(90, 50));
}



/**
 * Test on simple Triangular Mesh Construction and fonctions on resulting mesh.
 *
 */
bool testMeshOnSimpleConstruction()
{
  trace.beginBlock ( "Testing Simple Triangular Mesh construction..." );
  TriangularMeshFrom2DPoints<Point> aMesh (Point (0,0), Point(10,10));
  
  aMesh.addPointInsideMesh(Point(4,3));
  aMesh.addPointInsideMesh(Point(7,8));  
  
  bool isIn = aMesh.isInTriangle(3, Point(5,1)); 
  isIn = isIn && aMesh.isInTriangle(4, Point(1,3)); 
  isIn = isIn && aMesh.isInTriangle(5, Point(5,3)); 
  isIn = isIn && aMesh.isInTriangle(6, Point(8,9)); 
  isIn = isIn && aMesh.isInTriangle(7, Point(9,7)); 
  isIn = isIn && aMesh.isInTriangle(8, Point(6,6)); 
  unsigned int indexTr = aMesh.getTriangleIndexInclosingPoint(Point(1,1));
  trace.info() << "index of triangle containing pt (1,1): " << indexTr  << endl;
  unsigned int indexAdjacentTR = aMesh.getIndexAdjacentTriangle(5, 1);
  trace.info() << "index of triangle adjacent to Triangle of index 5 on face 1: " << indexAdjacentTR  << endl;
  unsigned int indexPt6_6 = aMesh.getTriangleIndexInclosingPoint(Point(6,6));
  trace.info() << "index of triangle including point of coords (6, 6): " << indexPt6_6   << endl;
  Board2D aBoard;
  aBoard << aMesh;

 std::vector<Point>  tr1 =  aMesh.getTrianglePoints(indexAdjacentTR);
 std::vector<Point>  tr2 =  aMesh.getTrianglePoints(5);
 
 aBoard.setPenColor(DGtal::Color(200,200,20));
 aBoard.fillTriangle(LibBoard::Point(tr1.at(0)[0],tr1.at(0)[1]), 
		     LibBoard::Point(tr1.at(1)[0],tr1.at(1)[1]),
		     LibBoard::Point(tr1.at(2)[0],tr1.at(2)[1]));
 aBoard.setPenColor(DGtal::Color(100,100,100));
 aBoard.fillTriangle(LibBoard::Point(tr2.at(0)[0],tr2.at(0)[1]), 
		     LibBoard::Point(tr2.at(1)[0],tr2.at(1)[1]),
		     LibBoard::Point(tr2.at(2)[0],tr2.at(2)[1]));
 
 
 

 aBoard.saveEPS("testSimpleTriangularMesh.eps");

  return isIn && indexTr ==4 && indexPt6_6 == indexAdjacentTR;
}






/**
 * Test on triangle transformation.
 *
 */

bool testTriangleSwaping(){
  trace.beginBlock ( "Testing triangle swaping  " );
   TriangularMeshFrom2DPoints<Point> aMesh (Point (0,0), Point(10,10));
   aMesh.addPointInsideMesh(Point(4,3));
   aMesh.addPointInsideMesh(Point(7,8)); 

   aMesh.swapTriangleOnEdge(5, 1);


   // Testing resulting triangles.
   unsigned int indexTr = aMesh.getTriangleIndexInclosingPoint(Point(4,6));
   trace.info() << "index of tr containing (4,6)=" << indexTr << endl;
   unsigned int indexTr2 = aMesh.getTriangleIndexInclosingPoint(Point(3,7));
   trace.info() << "index of tr containing (8,2)=" << indexTr2 << endl;
   Board2D aBoard;
   aBoard << aMesh;
   
   // Testing adjacency of resulting triangles.
   std::vector<Point>  tr1New =  aMesh.getTrianglePoints(indexTr);
   unsigned int adjIndexTr1NewF1 = aMesh.getIndexAdjacentTriangle(indexTr, 1);
   std::vector<Point>  trAdjToNew1F1 =  aMesh.getTrianglePoints(adjIndexTr1NewF1);
   
   aBoard.setPenColor(DGtal::Color(200,200,20));
   aBoard.fillTriangle(LibBoard::Point(tr1New.at(0)[0],tr1New.at(0)[1]), 
		       LibBoard::Point(tr1New.at(1)[0],tr1New.at(1)[1]),
		       LibBoard::Point(tr1New.at(2)[0],tr1New.at(2)[1]));
   aBoard.setPenColor(DGtal::Color(100,100,100));
   aBoard.fillTriangle(LibBoard::Point(trAdjToNew1F1.at(0)[0],trAdjToNew1F1.at(0)[1]), 
		       LibBoard::Point(trAdjToNew1F1.at(1)[0],trAdjToNew1F1.at(1)[1]),
		       LibBoard::Point(trAdjToNew1F1.at(2)[0],trAdjToNew1F1.at(2)[1]));
   unsigned int indexTr3 = aMesh.getTriangleIndexInclosingPoint(Point(5,9));
   trace.info() << "index of tr containing (5,9) = " << indexTr3 << endl;
   trace.info() << "index of tr Adj to TrNew1 face 1 =" << adjIndexTr1NewF1 << endl;


   aBoard.saveEPS("testTriangleSwaping.eps");
   return (indexTr==indexTr2) && (indexTr3 == adjIndexTr1NewF1) ;
}




/**
 * Test on simple Delaunay construction.
 *
 */
bool testMeshFromDelaunayConstruction()
{
  trace.beginBlock ( "Testing Mesh with delaunay contruction  " );
  
  TriangularMeshFrom2DPoints<Point> aMesh (Point (0,0), Point(100,100), true);
  TriangularMeshFrom2DPoints<Point> aMesh2 (Point (0,0), Point(100,100));
  

  aMesh2.addPointInsideMesh(Point(80,80));
  aMesh2.addPointInsideMesh(Point(80,90));
  aMesh2.addPointInsideMesh(Point(50,90));
  aMesh2.addPointInsideMesh(Point(3,4));
  aMesh2.addPointInsideMesh(Point(50,20));
  aMesh2.addPointInsideMesh(Point(60,60));
  
  srand ( time(NULL) );
  for (unsigned int i =0; i < 10000 ; i++){
    trace.progressBar((double) i, 10000);
    unsigned int x = 10+rand()%80;
    unsigned int y = 10+rand()%80;
    Point p(x,y);
    double norme = sqrt((x-50)*(x-50)+(y-50)*(y-50));
    if((norme < 41 && norme > 39) || (norme < 31 && norme > 29)){
      aMesh2.addPointInsideMesh(p);
      aMesh.addPointInsideDelaunayMesh(p);
    }
  } 

  
  Board2D aBoard;


  Board2D aBoard2;
  aBoard2 << aMesh2;    
  aMesh.removeTrianglesOfBoundingVertex();
  std::vector< DGtal::TriangularMeshFrom2DPoints<Point>::MeshTriangle > vectTr = aMesh.getTrianglesIncidentToVertex(5);
  for (unsigned int i = 0; i<vectTr.size(); i++){
    aBoard.setPenColor(DGtal::Color(200,200,20));
    DGtal::TriangularMeshFrom2DPoints<Point>::MeshTriangle tr1New = vectTr.at(i);
    aBoard.fillTriangle(LibBoard::Point(tr1New.point1[0],tr1New.point1[1]), 
			LibBoard::Point(tr1New.point2[0],tr1New.point2[1]),
			LibBoard::Point(tr1New.point3[0],tr1New.point3[1]));
  }
  std::vector<DGtal::TriangularMeshFrom2DPoints<Point>::MeshTriangle> allTr = aMesh.getAllTriangles();
  DGtal::TriangularMeshFrom2DPoints<Point>::CompToOrderTriangle comp;
  comp.pointCenter = Point(50,50);
  sort(allTr.begin(), allTr.end(), comp);
  GradientColorMap<int> cmap_grad(0, allTr.size());
  cmap_grad.addColor( Color( 50, 50, 255 ) );
  cmap_grad.addColor( Color( 255, 0, 0 ) );
  cmap_grad.addColor( Color( 255, 255, 10 ) );
  for (unsigned int i = 0; i<allTr.size(); i++){
    aBoard.setPenColor( cmap_grad(i) );
    DGtal::TriangularMeshFrom2DPoints<Point>::MeshTriangle tr1New = allTr.at(i);
    aBoard.fillTriangle(LibBoard::Point(tr1New.point1[0],tr1New.point1[1]), 
			LibBoard::Point(tr1New.point2[0],tr1New.point2[1]),
			LibBoard::Point(tr1New.point3[0],tr1New.point3[1]));
  } 
  aBoard.setPenColor(DGtal::Color(20,20,20));
  std::vector< std::vector<Point> > vectPolygons = aMesh.getVoronoiDiagram();
  for(unsigned int i=0;i<vectPolygons.size();  i++){
    std::vector< Point> aPolygon = vectPolygons.at(i);
    std::vector< LibBoard::Point > tmpCnt;
    for(unsigned int j=0; j< aPolygon.size(); j++){
      tmpCnt.push_back( LibBoard::Point(aPolygon.at(j)[0], aPolygon.at(j)[1]));
    }
    aBoard.drawPolyline(tmpCnt);
  }  

  aBoard << aMesh;  
  aBoard2.saveEPS("testMeshConstruction.eps");
  aBoard.saveEPS("testMeshConstructionDelaunay.eps");
  aBoard.saveFIG("testMeshConstructionDelaunay.fig");
  return true;
}






/**
 * Test iterator on mesh
 *
 **/
bool testIteratorOnTriangularMesh(){
  trace.beginBlock ( "Testing iterator on Triangular mesh  " );
  TriangularMeshFrom2DPoints<Point> aMesh (Point (0,0), Point(10,10));
  aMesh.addPointInsideDelaunayMesh(Point(4,3));
  aMesh.addPointInsideDelaunayMesh(Point(7,8)); 
  Point ptLast;
  TriangularMeshFrom2DPoints<Point>::TriangularMeshIterator it = aMesh.begin();
  for ( ; it!= aMesh.end(); it++){
    trace.info() << "triangle: " << (*it).point1 << " " << (*it).point2 << " " << (*it).point3 << endl;
    ptLast = (*it).point3;
  }
  return ptLast[0]==7 && ptLast[1]==8;
}








///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class MeshFromPoints" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  bool res1 =  testMeshOnSimpleConstruction();
  trace.emphase() << ( res1 ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  
  bool res2 =  testTriangularMeshFrom2DPointsFct();
  trace.emphase() << ( res2 ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  
  bool res3 = testTriangleSwaping();
  trace.emphase() << ( res3 ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  bool res4 = testMeshFromDelaunayConstruction();
  trace.emphase() << ( res4 ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  
  bool res5 = testIteratorOnTriangularMesh();
  trace.emphase() << ( res5 ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  

  bool resAll = res1 & res2 &  res3 & res4 & res5; 
  trace.emphase() << ( resAll ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return resAll ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
