// KeyFunctions.cpp

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

#include <climits>

#include "window/include/Windows.hpp"
#include "window/Key.hpp"
#include "window/win32/KeyFunctions.hpp"


namespace wnd
{
  bool virtKeyToKey(int virt_key, Key& key)
  {
    switch(virt_key)
    {
    case VK_BACK:      key = KEY_BACKSPACE;   return true;
    case VK_TAB:       key = KEY_TAB;         return true;
    case VK_CLEAR:     key = KEY_CLEAR;       return true;
    case VK_RETURN:    key = KEY_RETURN;      return true;
    case VK_ESCAPE:    key = KEY_ESCAPE;      return true;
    case VK_SPACE:     key = KEY_SPACE;       return true;
    case VK_SEPARATOR: key = KEY_SEPARATOR;   return true;
    case VK_SUBTRACT:  key = KEY_MINUS;       return true;
    case VK_DECIMAL:   key = KEY_DECIMAL;     return true;
    case VK_DIVIDE:    key = KEY_DIVIDE;      return true;
    case VK_UP:        key = KEY_UP;          return true;
    case VK_DOWN:      key = KEY_DOWN;        return true;
    case VK_RIGHT:     key = KEY_RIGHT;       return true;
    case VK_LEFT:      key = KEY_LEFT;        return true;
    case VK_INSERT:    key = KEY_INSERT;      return true;
    case VK_DELETE:    key = KEY_DELETE;      return true;
    case VK_HOME:      key = KEY_HOME;        return true;
    case VK_END:       key = KEY_END;         return true;
    case VK_PRIOR:     key = KEY_PAGEUP;      return true;
    case VK_NEXT:      key = KEY_PAGEDOWN;    return true;
    case VK_HELP:      key = KEY_HELP;        return true;
    case VK_PRINT:     key = KEY_PRINT;       return true;
    case VK_PAUSE:     key = KEY_PAUSE;       return true;
    case 0x30:         key = KEY_0;           return true;
    case 0x31:         key = KEY_1;           return true;
    case 0x32:         key = KEY_2;           return true;
    case 0x33:         key = KEY_3;           return true;
    case 0x34:         key = KEY_4;           return true;
    case 0x35:         key = KEY_5;           return true;
    case 0x36:         key = KEY_6;           return true;
    case 0x37:         key = KEY_7;           return true;
    case 0x38:         key = KEY_8;           return true;
    case 0x39:         key = KEY_9;           return true;
    case 0x41:         key = KEY_A;           return true;
    case 0x42:         key = KEY_B;           return true;
    case 0x43:         key = KEY_C;           return true;
    case 0x44:         key = KEY_D;           return true;
    case 0x45:         key = KEY_E;           return true;
    case 0x46:         key = KEY_F;           return true;
    case 0x47:         key = KEY_G;           return true;
    case 0x48:         key = KEY_H;           return true;
    case 0x49:         key = KEY_I;           return true;
    case 0x4A:         key = KEY_J;           return true;
    case 0x4B:         key = KEY_K;           return true;
    case 0x4C:         key = KEY_L;           return true;
    case 0x4D:         key = KEY_M;           return true;
    case 0x4E:         key = KEY_N;           return true;
    case 0x4F:         key = KEY_O;           return true;
    case 0x50:         key = KEY_P;           return true;
    case 0x51:         key = KEY_Q;           return true;
    case 0x52:         key = KEY_R;           return true;
    case 0x53:         key = KEY_S;           return true;
    case 0x54:         key = KEY_T;           return true;
    case 0x55:         key = KEY_U;           return true;
    case 0x56:         key = KEY_V;           return true;
    case 0x57:         key = KEY_W;           return true;
    case 0x58:         key = KEY_X;           return true;
    case 0x59:         key = KEY_Y;           return true;
    case 0x5A:         key = KEY_Z;           return true;
    case VK_F1:        key = KEY_F1;          return true;
    case VK_F2:        key = KEY_F2;          return true;
    case VK_F3:        key = KEY_F3;          return true;
    case VK_F4:        key = KEY_F4;          return true;
    case VK_F5:        key = KEY_F5;          return true;
    case VK_F6:        key = KEY_F6;          return true;
    case VK_F7:        key = KEY_F7;          return true;
    case VK_F8:        key = KEY_F8;          return true;
    case VK_F9:        key = KEY_F9;          return true;
    case VK_F10:       key = KEY_F10;         return true;
    case VK_F11:       key = KEY_F11;         return true;
    case VK_F12:       key = KEY_F12;         return true;
    case VK_F13:       key = KEY_F13;         return true;
    case VK_F14:       key = KEY_F14;         return true;
    case VK_F15:       key = KEY_F15;         return true;
    case VK_F16:       key = KEY_F16;         return true;
    case VK_F17:       key = KEY_F17;         return true;
    case VK_F18:       key = KEY_F18;         return true;
    case VK_F19:       key = KEY_F19;         return true;
    case VK_F20:       key = KEY_F20;         return true;
    case VK_NUMPAD0:   key = KEY_KP0;         return true;
    case VK_NUMPAD1:   key = KEY_KP1;         return true;
    case VK_NUMPAD2:   key = KEY_KP2;         return true;
    case VK_NUMPAD3:   key = KEY_KP3;         return true;
    case VK_NUMPAD4:   key = KEY_KP4;         return true;
    case VK_NUMPAD5:   key = KEY_KP5;         return true;
    case VK_NUMPAD6:   key = KEY_KP6;         return true;
    case VK_NUMPAD7:   key = KEY_KP7;         return true;
    case VK_NUMPAD8:   key = KEY_KP8;         return true;
    case VK_NUMPAD9:   key = KEY_KP9;         return true;
    case VK_MULTIPLY:  key = KEY_KP_MULTIPLY; return true;
    case VK_ADD:       key = KEY_KP_PLUS;     return true;
    case VK_NUMLOCK:   key = KEY_NUMLOCK;     return true;
    case VK_CAPITAL:   key = KEY_CAPSLOCK;    return true;
    case VK_LCONTROL:  key = KEY_LCTRL;       return true;
    case VK_RCONTROL:  key = KEY_RCTRL;       return true;
    case VK_LSHIFT:    key = KEY_LSHIFT;      return true;
    case VK_RSHIFT:    key = KEY_RSHIFT;      return true;
    case VK_LMENU:     key = KEY_LALT;        return true;
    case VK_RMENU:     key = KEY_RALT;        return true;
    }
    return false;
  }

