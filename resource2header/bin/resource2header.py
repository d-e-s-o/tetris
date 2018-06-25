#!/usr/bin/env python

#/***************************************************************************
# *   Copyright (C) 2015-2016 Daniel Mueller (deso@posteo.net)              *
# *                                                                         *
# *   This program is free software: you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation, either version 3 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU General Public License for more details.                          *
# *                                                                         *
# *   You should have received a copy of the GNU General Public License     *
# *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
# ***************************************************************************/

"""A script for converting arbitrary files into a hex representation in a C header."""

from argparse import (
  ArgumentParser,
)
from os.path import (
  basename,
  splitext,
)
from sys import (
  argv as sysargv,
)
from textwrap import (
  dedent,
  TextWrapper,
)


def setupArgumentParser():
  """Create and initialize an argument parser, ready for use."""
  parser = ArgumentParser()
  parser.add_argument(
    "in_file", action="store", metavar="IN-FILE",
    help="Input file to convert.",
  )
  parser.add_argument(
    "out_file", action="store", metavar="OUT-FILE",
    help="Output file to write to.",
  )
  return parser


def writeBody(in_file, out_file, indent):
  """Read data from the given file, convert it, and write it into another file."""
  wrapper = TextWrapper(width=80,
                        initial_indent=indent,
                        subsequent_indent=indent)
  remainder = []
  length = 0

  while True:
    in_data = in_file.read(512)
    if in_data == b"":
      break

    out_data = remainder + ["0x%02x" % b for b in in_data]
    length += len(in_data)

    lines = wrapper.wrap(", ".join(out_data))
    # We carry over the last line in case it had not reached the maximum
    # line width.
    for line in lines[:-1]:
      out_file.write(line + "\n")

    remainder = dedent(lines[-1]).split(", ")

  # The remainder might still contain data that we have to write out.
  lines = wrapper.wrap(", ".join(remainder))
  for line in lines:
    out_file.write(line + "\n")

  return length


def main(argv):
  """Convert a file into hexadecimal representation and write it into a C header."""
  parser = setupArgumentParser()
  ns = parser.parse_args(argv[1:])

  in_ = ns.in_file
  out = ns.out_file
  file_, _ = splitext(basename(out))
  base = file_.lower().translate(str.maketrans("-.", "__"))
  guard = "%s" % base.upper()
  content = "%s_data" % base
  size = "%s_size" % base

  with open(in_, "rb") as in_file,\
       open(out, "w+") as out_file:
    # Start by writing the header.
    out_file.write(dedent("""\
      // {file}

      #ifndef {guard}
      #define {guard}


      unsigned char const {content}[] = {{
    """).format(file=file_, guard=guard, content=content))

    # Next comes the actual file content in hexadecimal representation.
    length = writeBody(in_file, out_file, indent="  ")

    out_file.write(dedent("""\
      }};
      unsigned long const {size} = {length};


      #endif
    """).format(size=size, length=length))

  return 0


if __name__ == "__main__":
  exit(main(sysargv))
