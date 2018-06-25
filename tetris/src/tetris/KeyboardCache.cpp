// KeyboardCache.cpp

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

#include <util/Assert.hpp>

#include "tetris/KeyboardCache.hpp"


namespace ttrs
{
  /**
   * @param delay delay to enable key repeat after press
   * @param interval interval in which key repeats will occur
   */
  KeyboardCache::KeyboardCache(float delay, float interval)
    : cache_(wnd::KEY_MAX - wnd::KEY_MIN),
      key_(cache_.end()),
      delay_(delay),
      interval_(interval)
  {
  }

  /**
   * This method updates all "pressed times" for the keys with the given data.
   * @param time time passed since last call
   */
  void KeyboardCache::update(float time)
  {
    if (time > 0.0f)
    {
      for (Cache::iterator it = cache_.begin(); it != cache_.end(); ++it)
      {
        if (it->pressed_)
          it->time_ += time;
      }

      keyDataChanged();
    }
  }

  /**
   * Call this method whenever you recieve a key press event.
   * @param key key that is pressed
   * @return true if the user should execute the action bound to the key, false if not
   */
  bool KeyboardCache::onKeyDown(wnd::Key key)
  {
    KeyData& data = getKeyData(key);

    if (!data.pressed_)
    {
      data.pressed_ = true;
      data.time_    = -delay_;

      keyDataChanged();
      return true;
    }
    return false;
  }

  /**
   * Call this method whenever you receive a key release event.
   * @param key key that was released
   */
  void KeyboardCache::onKeyUp(wnd::Key key)
  {
    KeyData& data = getKeyData(key);

    // there are cases where a key up event happens without a key down before, we ignore them
    if (data.pressed_)
    {
      data.pressed_ = false;
      data.time_    = 0.0f;

      keyDataChanged();
    }
  }

  /**
   * This method checks, if any of the keys needs an action.
   * @param[out] key key the user needs to execute the action bound to it
   * @return true if the user should execute the action bound to the key, false if not
   * @note if there is no need for any action then the 'key' parameter will be left untouched
   */
  bool KeyboardCache::needsAction(wnd::Key& key)
  {
    while (key_ != cache_.end())
    {
      if (key_->pressed_ && key_->time_ >= interval_)
      {
        key = static_cast<wnd::Key>(key_ - cache_.begin() + wnd::KEY_MIN);
        ASSERTOP(key, gt, wnd::KEY_MIN);
        ASSERTOP(key, lt, wnd::KEY_MAX);

        key_->time_ -= interval_;
        return true;
      }

      ++key_;
    }
    return false;
  }

  /**
   * The constructor creates a new KeyData object and initalizes it with the default values.
   */
  inline KeyboardCache::KeyData::KeyData()
    : pressed_(false),
      time_(0.0f)
  {
  }

  /**
   * @param key key to recieve data from
   * @return KeyData associated to the given key
   */
  inline KeyboardCache::KeyData& KeyboardCache::getKeyData(wnd::Key key)
  {
    return cache_[getIndex(key)];
  }

  /**
   * @param key key to recieve data from
   * @return KeyData associated to the given key
   */
  inline KeyboardCache::KeyData const& KeyboardCache::getKeyData(wnd::Key key) const
  {
    return cache_[getIndex(key)];
  }

  /**
   * @param key key to get index in array to
   * @return index the KeyData to the given key is located at
   */
  inline KeyboardCache::Cache::size_type KeyboardCache::getIndex(wnd::Key key) const
  {
    ASSERTOP(key, gt, wnd::KEY_MIN);
    ASSERTOP(key, lt, wnd::KEY_MAX);

    KeyboardCache::Cache::size_type index = key - wnd::KEY_MIN;

    ASSERTOP(index, ge, 0);
    ASSERTOP(index, lt, cache_.size());
    return index;
  }

  /**
   * This method resets the search pointer for the NeedsAction method.
   */
  inline void KeyboardCache::keyDataChanged()
  {
    // start search for "action needing" keys at begin, because something has changed
    key_ = cache_.begin();
  }
}
