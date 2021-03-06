// JT format reading and visualization tools
// Copyright (C) 2013-2015 OPEN CASCADE SAS
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2 of the License, or any later
// version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// Copy of the GNU General Public License is in LICENSE.txt and  
// on <http://www.gnu.org/licenses/>.

#ifndef _BVH_Box_Header
#define _BVH_Box_Header

#include <BVH_Types.hxx>

//! Defines axis aligned bounding box (AABB) based on BVH vectors.
//! \tparam T Numeric data type
//! \tparam N Vector dimension
template<class T, int N>
class BVH_Box
{
public:

  typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

public:

  //! Creates uninitialized bounding box.
  BVH_Box() : 
      myMinPoint (BVH_VecNt::Zero()),
      myMaxPoint (BVH_VecNt::Zero()),
      myIsInited (Standard_False)  {}

  //! Creates bounding box of given point.
  BVH_Box (const BVH_VecNt& thePoint)
  : myMinPoint (thePoint),
    myMaxPoint (thePoint),
    myIsInited (Standard_True) {}

  //! Creates copy of another bounding box.
  BVH_Box (const BVH_Box& theBox)
  : myMinPoint (theBox.myMinPoint),
    myMaxPoint (theBox.myMaxPoint),
    myIsInited (theBox.myIsInited) {}

  //! Creates bounding box from corner points.
  BVH_Box (const BVH_VecNt& theMinPoint,
           const BVH_VecNt& theMaxPoint)
  : myMinPoint (theMinPoint),
    myMaxPoint (theMaxPoint),
    myIsInited (Standard_True) {}

public:

  //! Clears bounding box.
  void Clear();

  //! Is bounding box valid?
  Standard_Boolean IsValid() const;

  //! Appends new point to the bounding box.
  void Add (const BVH_VecNt& thePoint);

  //! Combines bounding box with another one.
  void Combine (const BVH_Box& theVolume);

  //! Returns minimum point of bounding box.
  const BVH_VecNt& CornerMin() const;

  //! Returns maximum point of bounding box.
  const BVH_VecNt& CornerMax() const;

  //! Returns minimum point of bounding box.
  BVH_VecNt& CornerMin();

  //! Returns maximum point of bounding box.
  BVH_VecNt& CornerMax();

  //! Returns surface area of bounding box.
  T Area() const;

  //! Returns diagonal of bounding box.
  BVH_VecNt Size() const;

  //! Returns center of bounding box.
  BVH_VecNt Center() const;

  //! Returns center of bounding box along the given axis.
  T Center (const Standard_Integer theAxis) const;

protected:

  BVH_VecNt        myMinPoint; //!< Minimum point of bounding box
  BVH_VecNt        myMaxPoint; //!< Maximum point of bounding box
  Standard_Boolean myIsInited; //!< Is bounding box initialized?

public:

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};

namespace BVH
{
  //! Tool class for calculating box center along the given axis.
  //! \tparam T Numeric data type
  //! \tparam N Vector dimension
  template<class T, int N>
  struct CenterAxis
  {
    // Not implemented
  };

  template<class T>
  struct CenterAxis<T, 2>
  {
    static T Center (const BVH_Box<T, 2>& theBox, const Standard_Integer theAxis)
    {
      if (theAxis == 0)
      {
        return (theBox.CornerMin().x() + theBox.CornerMax().x()) * static_cast<T> (0.5);
      }
      else if (theAxis == 1)
      {
        return (theBox.CornerMin().y() + theBox.CornerMax().y()) * static_cast<T> (0.5);
      }
      return static_cast<T> (0.0);
    }
  };

