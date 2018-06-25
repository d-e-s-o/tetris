// SharedPointer.hpp

/***************************************************************************
 *   Copyright (C) 2012,2013 Daniel Mueller (deso@posteo.net)              *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef PTRSHAREDPOINTER_HPP
#define PTRSHAREDPOINTER_HPP

#include "pointer/ReferenceCounter.hpp"
#include "pointer/Deleter.hpp"


namespace ptr
{
  /**
   * @todo actually, we want the exact to 'guard' to be given as template parameter, so we do not
   *       have to assume it is actually a pointer
   */
  template<typename T, typename DestroyerT = Deleter>
  class SharedPointer
  {
  public:
    explicit SharedPointer(T* pointer = 0, DestroyerT const& destroyer = DestroyerT());

    // use default copy and move constructor and copy and move assignment operator

    T*       pointer();
    T const* pointer() const;

    T*       operator -> ();
    T const* operator -> () const;

    T&       operator * ();
    T const& operator * () const;

    operator void const*() const;

  private:
    typedef ReferenceCounter<T*, DestroyerT> Counter;

    Counter counter_;
  };


  template<typename T, typename DestroyerT>
  bool operator ==(SharedPointer<T, DestroyerT> const& lhs,
                   SharedPointer<T, DestroyerT> const& rhs);

  template<typename T, typename DestroyerT>
  bool operator !=(SharedPointer<T, DestroyerT> const& lhs,
                   SharedPointer<T, DestroyerT> const& rhs);
}


namespace ptr
{
  /**
   * @param pointer
   * @param destroyer
   */
  template<typename T, typename DestroyerT>
  SharedPointer<T, DestroyerT>::SharedPointer(T* pointer, DestroyerT const& destroyer)
    : counter_(pointer, destroyer)
  {
  }

  template<typename T, typename DestroyerT>
  T* SharedPointer<T, DestroyerT>::pointer()
  {
    return counter_.object();
  }

  template<typename T, typename DestroyerT>
  T const* SharedPointer<T, DestroyerT>::pointer() const
  {
    return counter_.object();
  }

  template<typename T, typename DestroyerT>
  T* SharedPointer<T, DestroyerT>::operator ->()
  {
    return counter_.object();
  }

  template<typename T, typename DestroyerT>
  T const* SharedPointer<T, DestroyerT>::operator ->() const
  {
    return counter_.object();
  }

  template<typename T, typename DestroyerT>
  T& SharedPointer<T, DestroyerT>::operator *()
  {
    return *counter_.object();
  }

  template<typename T, typename DestroyerT>
  T const& SharedPointer<T, DestroyerT>::operator *() const
  {
    return *counter_.object();
  }

  /**
   * @note we do not define operator bool or something like that for it leads to unexpected behavior
   *       in some cases, e.g., when comparing SharedPointers using operator <() will invoke
   *       operator bool()
   */
  template<typename T, typename DestroyerT>
  SharedPointer<T, DestroyerT>::operator void const*() const
  {
    return pointer();
  }

  template<typename T, typename DestroyerT>
  bool operator ==(SharedPointer<T, DestroyerT> const& lhs, SharedPointer<T, DestroyerT> const& rhs)
  {
    return lhs.pointer() == rhs.pointer();
  }

  template<typename T, typename DestroyerT>
  bool operator !=(SharedPointer<T, DestroyerT> const& lhs, SharedPointer<T, DestroyerT> const& rhs)
  {
    return !(lhs == rhs);
  }
}


#endif
