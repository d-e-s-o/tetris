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
# * This is the main makefile to be included in every program that is to be built using this
# * build-system. This is the only file of this build-system that is meant to be included directly
# * by a user defined makefile.
# *
# * The following variables are used by the build-system:
# *
# * 1) must be defined:
# * - MAKE_DIR: directory (relative to the user makefile or absolute) where all makefiles
# *             of the build-system (i.e. this file) are located
# *
# * 2) most likely should be defined:
# * - CONF_DIR: directory containing additional definitions; at the moment this build system looks
# *             for a file called conf.mk in there and tries to include it; you may specify
# *             additional rules and flags specific to your environment or thelike there
# *
# * 3) can be defined:
# * - TARGETS_<type>:        names of targets of the given type to build
# * - SUBTARGETS:            list of paths to other makefiles for this build-system that are
# *                          included and built
# * - SRC_ROOT_<target>:     path (relative or absolute) to the root directory of all the source
# *                          files for the given target
# * - SRC_<type>_<target>:   list of filenames of the given source type and the given target; all
# *                          source files for one target will be treated to be relative to the
# *                          target's SRC_ROOT; any files given here should not be located outside
# *                          the directory tree spanned by the source root (so no
# *                          SRC_ROOT/../foo.c)
# * - PRE_DEPENDENCIES_<target>: list of files all prerequesites of the given target depend on
# * - DEPENDENCIES_<target>: list of files the given target depends on (e.g. a static library that
# *                          is to be built by another subtarget and linked to this target)
# * - EXCLUDE_FROM_ALL:      list of targets to exclude from making when no target is explicitly
# *                          specified (so when "all" is being built)
# *
# * 4) can be used:
# * - <target>:            for every target a special variable with the target's name is defined
# *                        that can be used to get the full path to the target
# * - TARGET_DIR_<target>: path to the directory of the given target's makefile relative to the
# *                        position where the actual make was invoked; this variable is important
# *                        whenever you want to your target to be some other's sub-target (which
# *                        you always should assume it might be!) -> prefix every file path that
# *                        is relative to your makefile's directory with this variable
# * - BUILD_DIR_<target>:  in essence this is the target specific TARGET_DIR_<target> directory
# *                        suffixed with the specified BUILD_DIR (see BUILD_DIR below)
# *
# * 5) can be overwritten:
# * - FIXED_DIR_<target>: directory where to place the given target; this is useful mainly for
# *                       targets that need to be created at fixed positions and not relative to
# *                       BUILD_DIR
# * - BUILD_DIR: path (relative) specifying the location, where all object and dependency files (all
# *              that is being generated during the build process) are stored; the given path is
# *              always treated to be relative to the targets makefile; this defaults to the
# *              directory the makefile is in
# * 6) can be set:
# * - QUIET:     set to non empty string to suppress all output of commands and messages alltogether
# * - VERBOSE:   set to non empty string to show actual commands instead of simple message
# * - SUPPRESS:  set to non empty string to suppress output from executed commands
# * - DEBUG:     set to non empty string to enable additional debug output
# *
# * @todo correct dependency handling is tricky - strictly speaking we would need to:
# *       - add some Makefiles to the dependency list (probably hard)
# *       - add environment variables (but not all!) to this list (infeasible?)
# *       - add additional configuration files (conf.mk) to this list (possible, but tricky, as this
# *         could include additional files...)
# * @todo we need a better way for sanitizing input, especially variables that are concerned with
# *       directories which might or might not be terminated by a slash
# */


#/**
# * This include guard protects us from including the contents of this block multiple times
# * (which would be wrong).
# */
ifndef MAKE_MK_INCLUDED
MAKE_MK_INCLUDED := 1

BUILD_DIR ?= .
bld_dir   := $(BUILD_DIR:/=)

.SUFFIXES:
.SECONDEXPANSION:
.DEFAULT_GOAL := all

VPATH :=


 include $(MAKE_DIR)/defines.mk
-include $(CONF_DIR)/conf.mk

 include $(MAKE_DIR)/functions.mk
 include $(MAKE_DIR)/subtargets.mk
 include $(MAKE_DIR)/rules.mk


#/**
# * @param 1 target directory
# * @param 2 source root directory
# * @param 3 target name
# * @param 4 source type
# * @param 5 file extension of source file
# * @param 6 list of files of this source type
# * @param 7 type of object to generate
# */
define dfn_target_src_ext
  $$(call log_debug,dfn_target_src_ext target_dir=$1 root=$2 target=$3\
                    source_type=$4 ext=$5 file_list=$6 generate_type=$7)

  trg_lst_$3 := $$(addsuffix $$(EXT_$7),$$(filter %$5,$6))
  pre_dep_$3 := $$(PRE_DEPENDENCIES_$3)

  $$(if $$(trg_lst_$3),$$(eval $$(call dfn_static_rule_$7_$4,$1,$2,$5,$3,$$(trg_lst_$3),$$(pre_dep_$3))))
endef

