// MemoryBuffer.hpp

/***************************************************************************
 *   Copyright (C) 2009,2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef UTLMEMORYBUFFER_HPP
#define UTLMEMORYBUFFER_HPP

#include "util/Config.hpp"
#include "util/io/StreamBuffer.hpp"


namespace utl
{
  /**
   * @todo add a description and explain why this class is required etc.
   * @todo remove this class once we got rid of the requirement to provide a Writer object to
   *       MemoryBuffer
   */
  struct NoWrite
  {
    /**
     * @param buffer some buffer
     * @param count number of elements in 'buffer'
     * @return true
     */
    bool operator()(byte_t const* buffer, size_t count) const
    {
      return true;
    }
  };


  /**
   * This class implements the StreamBuffer interface for a region of memory.
   * @see StreamBuffer
   * @todo think about exposing the BufferSize parameter
   * @todo remove WriterT parameter once we got rid of flush functionality
   */
  template<size_t BufferSize, typename WriterT>
  class MemoryBuffer: public StreamBuffer
  {
  public:
    MemoryBuffer(WriterT const& writer);

    virtual void put(byte_t value) override;
    virtual void put(byte_t const* range, size_t size) override;

    virtual void flush() override;

    byte_t const* buffer() const;

  private:
    WriterT writer_;

    byte_t buffer_[BufferSize];

    byte_t* const begin_;
    byte_t* const end_;

    byte_t* current_;
  };
}


namespace utl
{
  /**
   * @param begin pointer to first element (begin of memory)
   * @param end pointer to one past the last valid element
   */
  template<size_t BufferSize, typename WriterT>
  inline MemoryBuffer<BufferSize, WriterT>::MemoryBuffer(WriterT const& writer)
    : StreamBuffer(),
      writer_(writer),
      begin_(buffer_),
      end_(buffer_ + sizeof(buffer_)),
      current_(buffer_)
  {
  }

  /**
   * @copydoc StreamBuffer::put
   */
  template<size_t BufferSize, typename WriterT>
  inline void MemoryBuffer<BufferSize, WriterT>::put(byte_t element)
  {
    if (current_ == end_)
      flush();

    *current_ = element;
    current_++;
  }

  /**
   * @copydoc StreamBuffer::put
   */
  template<size_t BufferSize, typename WriterT>
  inline void MemoryBuffer<BufferSize, WriterT>::put(byte_t const* elements, size_t size)
  {
    // @todo implement me!
  }

  /**
   * @copydoc StreamBuffer::flush
   */
  template<size_t BufferSize, typename WriterT>
  inline void MemoryBuffer<BufferSize, WriterT>::flush()
  {
    // @todo WriterT::operator () returns a boolean value indicating whether or not the operation
    //       was success, we need a way to handle it or remove it
    writer_(begin_, current_ - begin_);
    current_ = begin_;
  }

  /**
   * @return pointer to buffer memory
   */
  template<size_t BufferSize, typename WriterT>
  inline byte_t const* MemoryBuffer<BufferSize, WriterT>::buffer() const
  {
    return &buffer_[0];
  }
}


#endif