  template<class T>
  struct CenterAxis<T, 3>
  {
    static T Center (const BVH_Box<T, 3>& theBox, const Standard_Integer theAxis)
    {
      if (theAxis == 0)
      {
        return (theBox.CornerMin().x() + theBox.CornerMax().x()) * static_cast<T> (0.5);
      }
      else if (theAxis == 1)
      {
        return (theBox.CornerMin().y() + theBox.CornerMax().y()) * static_cast<T> (0.5);
      }
      else if (theAxis == 2)
      {
        return (theBox.CornerMin().z() + theBox.CornerMax().z()) * static_cast<T> (0.5);
      }
      return static_cast<T> (0.0);
    }
  };

  template<class T>
  struct CenterAxis<T, 4>
  {
    static T Center (const BVH_Box<T, 4>& theBox, const Standard_Integer theAxis)
    {
      if (theAxis == 0)
      {
        return (theBox.CornerMin().x() + theBox.CornerMax().x()) * static_cast<T> (0.5);
      }
      else if (theAxis == 1)
      {
        return (theBox.CornerMin().y() + theBox.CornerMax().y()) * static_cast<T> (0.5);
      }
      else if (theAxis == 2)
      {
        return (theBox.CornerMin().z() + theBox.CornerMax().z()) * static_cast<T> (0.5);
      }
      return static_cast<T> (0.0);
    }
  };

  //! Tool class for calculating surface area of the box.
  //! \tparam T Numeric data type
  //! \tparam N Vector dimension
  template<class T, int N>
  struct SurfaceCalculator
  {
    // Not implemented
  };

  template<class T>
  struct SurfaceCalculator<T, 2>
  {
    static T Area (const typename BVH_Box<T, 2>::BVH_VecNt& theSize)
    {
      return theSize.x() * theSize.y();
    }
  };

  template<class T>
  struct SurfaceCalculator<T, 3>
  {
    static T Area (const typename BVH_Box<T, 3>::BVH_VecNt& theSize)
    {
      return ( theSize.x() * theSize.y() +
               theSize.x() * theSize.z() +
               theSize.z() * theSize.y() ) * static_cast<T> (2.0);
    }
  };

  template<class T>
  struct SurfaceCalculator<T, 4>
  {
    static T Area (const typename BVH_Box<T, 4>::BVH_VecNt& theSize)
    {
      return ( theSize.x() * theSize.y() +
               theSize.x() * theSize.z() +
               theSize.z() * theSize.y() ) * static_cast<T> (2.0);
    }
  };

  //! Tool class for calculate component-wise vector minimum
  //! and maximum (optimized version).
  //! \tparam T Numeric data type
  //! \tparam N Vector dimension
  template<class T, int N>
  struct BoxMinMax
  {
    typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

    static void CwiseMin (BVH_VecNt& theVec1, const BVH_VecNt& theVec2)
    {
      theVec1.x() = Min (theVec1.x(), theVec2.x());
      theVec1.y() = Min (theVec1.y(), theVec2.y());
      theVec1.z() = Min (theVec1.z(), theVec2.z());
    }

    static void CwiseMax (BVH_VecNt& theVec1, const BVH_VecNt& theVec2)
    {
      theVec1.x() = Max (theVec1.x(), theVec2.x());
      theVec1.y() = Max (theVec1.y(), theVec2.y());
      theVec1.z() = Max (theVec1.z(), theVec2.z());
    }
  };

  template<class T>
  struct BoxMinMax<T, 2>
  {
    typedef typename BVH::VectorType<T, 2>::Type BVH_VecNt;

    static void CwiseMin (BVH_VecNt& theVec1, const BVH_VecNt& theVec2)
    {
      theVec1.x() = Min (theVec1.x(), theVec2.x());
      theVec1.y() = Min (theVec1.y(), theVec2.y());
    }

    static void CwiseMax (BVH_VecNt& theVec1, const BVH_VecNt& theVec2)
    {
      theVec1.x() = Max (theVec1.x(), theVec2.x());
      theVec1.y() = Max (theVec1.y(), theVec2.y());
    }
  };
}

#include <BVH_Box.lxx>

#endif // _BVH_Box_Header
