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

#include <X11/Xutil.h>

#include "window/Key.hpp"
#include "KeyFunctions.hpp"


namespace wnd
{
  bool translateKey(KeySym key_sym, Key& key)
  {
    switch(key_sym)
    {
    case XK_BackSpace: key = KEY_BACKSPACE;   return true;
    case XK_Tab:       key = KEY_TAB;         return true;
    case XK_Clear:     key = KEY_CLEAR;       return true;
    case XK_Return:    key = KEY_RETURN;      return true;
    case XK_Escape:    key = KEY_ESCAPE;      return true;
    case XK_space:     key = KEY_SPACE;       return true;
    case XK_KP_Separator: key = KEY_SEPARATOR; return true;
    case XK_minus:     key = KEY_MINUS;       return true;
//    case VK_DECIMAL:   key = KEY_DECIMAL;     return true;
//    case VK_DIVIDE:    key = KEY_DIVIDE;      return true;
    case XK_Up:        key = KEY_UP;          return true;
    case XK_Down:      key = KEY_DOWN;        return true;
    case XK_Right:     key = KEY_RIGHT;       return true;
    case XK_Left:      key = KEY_LEFT;        return true;
    case XK_Insert:    key = KEY_INSERT;      return true;
    case XK_Delete:    key = KEY_DELETE;      return true;
    case XK_Home:      key = KEY_HOME;        return true;
    case XK_End:       key = KEY_END;         return true;
    case XK_Page_Up:   key = KEY_PAGEUP;      return true;
    case XK_Page_Down: key = KEY_PAGEDOWN;    return true;
    case XK_Help:      key = KEY_HELP;        return true;
    case XK_Print:     key = KEY_PRINT;       return true;
    case XK_Pause:     key = KEY_PAUSE;       return true;
    case XK_0:         key = KEY_0;           return true;
    case XK_1:         key = KEY_1;           return true;
    case XK_2:         key = KEY_2;           return true;
    case XK_3:         key = KEY_3;           return true;
    case XK_4:         key = KEY_4;           return true;
    case XK_5:         key = KEY_5;           return true;
    case XK_6:         key = KEY_6;           return true;
    case XK_7:         key = KEY_7;           return true;
    case XK_8:         key = KEY_8;           return true;
    case XK_9:         key = KEY_9;           return true;
    case XK_a:         key = KEY_A;           return true;
    case XK_b:         key = KEY_B;           return true;
    case XK_c:         key = KEY_C;           return true;
    case XK_d:         key = KEY_D;           return true;
    case XK_e:         key = KEY_E;           return true;
    case XK_f:         key = KEY_F;           return true;
    case XK_g:         key = KEY_G;           return true;
    case XK_h:         key = KEY_H;           return true;
    case XK_i:         key = KEY_I;           return true;
    case XK_j:         key = KEY_J;           return true;
    case XK_k:         key = KEY_K;           return true;
    case XK_l:         key = KEY_L;           return true;
    case XK_m:         key = KEY_M;           return true;
    case XK_n:         key = KEY_N;           return true;
    case XK_o:         key = KEY_O;           return true;
    case XK_p:         key = KEY_P;           return true;
    case XK_q:         key = KEY_Q;           return true;
    case XK_r:         key = KEY_R;           return true;
    case XK_s:         key = KEY_S;           return true;
    case XK_t:         key = KEY_T;           return true;
    case XK_u:         key = KEY_U;           return true;
    case XK_v:         key = KEY_V;           return true;
    case XK_w:         key = KEY_W;           return true;
    case XK_x:         key = KEY_X;           return true;
    case XK_y:         key = KEY_Y;           return true;
    case XK_z:         key = KEY_Z;           return true;
    case XK_F1:        key = KEY_F1;          return true;
    case XK_F2:        key = KEY_F2;          return true;
    case XK_F3:        key = KEY_F3;          return true;
    case XK_F4:        key = KEY_F4;          return true;
    case XK_F5:        key = KEY_F5;          return true;
    case XK_F6:        key = KEY_F6;          return true;
    case XK_F7:        key = KEY_F7;          return true;
    case XK_F8:        key = KEY_F8;          return true;
    case XK_F9:        key = KEY_F9;          return true;
    case XK_F10:       key = KEY_F10;         return true;
    case XK_F11:       key = KEY_F11;         return true;
    case XK_F12:       key = KEY_F12;         return true;
    case XK_F13:       key = KEY_F13;         return true;
    case XK_F14:       key = KEY_F14;         return true;
    case XK_F15:       key = KEY_F15;         return true;
    case XK_F16:       key = KEY_F16;         return true;
    case XK_F17:       key = KEY_F17;         return true;
    case XK_F18:       key = KEY_F18;         return true;
    case XK_F19:       key = KEY_F19;         return true;
    case XK_F20:       key = KEY_F20;         return true;
    case XK_KP_0:      key = KEY_KP0;         return true;
    case XK_KP_1:      key = KEY_KP1;         return true;
    case XK_KP_2:      key = KEY_KP2;         return true;
    case XK_KP_3:      key = KEY_KP3;         return true;
    case XK_KP_4:      key = KEY_KP4;         return true;
    case XK_KP_5:      key = KEY_KP5;         return true;
    case XK_KP_6:      key = KEY_KP6;         return true;
    case XK_KP_7:      key = KEY_KP7;         return true;
    case XK_KP_8:      key = KEY_KP8;         return true;
    case XK_KP_9:      key = KEY_KP9;         return true;
    case XK_KP_Multiply: key = KEY_KP_MULTIPLY; return true;
    case XK_KP_Add:    key = KEY_KP_PLUS;     return true;
    case XK_Num_Lock:  key = KEY_NUMLOCK;     return true;
    case XK_Caps_Lock: key = KEY_CAPSLOCK;    return true;
    case XK_Control_L: key = KEY_LCTRL;       return true;
    case XK_Control_R: key = KEY_RCTRL;       return true;
    case XK_Shift_L:   key = KEY_LSHIFT;      return true;
    case XK_Shift_R:   key = KEY_RSHIFT;      return true;
    case XK_Alt_L:     key = KEY_LALT;        return true;
    case XK_Alt_R:     key = KEY_RALT;        return true;
    }
    return false;
  }
}
