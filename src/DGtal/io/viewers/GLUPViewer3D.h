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
 * @file GLUPViewer3D.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Lorraine, France
 *
 * @date 2016/06/08
 *
 * Header file for module GLUPViewer3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(GLUPViewer3D_RECURSES)
#error Recursive header files inclusion detected in GLUPViewer3D.h
#else // defined(GLUPViewer3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GLUPViewer3D_RECURSES

#if !defined GLUPViewer3D_h
/** Prevents repeated inclusion of headers. */
#define GLUPViewer3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/Display3D.h"
#include "geogram_gfx/glup_viewer/glup_viewer.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class GLUPViewer3D
/**
 * Description of class 'GLUPViewer3D' <p>
 * \brief Aim:
 */
template < typename Space = DGtal::SpaceND<3>,
           typename KSpace = DGtal::KhalimskySpaceND<3> >

class GLUPViewer3D: public GEO::Application, public DGtal::Display3D<Space, KSpace>
{
    // ----------------------- Standard services ------------------------------
public:

    /**
     * Destructor.
     */
    ~GLUPViewer3D();

    // ----------------------- Interface --------------------------------------
public:

  /**
   * \brief DemoGlupApplication constructor.
   */
  GLUPViewer3D( int argc, char** argv,
                const std::string& usage
                ) : GEO::Application(argc, argv, usage) {
      myPoint_size = 10.0f;
      myShrink = 0.0f;
      myIndex = 30;
      // Define the 3d region that we want to display
      // (xmin, ymin, zmin, xmax, ymax, zmax)
      glup_viewer_set_region_of_interest(0.0f, 0.0f, 0.0f, 100.0f, 100.0f, 100.0f);
        
  }
  virtual void draw_scene();


  void updateList ( bool needToUpdateBoundingBox=true );
  

  
  /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;


    enum ImageDirection {xDirection, yDirection, zDirection, undefDirection };
    enum TextureMode {RGBMode, GrayScaleMode };
  
  /**
   * Set the default color for future drawing.
     * @param key a stream key
     * @return a reference on 'this'.
     **/
  GLUPViewer3D<Space, KSpace> & operator<< ( const typename GLUPViewer3D<Space, KSpace>::StreamKey & key );

  
  template <typename TDrawableWithGLUPViewer3D>
  /**
   * Draws the drawable [object] in this board. It should satisfy
   * the concept CDrawableWithViewer3D, which requires for instance a
   * method setStyle( Viewer3D<Space, KSpace> & ).
   *
   * @param object any drawable object.
   * @return a reference on 'this'.
   */
  GLUPViewer3D<Space, KSpace> & operator<< ( const TDrawableWithGLUPViewer3D & object );





  
    // ------------------------- Protected Datas ------------------------------
private:
    // ------------------------- Private Datas --------------------------------
private:

    // ------------------------- Hidden services ------------------------------
protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    GLUPViewer3D();

    void draw_vertex_sphere(GEO::index_t i, GEO::index_t j);

  
    /**
     * Creates an OpenGL list of type GL_QUADS from a CubeD3D.  Only
     * one OpenGL list is created but each map compoment (CubeD3D
     * vector) are marked by its identifier through the OpenGl
     * glPushName() function.
     * See @ref moduleQGLInteraction for more details.
     * @param[in] aCubeMap  a map of cube (CubesMap) associating a name to a vector of CubeD3D.
     **/
  void glupCreateListCubesMaps(const typename DGtal::Display3D<Space, KSpace>::CubesMap &aCubeMap);


  
private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
  GLUPViewer3D ( const DGtal::GLUPViewer3D<Space, KSpace> & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
  GLUPViewer3D & operator= ( const DGtal::GLUPViewer3D<Space, KSpace> & other );



  
  
    // ------------------------- Internals ------------------------------------
private:
  float myPoint_size;
  float myShrink;
  GEO::index_t myIndex;

}; // end of class GLUPViewer3D


/**
 * Overloads 'operator<<' for displaying objects of class 'GLUPViewer3D'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'GLUPViewer3D' to write.
 * @return the output stream after the writing.
 */
template < typename Space, typename KSpace>
std::ostream&
operator<< ( std::ostream & out, const GLUPViewer3D<Space, KSpace> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/io/viewers/GLUPViewer3D.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined GLUPViewer3D_h

#undef GLUPViewer3D_RECURSES
#endif // else defined(GLUPViewer3D_RECURSES)
