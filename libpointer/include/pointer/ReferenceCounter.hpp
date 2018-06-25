// ReferenceCounter.hpp

/***************************************************************************
 *   Copyright (C) 2012,2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef PTRREFERENCECOUNTER_HPP
#define PTRREFERENCECOUNTER_HPP

#include <util/Assert.hpp>


namespace ptr
{
  /**
   *
   */
  template<typename ObjectT, typename DestroyerT>
  class ReferenceCounter
  {
  public:
    ReferenceCounter(ObjectT const& object, DestroyerT const& destroyer);
    ReferenceCounter(ReferenceCounter const& other);
    ReferenceCounter(ReferenceCounter&& other);

    ~ReferenceCounter();

    ReferenceCounter& operator =(ReferenceCounter const& other);
    ReferenceCounter& operator =(ReferenceCounter&& other);

    ObjectT&       object();
    ObjectT const& object() const;

  private:
    class Holder
    {
    public:
      Holder(ObjectT const& object, DestroyerT const& destroyer);
      ~Holder();

      ObjectT& object();

      int up();
      int down();

    private:
      ObjectT    object_;
      DestroyerT destroyer_;

      int count_;

      Holder(Holder const&) = delete;
      Holder(Holder&&) = delete;

      Holder operator =(Holder const&) = delete;
      Holder operator =(Holder&&) = delete;
    };

    Holder* holder_;

    void down();
  };
}


namespace ptr
{
  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>::ReferenceCounter(ObjectT const& object, DestroyerT const& destroyer)
    : holder_(new Holder(object, destroyer))
  {
  }

  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>::ReferenceCounter(ReferenceCounter const& other)
    : holder_(other.holder_)
  {
    holder_->up();
  }

  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>::ReferenceCounter(ReferenceCounter&& other)
    : holder_(other.holder_)
  {
    other.holder_ = nullptr;
  }

  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>::~ReferenceCounter()
  {
    down();
  }

  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>& ReferenceCounter<ObjectT, DestroyerT>::operator =(ReferenceCounter const& other)
  {
    if (this != &other)
    {
      down();

      holder_ = other.holder_;
      holder_->up();
    }
    return *this;
  }

  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>& ReferenceCounter<ObjectT, DestroyerT>::operator =(ReferenceCounter&& other)
  {
    ASSERTOP(this, ne, &other);

    down();

    holder_ = other.holder_;
    other.holder_ = nullptr;

    return *this;
  }

  template<typename ObjectT, typename DestroyerT>
  void ReferenceCounter<ObjectT, DestroyerT>::down()
  {
    // holder_ can be null if we used a move operation
    if (holder_ != nullptr && holder_->down() <= 0)
      delete holder_;
  }

  template<typename ObjectT, typename DestroyerT>
  ObjectT& ReferenceCounter<ObjectT, DestroyerT>::object()
  {
    ASSERTOP(holder_, ne, nullptr);
    return holder_->object();
  }

  template<typename ObjectT, typename DestroyerT>
  ObjectT const& ReferenceCounter<ObjectT, DestroyerT>::object() const
  {
    ASSERTOP(holder_, ne, nullptr);
    return holder_->object();
  }

  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>::Holder::Holder(ObjectT const& object, DestroyerT const& destroyer)
    : object_(object),
      destroyer_(destroyer),
      count_(1)
  {
  }

  template<typename ObjectT, typename DestroyerT>
  ReferenceCounter<ObjectT, DestroyerT>::Holder::~Holder()
  {
    destroyer_(object_);
  }

  template<typename ObjectT, typename DestroyerT>
  ObjectT& ReferenceCounter<ObjectT, DestroyerT>::Holder::object()
  {
    return object_;
  }

  template<typename ObjectT, typename DestroyerT>
  int ReferenceCounter<ObjectT, DestroyerT>::Holder::up()
  {
    return ++count_;
  }

  template<typename ObjectT, typename DestroyerT>
  int ReferenceCounter<ObjectT, DestroyerT>::Holder::down()
  {
    return --count_;
  }
}


#endif
