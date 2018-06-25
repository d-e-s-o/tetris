// Result.hpp

/***************************************************************************
 *   Copyright (C) 2012 Daniel Mueller                                     *
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

#ifndef TOKRESULT_HPP
#define TOKRESULT_HPP

#include "tokenize/Config.hpp"


namespace tok
{
  /**
   * This structure describes the result of a scan() operation.
   */
  struct Result
  {
    typedef short result_t;

    /**
     * This value represents the number of symbols scanned in the last invocation. This is also used
     * for error reporting, i.e., negative value typically indicates an error.
     */
    result_t last;

    /**
     * This value is the maximum number of symbols parsed. This is mainly useful for error
     * reporting, i.e., giving the user a hint where the actual scan() stopped.
     */
    result_t max;
  };
}


#endif
