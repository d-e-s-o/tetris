#/***************************************************************************
# *   Copyright (C) 2009-2012 Daniel Mueller (deso@posteo.net)              *
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


#/**
# * This little function is used in the "reverse" function. It returns the tail of the list.
# * This is basically the complement to the "firstword" function:
# * $1 == $(firstword $1) $(call tail,$1)
# * @param 1 list of words
# * @return list of words from the given list without the one at the front
# */
tail = $(wordlist 2,$(words $1),$1)


#/**
# * This function can be used to reverse the order of elements of a variable/list.
# * @param 1 list that elements are to be reversed
# * @return list with reversed order of elements
# */
reverse = $(if $1,$(call reverse,$(call tail,$1)) $(firstword $1))


#/**
# * This function is used to implement the dirs_file function. Do not call it directly.
# */
dirs_impl = $(if $1,$1 $(call dirs_impl,$(patsubst ./,,$(dir $(patsubst %/,%,$1)))))


#/**
# * This function returns a list of all directories contained in the path of $1.
# * e.g. file := dir1/dir2/dir3/file.foo
# *      -> the path of file contains the directories: dir1/dir2/dir3/ dir1/dir2/ dir1/
# * @param 1 file or directory to retrieve directory list from
# * @return list of directories contained in the given file
# */
dirs_file = $(call dirs_impl,$(dir $1))


#/**
# * This function takes a list of files and executes the dirs_file function on each of them.
# * @param 1 list of files
# * @return list of direcotires contained in the given list of files
# * @see dirs_file
# */
dirs_files = $(sort $(foreach file,$1,$(call dirs_file,$(file))))


#/**
# * This function uses the dirs_files function to create a sorted list of directories contained in
# * the paths of the files given in $1.
# * @param 1 list of files to get directory list for
# * @return sorted list of directories contained in the given list of files (ready for mkdir)
# */
dirs_dirs = $(call dirs_files,$(sort $(filter-out ./,$(dir $1))))


#/**
# * This function works like dirs_dirs but reverses the order of the directories.
# * @param 1 list of files to get directory list for
# * @return reversely sorted list of directories contained in the given list of files (ready for
# *         rmdir)
# * @note the logic behind this function is the following:
# *  - retrieve the directories of the files (the directories they are in)
# *  - remove all ./ directories (we do not care about the current directory)
# *  - sort the list of directories in lexical order and by that removing duplicates
# *  - retrieve a list of all directories "contained" in the given list of directories
# *  - sort again as there might be new duplicates
# *  - reverse that list (to allow rmdir to work correctly):
# *    - "foo/ foo/bar/" will become "foo/bar/ foo/" which rmdir can remove correctly
# */
dirs_dirs_rev = $(call reverse,$(call dirs_dirs,$1))


#/**
# * @param 1 list of source types
# * @param 2 target name
# * @param 3 prefix of variable name to concatenate the source type to to retrieve the actual
# *          files for that source type
# * @return list of files the target has for every given source type
# */
files_list = $(foreach type,$1,$($(3)_$(type)_$2))


#/**
# * @param 1 target directory
# * @param 2 build directory
# */
mk_dir = $(patsubst ./%,%,$(patsubst %/,%,$1/$(patsubst ./%,%,$(patsubst %/,%,$2)/)))


#/**
# * @param 1 target directory
# * @param 2 list of build directories to create
# */
mk_dirs = $(foreach directory,$2,$(call mk_dir,$1,$(directory)))

#/**
# * Output the given string if debug variable $(D) is set.
# * @param 1 output string
# */
log_debug = $(if $(D),$(info $1))