#/**
# * @param 1 target directory
# * @param 2 target name
# * @param 3 source type
# */
define dfn_target_src
  $$(call log_debug,dfn_target_src target_dir=$1 target=$2 source_type=$3)

  src_root_$2 := $$(patsubst %/,%,$$(SRC_ROOT_$2))
  src_$2_$3   := $$(patsubst ./%,%,$$(addprefix $1/,$$(SRC_$3_$2)))

  ifdef src_$2_$3
    ext_$2_$3 := $$(sort $$(suffix $$(src_$2_$3)))
    obj_$2_$3 := $$(addsuffix $$(EXT_OBJ),$$(src_$2_$3))
    dep_$2_$3 := $$(addsuffix $$(EXT_DEP),$$(src_$2_$3))

    $$(foreach extension,$$(ext_$2_$3),$$(foreach type,$$(TYPES_GEN),$$(eval\
      $$(call dfn_target_src_ext,$1,$$(src_root_$2),$2,$3,$$(extension),$$(src_$2_$3),$$(type)))))

    ifneq ($$(MAKECMDGOALS),dep)
      ifneq ($$(MAKECMDGOALS),clean)
      -include $$(dep_$2_$3)
      endif
    endif
  endif
endef

#/**
# * @param 1 target name
# * @param 2 target including path
# */
define dfn_phony_target
  $$(call log_debug,dfn_phony_target target=$1 target_with_path=$2)

  ifneq ($1,$2)
    .PHONY: $1
    $1: $2
  endif
endef

#/**
# * This function can be used to create all rules needed for creating a given target.
# * @param 1 target type
# * @param 2 target name
# */
define dfn_target
  $$(call log_debug,dfn_target target_type=$1 target_name=$2)

  trg        := $$(trg) $2
  trg_rel_$2 := $$(patsubst ./%,%,$$(patsubst %/,%,$$(if $$(FIXED_DIR_$2),$$(FIXED_DIR_$2),$$(BUILD_DIR_$2)))/$2)
  trg_lst    := $$(trg_lst) $$(trg_rel_$2)

  $$(foreach type,$$(TYPES_SRC),$$(eval $$(call dfn_target_src,$$(BUILD_DIR_$2),$2,$$(type))))

  trg_dep_$2 := $$(foreach type,$$(TYPES_SRC),$$(obj_$2_$$(type)))

  $$(eval $$(call dfn_target_rule_$1,$$(trg_rel_$2),$2,$$(trg_dep_$2),$$(DEPENDENCIES_$2)))
  $$(eval $$(call dfn_phony_target,$2,$$(trg_rel_$2)))
endef


#/**
# * This is the loop for creating rules for all targets built by the "all" target.
# * @note this call has to be done before all other targets are defined, as some of them use
# *       variables that will be defined here (it is not really nice, but probably the only
# *       solution that does not calculate all the files everywhere again)
# */
$(foreach type,$(TYPES_TRG),$(foreach target,$(trg_$(type)),$(eval\
  $(call dfn_target,$(type),$(target)))))


#/**
# * This is the default target that is to be executed if no other target is specified.
# */
all:: $(filter-out $(trg_exclude),$(trg))


#/**
# * These rules are used for creating a directory marker file including all directories to this
# * file.
# * @note we could use mkdir --parent / -p, but this option is said to be not very portable, thus
# *       we create the list of directories ourself and create them step by step
# * @note we use "|| true" here to suppress the "error...ignored" message from make when using "-"
# *       for ignoring errors
# * @note newer make versions do not allow mixed rules (implicit and normal), thus we need this
# *       define and make two rules out of it
# */
define dfn_dir_marker_target
  $(call log_debug,dfn_dir_marker_target target=$@)

  $(if $(call dirs_dirs,$@),$(V) $(MKDIR) $(call dirs_dirs,$@) &> /dev/null || true)
  $(if $@,                  $(V) $(TOUCH) $@)
endef

$(DIR_MARKER):
	$(dfn_dir_marker_target)

%/$(DIR_MARKER):
	$(dfn_dir_marker_target)


#/**
# * Target for creating all direct dependencies from source files, not from other targets.
# */
dep:: $(foreach target,$(trg),$(patsubst ./%,%,$(addprefix $(BUILD_DIR_$(target))/,\
        $(addsuffix $(EXT_DEP),$(foreach type,$(TYPES_SRC),$(SRC_$(type)_$(target)))))))


#/**
# * This target can be used for removing all previously created files and directories.
# */
clean:: trg   := $(foreach type,$(TYPES_TRG),$(trg_$(type)))
clean:: src   := $(foreach target,$(trg),$(foreach type,$(TYPES_SRC),$(src_$(target)_$(type))))
clean:: obj   := $(foreach target,$(trg),$(foreach type,$(TYPES_SRC),$(obj_$(target)_$(type))))
clean:: dep   := $(foreach target,$(trg),$(foreach type,$(TYPES_SRC),$(dep_$(target)_$(type))))
clean:: dirs  := $(BUILD_DIR) $(call reverse,$(sort $(strip $(foreach target,$(trg),\
                   $(FIXED_DIR_$(target)) $(patsubst ./%,%,$(addprefix $(BUILD_DIR_$(target))/,\
                     $(call dirs_dirs,$(foreach type,$(TYPES_SRC),$(SRC_$(type)_$(target))))))))))
clean:: marks := $(addsuffix /$(DIR_MARKER),$(patsubst %/,%,$(dirs)))
clean:: files := $(strip $(trg_lst) $(obj) $(dep) $(marks))
clean::
	$(MSG_CLEAN)
	$(if $(files),$(V)-$(RM)    $(files)                            $(S))
	$(if $(dirs), $(V)-$(RMDIR) $(patsubst .,,$(dirs)) 2> /dev/null $(S))
else
include $(MAKE_DIR)/subtargets.mk
endif
