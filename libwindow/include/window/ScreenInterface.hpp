// ScreenInterface.hpp

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

#ifndef WNDSCREENBASE_HPP
#define WNDSCREENBASE_HPP

#include <container/Set.hpp>

#include "window/Config.hpp"
#include "window/Resolution.hpp"


namespace wnd
{
  /**
   * This class is the base class for all screen classes.
   * @todo the user should only be able to create one screen instance at a time (well actually the
   *       user does not need to create *ANY*, the WindowImpl does that)
   */
  class LIBWINDOW_EXPORT ScreenInterface
  {
  public:
    typedef ctr::Set<Resolution> Resolutions;
    typedef Resolutions::ConstIterator Iterator;

    ScreenInterface();
    virtual ~ScreenInterface() = 0;

    /**
     * @return resolution currently in use
     * @throw Error if querying resolution failed
     */
    virtual Resolution queryCurrentResolution() const = 0;

    /**
     * This method tries to get a list of the currently available display settings. They can be
     * accessed via BeginResolution and EndResolution.
     * If this method was called before the list is cleared and refilled with the new data.
     * @throw Error if querying resolutions failed
     * @see BeginResolution
     * @see EndResolution
     */
    virtual void queryAvailableResolutions() = 0;

    /**
     * This method changes the current screen resolution to the given one.
     * @param resolution to change to
     * @throw Error if changing resolution failed
     * @note if the ScreenInterface object is destroyed it has to restore the initially set
     *       resolution
     */
    virtual void changeResolution(Resolution const& resolution) = 0;

    /**
     * @return iterator pointing to first resolution
     */
    virtual Iterator beginResolution() const = 0;

    /**
     * @return iterator pointing right behind the last valid resolution
     */
    virtual Iterator endResolution() const = 0;

  private:
    ScreenInterface(ScreenInterface const&);
    ScreenInterface& operator =(ScreenInterface const&);
  };
}


namespace wnd
{
  /**
   * The default constructor creates a new ScreenInterface.
   */
  inline ScreenInterface::ScreenInterface()
  {
  }
}


#endif
