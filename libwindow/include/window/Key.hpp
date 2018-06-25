// Key.hpp

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

#ifndef WNDKEY_HPP
#define WNDKEY_HPP


namespace wnd
{
  /**
   * Enumeration for the different keys
   */
  enum Key
  {
    KEY_MIN = 0xDE50,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_CLEAR,
    KEY_RETURN,
    KEY_ESCAPE,
    KEY_SPACE,
    KEY_SEPARATOR,
    KEY_MINUS,
    KEY_DECIMAL,
    KEY_DIVIDE,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGEUP,
    KEY_PAGEDOWN,
    KEY_HELP,
    KEY_PRINT,
    KEY_PAUSE,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,
    KEY_KP0,
    KEY_KP1,
    KEY_KP2,
    KEY_KP3,
    KEY_KP4,
    KEY_KP5,
    KEY_KP6,
    KEY_KP7,
    KEY_KP8,
    KEY_KP9,
    KEY_KP_SEPARATOR,
    KEY_KP_DIVIDE,
    KEY_KP_MULTIPLY,
    KEY_KP_MINUS,
    KEY_KP_PLUS,
    KEY_NUMLOCK,
    KEY_CAPSLOCK,
    KEY_LSHIFT,
    KEY_RSHIFT,
    KEY_LCTRL,
    KEY_RCTRL,
    KEY_LALT,
    KEY_RALT,
    KEY_MAX
  };

  /**
   * Enumeration for the different modifier keys
   * @note Modifier keys can be or'ed (|) to represent multiple activated keys
   */
  enum ModifierKey
  {
    MOD_KEY_MIN = 1,
    MOD_KEY_NONE = 1 << 1,
    MOD_KEY_NUM = 1 << 2,
    MOD_KEY_CAPS = 1 << 3,
    MOD_KEY_LCTRL = 1 << 4,
    MOD_KEY_RCTRL = 1 << 5,
    MOD_KEY_LSHIFT = 1 << 6,
    MOD_KEY_RSHIFT = 1 << 7,
    MOD_KEY_LALT = 1 << 8,
    MOD_KEY_RALT = 1 << 9,
    MOD_KEY_MAX = 1 << 10
  };

  bool checkForModifier(ModifierKey keys, ModifierKey key);
}


namespace wnd
{
  /**
   * This function can be used to check whether a set of keys (combined by |)
   * contains a single other modifier key or another set.
   * @param keys set of keys to check for containing another
   * @param key key to check whether it is included in keys
   * @return true if key is included in keys, false if not
   */
  inline bool checkForModifier(ModifierKey keys, ModifierKey key)
  {
    return (keys & key) == key;
  }
}


#endif
