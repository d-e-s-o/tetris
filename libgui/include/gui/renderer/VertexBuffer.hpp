// VertexBuffer.hpp

/***************************************************************************
 *   Copyright (C) 2006-2012,2014 Daniel Mueller (deso@posteo.net)         *
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

#ifndef GUIVERTEXBUFFER_HPP
#define GUIVERTEXBUFFER_HPP

#include <util/Assert.hpp>
#include <container/Array.hpp>
#include <container/ArrayFunctions.hpp>

#include "gui/Allocator.hpp"


namespace gui
{
  /**
   * This class represents a memory saving vertex buffer. If not used (not active) it will clear
   * and shrink the buffer, otherwise it grants access to it.
   */
  template<typename VertexT>
  class VertexBuffer
  {
  protected:
    //typedef typename gui::Allocator::rebind<VertexT>::other Allocator;
    //typedef std::vector<VertexT, Allocator> VertexCache;

    /**
     * @todo use gui::Allocator here
     */
    typedef ctr::Array<VertexT> VertexCache;

  public:
    VertexBuffer(size_t capacity);

    VertexT const* getBegin() const;
    VertexT const* getEnd() const;

    VertexT* getCurrent();

    size_t getCurrentSize() const;
    size_t getRemainingCapacity() const;

    void increaseSize(size_t count);

    void clear();

    bool isActive() const;
    void setActive(bool active);

  private:
    VertexCache cache_;
    size_t      index_;
    size_t      capacity_;

    bool active_;

    VertexBuffer(VertexBuffer const& rhs);
    VertexBuffer& operator =(VertexBuffer const& rhs);
  };
}


namespace gui
{
  /**
   * @param capacity capacity the vertex buffer should have when active (number of vertices it
   *        can hold)
   */
  template<typename VertexT>
  inline VertexBuffer<VertexT>::VertexBuffer(size_t capacity)
    : cache_(0),
      index_(0),
      capacity_(capacity),
      active_(false)
  {
  }

  /**
   * @return pointer to first element in buffer
   */
  template<typename VertexT>
  inline VertexT const* VertexBuffer<VertexT>::getBegin() const
  {
    ASSERT(active_);
    return &cache_[0];
  }

  /**
   * @return pointer to one after the last used vertex
   */
  template<typename VertexT>
  inline VertexT const* VertexBuffer<VertexT>::getEnd() const
  {
    ASSERT(active_);
    ASSERTOP(index_, lt, capacity_);

    return &cache_[index_];
  }

  /**
   * @return pointer to the next untouched vertex that the user can write to
   */
  template<typename VertexT>
  inline VertexT* VertexBuffer<VertexT>::getCurrent()
  {
    ASSERT(active_);
    ASSERTOP(index_, lt, capacity_);

    return &cache_[index_];
  }

  /**
   * @return number of vertices currently in the buffer
   */
  template<typename VertexT>
  inline size_t VertexBuffer<VertexT>::getCurrentSize() const
  {
    ASSERT(active_);
    ASSERTOP(index_, le, capacity_);

    return index_;
  }

  /**
   * @return number of vertices the user can add until the buffer is full
   */
  template<typename VertexT>
  inline size_t VertexBuffer<VertexT>::getRemainingCapacity() const
  {
    ASSERTOP(cache_.size(), eq, capacity_);
    ASSERTOP(index_, le, capacity_);

    return capacity_ - index_;
  }

  /**
   * This function has to be called everytime the user got a pointer to the vertices and copied
   * one or more to the buffer.
   * @param count number of vertices copied into the buffer
   */
  template<typename VertexT>
  inline void VertexBuffer<VertexT>::increaseSize(size_t count)
  {
    ASSERTOP(index_, lt, capacity_);
    index_ += count;
    ASSERTOP(index_, le, capacity_);
  }

  /**
   * This method clears the vertex buffer, after that the full capacity can be used.
   */
  template<typename VertexT>
  inline void VertexBuffer<VertexT>::clear()
  {
    ASSERTOP(index_, le, capacity_);
    index_ = 0;
  }

  /**
   * @return true if the vertex buffer is active, false if not
   */
  template<typename VertexT>
  inline bool VertexBuffer<VertexT>::isActive() const
  {
    return active_;
  }

  /**
   * @param active true to activate the vertex buffer, false to deactivate it
   */
  template<typename VertexT>
  void VertexBuffer<VertexT>::setActive(bool active)
  {
    ASSERTOP(index_, eq, 0);

    if (!active)
      cache_ = VertexCache();
    else
      ctr::resize(cache_, capacity_, VertexT());

    active_ = active;

    ASSERTOP(index_, eq, 0);
  }
}


#endif
