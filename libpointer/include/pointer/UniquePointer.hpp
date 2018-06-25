// UniquePointer.hpp

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

#ifndef PTRUNIQUEPOINTER_HPP
#define PTRUNIQUEPOINTER_HPP

#include "pointer/Deleter.hpp"


namespace ptr
{
  /**
   *
   */
  template<typename T, typename DestroyerT = Deleter>
  class UniquePointer
  {
  public:
    explicit UniquePointer(T* pointer, DestroyerT const& destroyer = DestroyerT());
    UniquePointer(UniquePointer&& pointer);
    UniquePointer(UniquePointer const&) = delete;

    ~UniquePointer();

    UniquePointer& operator =(UniquePointer&& other);
    UniquePointer& operator =(UniquePointer const&) = delete;

    T*       pointer();
    T const* pointer() const;

    T*       operator ->();
    T const* operator ->() const;

    T&       operator *();
    T const& operator *() const;

    operator void const*() const;

  private:
    T*         pointer_;
    DestroyerT destroyer_;
  };


  template<typename T, typename DestroyerT>
  bool operator ==(UniquePointer<T, DestroyerT> const& lhs,
                   UniquePointer<T, DestroyerT> const& rhs);

  template<typename T, typename DestroyerT>
  bool operator !=(UniquePointer<T, DestroyerT> const& lhs,
                   UniquePointer<T, DestroyerT> const& rhs);
}


namespace ptr
{
  /**
   * @param pointer
   * @param destroyer
   */
  template<typename T, typename DestroyerT>
  UniquePointer<T, DestroyerT>::UniquePointer(T* pointer, DestroyerT const& destroyer)
    : pointer_(pointer),
      destroyer_(destroyer)
  {
  }

  /**
   *
   */
  template<typename T, typename DestroyerT>
  UniquePointer<T, DestroyerT>::UniquePointer(UniquePointer&& other)
    : pointer_(other.pointer_),
      destroyer_(other.destroyer_)
  {
    other.pointer_ = nullptr;
  }

  /**
   *
   */
  template<typename T, typename DestroyerT>
  UniquePointer<T, DestroyerT>::~UniquePointer()
  {
    destroyer_(pointer_);
  }

  /**
   * @param other
   */
  template<typename T, typename DestroyerT>
  UniquePointer<T, DestroyerT>& UniquePointer<T, DestroyerT>::operator =(UniquePointer&& other)
  {
    destroyer_(pointer_);

    pointer_   = other.pointer_;
    destroyer_ = other.destroyer_;

    other.pointer_ = nullptr;
    return *this;
  }

  /**
   * @return
   */
  template<typename T, typename DestroyerT>
  T* UniquePointer<T, DestroyerT>::pointer()
  {
    return pointer_;
  }

  /**
   * @return
   */
  template<typename T, typename DestroyerT>
  T const* UniquePointer<T, DestroyerT>::pointer() const
  {
    return pointer_;
  }

  /**
   * @return
   */
  template<typename T, typename DestroyerT>
  T* UniquePointer<T, DestroyerT>::operator ->()
  {
    return pointer_;
  }

  /**
   * @return
   */
  template<typename T, typename DestroyerT>
  T const* UniquePointer<T, DestroyerT>::operator ->() const
  {
    return pointer_;
  }

  /**
   * @return
   */
  template<typename T, typename DestroyerT>
  T& UniquePointer<T, DestroyerT>::operator *()
  {
    return *pointer_;
  }

  /**
   * @return
   */
  template<typename T, typename DestroyerT>
  T const& UniquePointer<T, DestroyerT>::operator *() const
  {
    return *pointer_;
  }

  /**
   * @see SharedPointer::operator void const*() for an explanation why we provide operator void
   *      const* instead of operator bool()
   */
  template<typename T, typename DestroyerT>
  UniquePointer<T, DestroyerT>::operator void const*() const
  {
    return pointer();
  }

  /**
   * @param lhs
   * @param rhs
   */
  template<typename T, typename DestroyerT>
  bool operator ==(UniquePointer<T, DestroyerT> const& lhs,
                   UniquePointer<T, DestroyerT> const& rhs)
  {
    return lhs.pointer() == rhs.pointer();
  }

  /**
   * @param lhs
   * @param rhs
   */
  template<typename T, typename DestroyerT>
  bool operator !=(UniquePointer<T, DestroyerT> const& lhs,
                   UniquePointer<T, DestroyerT> const& rhs)
  {
    return !(lhs == rhs);
  }
}


#endif
