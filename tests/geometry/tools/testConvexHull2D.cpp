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
 * @file testConvexHull2D.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/06
 *
 * Functions for testing the functions devoted to convex hull computations.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Circulator.h"

#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/tools/Hull2DHelpers.h"
#include "DGtal/geometry/tools/PolarPointComparatorBy2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"
#include "DGtal/geometry/tools/determinant/PredicateFromOrientationFunctor2.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing the functions devoted to convex hull computations.
///////////////////////////////////////////////////////////////////////////////
/**
 * Function that checks whether two ranges are equal up to circular shifts or not. 
 * For example, (1, 2, 3) and (2, 3, 1) are equal, 
 * but (1, 2, 3) and (2, 1, 3) are not equal. 
 *
 * @param first1 begin iterator of the first range
 * @param last1 end iterator of the first range
 * @param first2 begin iterator of the second range
 * @param last2 end iterator of the second range
 * @typename ForwardIterator a model of forward iterator
 *
 * @return 'true' if the two ranges are equal, 'false' otherwise
 */
template <typename ForwardIterator>
bool circularlyEqual(const ForwardIterator& first1, const ForwardIterator& last1, 
		     const ForwardIterator& first2, const ForwardIterator& last2 )
{
  ASSERT( first2 != last2 ); 

  //find a element of the first range equal to the first element of the second range
  ForwardIterator start1 = find( first1, last1, *first2 );
  if (start1 == last1)
    return false; 
  else
    {
      bool areEqual = true; //true if the two ranges are equal up to circular shifts
      //check whether the two ranges are equal or not
      Circulator<ForwardIterator> c1(start1, first1, last1); 
      Circulator<ForwardIterator> cEnd1 = c1; 
      Circulator<ForwardIterator> c2(first2, first2, last2); 
      do
	{
	  if (*c1 != *c2)
	    areEqual = false; 
	  else
	    {
	      ++c1; 
	      ++c2; 
	    }
	} while ( (c1 != cEnd1) && (areEqual) ); 
      return areEqual; 

    }
}

/**
 * Testing functions that computes the convex hull of a range of points
 * @return 'true' if passed. 
 */
