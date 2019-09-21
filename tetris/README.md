tetris
======

**tetris** is a [Tetris][wiki-tetris] clone (yes, yet another) written
in C++, with a minimal set of dependencies. It uses OpenGL for its
rendering and relies on X11 for window creation. Direct3D and Win32
support exists, but after completely transitioning to Linux has not seen
active development for a while.

The game puts together and showcases a set of libraries as well as a
custom GNU make based build system, written over years on the side in an
effort to understand software and OS architecture better and to gain
some software development experience.

A few of the program's features include:
- packaged as a standalone binary with all resources embedded
- configurable through an in-game UI which includes mouse support
- config file support persisting the settings made (`tetris.cfg`)
- arbitrary field sizes and a generic stone rotation algorithm (so it
  would be easily possible to add custom stone constellations)
- a self-playing AI


Usage
-----

The program uses the following key bindings:

| Key    | Function                                 |
|--------|------------------------------------------|
| h      | Move stone left                          |
| l      | Move stone right                         |
| k      | Move stone down                          |
| 1      | Rotate stone left                        |
| 2      | Rotate stone right                       |
| Space  | Drop stone all the way down              |
| Return | Restart the game                         |
| f      | Toggle frames per second counter         |
| s      | Show settings dialog                     |
| q      | Quit the program                         |
| F2     | Toggle self-playing AI                   |
| F3     | Pause the game                           |


Building
--------

**tetris** has the following set of dependencies:
- `g++`
- GNU Make
- `libjpeg` (including headers)
- `libpng` (including headers)
- OpenGL and `glu` (`GL/gl.h` & `GL/glu.h`)

The program can be build as follows:
- `(cd tetris/build/gmake && make --jobs)`

The resulting program is located in `tetris/bin/tetris` and can be
invoked as such. The optional argument `--use-config=<config-path>`
makes the program load and persist its settings from/into the file
`<config-path>`. Note that this path needs to be absolute.


Notes
-----

No, I am not colorblind or like to torture people's eyes. The colors of
the user interface are they way they are because `libgui`, the library
upon which the UI is built, is (was) under development (perhaps more
precisely: the theme you see being used) and a pink-ish color provides a
stark contrast to the colors of the actual UI elements, making for
easier pixel-perfect work.


[wiki-tetris]: https://en.wikipedia.org/wiki/Tetris