  /**
   * @param[in] value value to check whether the low order bit is set
   * @return true if low order bit is set, false if not
   */
  template<typename T>
  inline bool lowOrderBitSet(T value)
  {
    return (value & 0x01) == 0x01;
  }

  /**
   * @param[in] value value to check whether the high order bit is set
   * @return true if high order bit is set, false if not
   */
  template<typename T>
  inline bool highOrderBitSet(T value)
  {
    T bit = T(1 << (sizeof(value) * CHAR_BIT - 1));
    return (value & bit) == bit;
  }

  /**
   * @param[in] virt_key key to check for press state
   * @return true if key is pressed, false if not
   */
  inline bool isKeyDown(int virt_key)
  {
    // If the high-order bit is 1, the key is down; otherwise, it is up.
    SHORT state = GetKeyState(virt_key);
    return highOrderBitSet(state);
  }

  /**
   * @param[in] virt_key key to check for toggle state
   * @return true if key is toggled, false if not
   */
  inline bool isKeyToggled(int virt_key)
  {
    // If the low-order bit is 1, the key is toggled. A key, such as the CAPS LOCK key, is toggled
    // if it is turned on. The key is off and untoggled if the low-order bit is 0.
    SHORT state = GetKeyState(virt_key);
    return lowOrderBitSet(state);
  }

  /**
   * This method checks all relevant modifier keys for their status and
   * returns the combined result.
   * @return variable with all pressed modifier keys or'ed (|) together
   */
  ModifierKey getModifierKeys()
  {
    int key = 0;

    if (isKeyToggled(VK_NUMLOCK))
      key |= MOD_KEY_NUM;
    if (isKeyToggled(VK_CAPITAL))
      key |= MOD_KEY_CAPS;
    if (isKeyDown(VK_LCONTROL))
      key |= MOD_KEY_LCTRL;
    if (isKeyDown(VK_RCONTROL))
      key |= MOD_KEY_RCTRL;
    if (isKeyDown(VK_LSHIFT))
      key |= MOD_KEY_LSHIFT;
    if (isKeyDown(VK_RSHIFT))
      key |= MOD_KEY_RSHIFT;
    if (isKeyDown(VK_LMENU))
      key |= MOD_KEY_LALT;
    if (isKeyDown(VK_RMENU))
      key |= MOD_KEY_RALT;

    if (key == 0)
      key = MOD_KEY_NONE;

    return static_cast<ModifierKey>(key);
  }
}