bool testConvexHull2D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef PointVector<2,DGtal::int32_t> Point;
  
  trace.beginBlock ( "One simple test..." );

  vector<Point> data, g, res; 
  //data
  data.push_back( Point(2,0) );
  data.push_back( Point(4,0) ); 
  data.push_back( Point(0,3) );
  data.push_back( Point(0,-4) ); 
  data.push_back( Point(3,4) );
  data.push_back( Point(5,0) ); 
  data.push_back( Point(4,3) );
  data.push_back( Point(0,5) ); 
  data.push_back( Point(-3,-4) );
  data.push_back( Point(-5,0) ); 
  data.push_back( Point(-4,-3) );
  data.push_back( Point(0,-5) );
  data.push_back( Point(3,-4) );
  data.push_back( Point(4,-3) );
  data.push_back( Point(-3,4) );
  data.push_back( Point(-4,3) );
  //ground truth
  g.push_back( Point(5,0) ); 
  g.push_back( Point(4,3) );
  g.push_back( Point(3,4) );
  g.push_back( Point(0,5) ); 
  g.push_back( Point(-3,4) );
  g.push_back( Point(-4,3) );
  g.push_back( Point(-5,0) ); 
  g.push_back( Point(-4,-3) );
  g.push_back( Point(-3,-4) );
  g.push_back( Point(0,-5) );
  g.push_back( Point(3,-4) );
  g.push_back( Point(4,-3) );

  //geometric predicate
  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int64_t> Functor;  
  Functor functor; 
  typedef PredicateFromOrientationFunctor2<Functor> Predicate; 
  Predicate predicate( functor ); 

  //namespace
  using namespace functions::Hull2D; 

  //andrew algorithm
  trace.info() << " andrew algorithm " << std::endl; 
  andrewConvexHullAlgorithm( data.begin(), data.end(), back_inserter( res ), predicate );   

  copy(res.begin(), res.end(), ostream_iterator<Point>( cout, " " ) ); 
  cout << endl; 

  if ( (res.size() == g.size()) && 
	(circularlyEqual(res.begin(), res.end(), g.begin(), g.end())) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //graham algorithm
  res.clear(); 
  trace.info() << " graham algorithm " << std::endl;
  functors::PolarPointComparatorBy2x2DetComputer<Point> comparator;  
  grahamConvexHullAlgorithm( data.begin(), data.end(), back_inserter( res ), predicate, comparator );

  copy(res.begin(), res.end(), ostream_iterator<Point>( cout, " " ) ); 
  cout << endl; 

  if ( (res.size() == g.size()) && 
	(circularlyEqual(res.begin(), res.end(), g.begin(), g.end())) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //melkman algorithm
  res.clear(); 
  trace.info() << " melkman algorithm " << std::endl;
  sort( data.begin(), data.end() ); 
  melkmanConvexHullAlgorithm( data.begin(), data.end(), back_inserter( res ), functor );

  copy(res.begin(), res.end(), ostream_iterator<Point>( cout, " " ) ); 
  cout << endl; 

  if ( (res.size() == g.size()) && 
	(circularlyEqual(res.begin(), res.end(), g.begin(), g.end())) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;
  // melkman on line construction of  convex hull:
  trace.info() << "on line convex hull construction" << std::endl;
  DGtal::MelkmanConvexHull<Point, Functor> ch; 
  for(vector<Point>::const_iterator it = data.begin(); it != data.end(); it++)
    {
      ch.add(*it);
    }


  unsigned int cvSize = 0;
  for(DGtal::MelkmanConvexHull<Point, Functor>::ConstIterator it = ch.begin(); it != ch.end(); it++, cvSize++)
    {
      trace.info() << *it ;
    };
  trace.info() << std::endl;

  if(res.size() == cvSize && (cvSize == ch.size()))
    nbok++;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;  
  // test copy and [] operator on convex hull:
  trace.info() << "test copy and [] operator on convex hull:" << std::endl;
  DGtal::MelkmanConvexHull<Point, Functor> ch2 = ch;
  unsigned int cvSize2 = 0;
  for(DGtal::MelkmanConvexHull<Point, Functor>::ConstIterator it = ch.begin(); it != ch.end(); it++, cvSize2++)
    {
      trace.info() << *it ;
    };
   if(res.size() == cvSize2 && ch[0] == ch2[0])
    nbok++;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;  
  trace.endBlock();


  trace.beginBlock ( "Random Tests..." );
  vector<Point> randomData, res1, res2; 
  const int numberOfPoints = 1000; 
  const int numberOfTries = 50; 
  
  for (int i = 0; ( (i < numberOfTries)&&(nbok == nb) ); i++)
    {
      //new data
      randomData.clear(); 
      res1.clear(); 
      res2.clear(); 
      for (int j = 0; j < numberOfPoints; j++)
	  randomData.push_back( Point(rand()%256, rand()%256) ); 
      //computation
      andrewConvexHullAlgorithm( randomData.begin(), randomData.end(), back_inserter( res1 ), predicate );   
      grahamConvexHullAlgorithm( randomData.begin(), randomData.end(), back_inserter( res2 ), predicate, comparator );
      //comparison
      if ( (res1.size() == res2.size()) && 
	   (circularlyEqual(res1.begin(), res1.end(), res2.begin(), res2.end())) )
	nbok++; 
      nb++; 
      trace.info() << "(" << nbok << "/" << nb << ") " << endl;
      //another computation
      res2.clear(); 
      sort( randomData.begin(), randomData.end() ); 
      melkmanConvexHullAlgorithm( randomData.begin(), randomData.end(), back_inserter( res2 ), functor );   
      //comparison
      if ( (res1.size() == res2.size()) && 
	   (circularlyEqual(res1.begin(), res1.end(), res2.begin(), res2.end())) )
	nbok++; 
      nb++; 
      trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    }

  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing convex hull function" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testConvexHull2D();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
