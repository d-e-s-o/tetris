// KeyboardCache.hpp

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

#ifndef TTRSKEYBOARDCACHE_HPP
#define TTRSKEYBOARDCACHE_HPP

#include <vector>

#include <window/Key.hpp>


namespace ttrs
{
  /**
   * This class caches the keyboard state data by "intercepting" key press and release events.
   * The main advantage of this class is, that one can press and react on multiple keys at a time,
   * which some systems (like Windows) do not support (pressing another key interrupts the repeat of
   * the previous one there).
   * Another point is that you can freely define the delay after which the key will repeat and at
   * which frequency it will do so.
   */
  class KeyboardCache
  {
  public:
    KeyboardCache(float delay, float interval);

    void update(float time);

    bool onKeyDown(wnd::Key key);
    void onKeyUp(wnd::Key key);

    bool needsAction(wnd::Key& key);

  private:
    struct KeyData
    {
      bool pressed_;
      float time_;

      KeyData();
    };

    typedef std::vector<KeyData> Cache;

    Cache cache_;
    Cache::iterator key_;

    float delay_;
    float interval_;

    KeyData&       getKeyData(wnd::Key key);
    KeyData const& getKeyData(wnd::Key key) const;

    Cache::size_type getIndex(wnd::Key key) const;

    void keyDataChanged();
  };
}


#endif
