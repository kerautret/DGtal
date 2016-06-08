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

#pragma once

/**
 * @file CDrawableWithGLUPViewer3D.h
 * @author Aline Martin
 *
 * @date 2013/07/02
 *
 * Header file for concept CDrawableWithGLUPViewer3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDrawableWithGLUPViewer3D_RECURSES)
#error Recursive header files inclusion detected in CDrawableWithGLUPViewer3D.h
#else // defined(CDrawableWithGLUPViewer3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDrawableWithGLUPViewer3D_RECURSES

#if !defined CDrawableWithGLUPViewer3D_h
/** Prevents repeated inclusion of headers. */
#define CDrawableWithGLUPViewer3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"
#include "DGtal/io/CDrawableWithDisplay3D.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class CDrawableWithGLUPViewer3D
  /**
Description of \b concept '\b CDrawableWithGLUPViewer3D' <p>
@ingroup Concepts

@brief Aim:  The concept CDrawableWithGLUPViewer3D specifies what are the classes
that admit an export with Viewer3D.
    
An object x satisfying this concept may then be used as:
    
   \code
   Viewer3D display;
   display << CustomStyle( x.className(), x.defaultStyle() )
         << x;
   \endcode 
   
### Refinement of
   
### Associated types :
   
### Notation
    - \a X : A type that is a model of CDrawableWithGLUPViewer3DD
    - \a x, \a y  : Object of type X
    - \a m  : a string of characters
   
### Definitions
   
### Valid expressions and semantics

| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
|the default draw style | x.defaultStyle( m = "") | mode \a m: \c std::string | CDrawableWithGLUPViewer3D | | returns a dynamic allocation of the default style for the model \a X in mode \a m | | |
|the name of the model X | x.className() | | std::string | | returns a string telling the name of the model X | | |
|the way the object \a x is drawn | x.setStyle(CDrawableWithGLUPViewer3D &display) | | | |draws the object \c x on the \c display stream | | |

### Invariants
   
### Models
    ArimeticalDSS, FreemanChain, HyperRectDomain, ImageContainerByHashTree, ImageContainerBySTLVector, PointVector, DigitalSetBySTLSet,DigitalSetBySTLVector, Object
   
### Notes
    @todo ImageContainerByHashTree does not implement setStyle(display &).
    @todo ImageContainerByHashTree does not implement defaultStyle(std::string&)const.
   */  
  
  
  template <typename T, typename S, typename KS>
  struct CDrawableWithGLUPViewer3D  : public CDrawableWithDisplay3D<T, S, KS>
  {

  BOOST_CONCEPT_USAGE( CDrawableWithGLUPViewer3D )
    {
      //Drawable model should have a className() returning a string
      concepts::ConceptUtils::sameType( myS, myT.className() );

    }

    // ------------------------- Private Datas --------------------------------
  private:

    T myT; //! the drawable class
    DrawableWithGLUPViewer3D *myD;

    std::string myS;

    // ------------------------- Internals ------------------------------------

  }; // end of concept CDrawableWithGLUPViewer3D
  
} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDrawableWithGLUPViewer3D_h

#undef CDrawableWithGLUPViewer3D_RECURSES
#endif // else defined(CDrawableWithGLUPViewer3D_RECURSES)
