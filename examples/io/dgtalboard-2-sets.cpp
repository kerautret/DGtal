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
//LICENSE-END
/**
 * @file dgtalboard-2-sets.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/11/26
 *
 * An example file named dgtalboard-2-sets.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/DGtalBoard.h"
#include "DGtal/helpers/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  trace.beginBlock ( "Example dgtalboard-2-sets" );

  Point p1( -10, -7 );
  Point p2( 10, 7 );
  Domain domain( p1, p2 );
  DigitalSet shape_set( domain );
  Shapes<Domain>::addNorm1Ball( shape_set, Point( -5, -1 ), 5 );
  Shapes<Domain>::addNorm1Ball( shape_set, Point( 5, 1 ), 5 );
  shape_set.erase( Point( -5, -1 ) );
  shape_set.erase( Point( 5, 1 ) );

  DGtalBoard board;
  board << domain << shape_set; // display domain and set
  board.saveSVG( "dgtalboard-2-sets-1.svg");
  board.saveEPS( "dgtalboard-2-sets-1.eps");
  board.clear();

  // Object with couple (4,8) of adjacency.
  Object4_8 shape( dt4_8, shape_set );
  board << domain // display domain
	<< SetMode( shape.styleName(), "DrawAdjacencies" )
	<< shape; // and object with mode "DrawAdjacencies"
  board.saveSVG( "dgtalboard-2-sets-2.svg");
  board.saveEPS( "dgtalboard-2-sets-2.eps");
  board.clear();

  // Object with couple (8,4) of adjacency.
  Object8_4 shape2( dt8_4, shape_set );
  board << domain // display domain
	<< SetMode( shape2.styleName(), "DrawAdjacencies" )
	<< shape2; // and object with mode "DrawAdjacencies"
  board.saveSVG( "dgtalboard-2-sets-3.svg");
  board.saveEPS( "dgtalboard-2-sets-3.eps");

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
