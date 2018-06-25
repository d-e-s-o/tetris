// Evaluate.cpp

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

#include <util/Assert.hpp>
#include <container/String.hpp>
#include <tokenize/Result.hpp>

#include "options/Option.hpp"
#include "options/Error.hpp"
#include "options/Scanner.hpp"
#include "options/Parser.hpp"


namespace opt
{
  namespace
  {
    /**
     * @param begin
     * @param options
     * @param size
     * @param tokens
     * @return
     */
    Error evaluate(char_t const* begin, Option options[], size_t size, parser::Tokens const& tokens)
    {
      for (parser::Tokens::IteratorType poption = tokens.begin(); poption != tokens.end(); poption++)
      {
        ASSERTOP(poption->name_begin, ne, nullptr);
        ASSERTOP(poption->name_end, ne, nullptr);

        bool found = false;

        for (size_t i = 0; i < size; i++)
        {
          ctr::String name(poption->name_begin, poption->name_end);

          if (poption->is_long)
          {
            if (options[i].long_option != 0)
              found = (name == ctr::String(options[i].long_option));
          }
          else
          {
            if (options[i].short_option != 0)
              found = (name == ctr::String(options[i].short_option));
          }

          if (found)
          {
            if (options[i].count > 0 && options[i].type != OPTION_TYPE_ALLOW_MULTIPLE)
              return Error{ERROR_TOO_MANY, i, 0, 0};

            options[i].count++;

            if (poption->arg_begin != 0 || poption->arg_end != 0)
            {
              ASSERTOP(poption->arg_begin, ge, begin);
              ASSERTOP(poption->arg_end, ge, poption->arg_begin);

              size_t index  = poption->arg_begin - begin;
              size_t length = poption->arg_end - poption->arg_begin;

              if (options[i].type != OPTION_TYPE_OPTIONAL_ARGUMENT &&
                  options[i].type != OPTION_TYPE_REQUIRED_ARGUMENT)
              {
                return Error{ERROR_ARGUMENT, i, index, length};
              }

              options[i].argument_index  = index;
              options[i].argument_length = length;
            }
            else if (options[i].type == OPTION_TYPE_REQUIRED_ARGUMENT)
            {
              return Error{ERROR_NO_ARGUMENT, i, 0, 0};
            }
            break;
          }
        }

        if (!found)
        {
          size_t string_index  = poption->name_begin - begin;
          size_t string_length = poption->name_end - poption->name_begin;

          return Error{ERROR_UNKNOWN, 0, string_index, string_length};
        }
      }
      return Error{ERROR_NONE, 0, 0, 0};
    }


    /**
     * @param begin
     * @param stokens
     * @param options
     * @param size
     * @return
     */
    Error parse(char_t const* begin, scanner::Tokens const& stokens, Option options[], size_t size)
    {
      parser::Tokens ptokens;
      tok::Result r = parser::parse(stokens.begin(), stokens.end(), ptokens);

      // this case should actually never happen, I guess, because every scanned token is a valid
      // input to the parser
      if (r.last < 0)
      {
        size_t string_index  = (stokens.begin() + r.max)->begin - begin;
        size_t string_length = (stokens.begin() + r.max)->end -
                               (stokens.begin() + r.max)->begin;

        return Error{ERROR_TOKEN, 0, string_index, string_length};
      }

      if (r.last != stokens.end() - stokens.begin())
      {
        size_t string_index  = (stokens.begin() + r.last)->begin - begin;
        size_t string_length = (stokens.begin() + r.last)->end -
                               (stokens.begin() + r.last)->begin;

        return Error{ERROR_TOKEN, 0, string_index, string_length};
      }
      return evaluate(begin, options, size, ptokens);
    }
  }


  /**
   * @param begin
   * @param end
   * @param options
   * @param size
   * @return
   * @todo we need support for options that contain a dash
   */
  Error evaluate(char_t const* begin, char_t const* end, Option options[], size_t size)
  {
    scanner::Tokens stokens;
    tok::Result r = scanner::scan(begin, end, stokens);

    if (r.last != end - begin)
    {
      size_t string_index  = r.max;
      size_t string_length = (end - begin) - r.max;

      return Error{ERROR_SYMBOL, 0, string_index, string_length};
    }
    return parse(begin, stokens, options, size);
  }
}
