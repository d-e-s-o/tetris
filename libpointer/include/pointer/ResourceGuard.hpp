// ResourceGuard.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012 Daniel Mueller (deso@posteo.net)              *
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

#ifndef PTRRESOURCEGUARD_HPP
#define PTRRESOURCEGUARD_HPP


namespace ptr
{
  /**
   * This class template can be used to guard resources. It encapsulates an object that has to be
   * free'd into an automatically allocated object, which will be destroyed on scope exit, freeing
   * the resource it was created with using the given destroyer object. The DestroyerT can be a
   * functor or pointer to function that takes the data as the only parameter.
   */
  template<typename T, typename DestroyerT>
  class ResourceGuard
  {
  public:
    explicit ResourceGuard(T data, DestroyerT destroyer = DestroyerT());
    ~ResourceGuard();

    void release();

  private:
    T          data_;
    DestroyerT destroyer_;

    bool released_;

    ResourceGuard(ResourceGuard const&);
    ResourceGuard& operator =(ResourceGuard const&);
  };
}


namespace ptr
{
  /**
   * @param data data that has to be guarded
   * @param destroyer function or functor that is used to free the data
   */
  template<typename T, typename DestroyerT>
  ResourceGuard<T, DestroyerT>::ResourceGuard(T data, DestroyerT destroyer)
    : data_(data),
      destroyer_(destroyer),
      released_(false)
  {
  }

  /**
   * The destructor free's the data supplied during construction.
   */
  template<typename T, typename DestroyerT>
  ResourceGuard<T, DestroyerT>::~ResourceGuard()
  {
    if (!released_)
      destroyer_(data_);
  }

  /**
   * Calling this method will release the data from its ownage by the guard, meaning it will no
   * longer destroy the data during destruction.
   */
  template<typename T, typename DestroyerT>
  void ResourceGuard<T, DestroyerT>::release()
  {
    released_ = true;
  }
}


#endif
