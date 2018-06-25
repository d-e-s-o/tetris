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
# * @param 1 target name
# * @param 2 target directory
# * @note TARGET_DIR_<target> is the directory that contains the Makefile of this target
# * @todo the assignment to $1 is exactly the same as to trg_rel_$2 in make.mk -- find a way to
# *       share the code
# */
define dfn_update_target_var
  TARGET_DIR_$1 := $2
  BUILD_DIR_$1  := $$(call mk_dir,$2,$$(bld_dir))
  $1            := $$(patsubst ./%,%,$$(patsubst %/,%,$$(if $$(FIXED_DIR_$1),$$(FIXED_DIR_$1),$$(BUILD_DIR_$1)))/$1)
endef

#/**
# * @param 1 target type
# * @param 2 target directory
# * @param 3 list of all targets for the given target type
# * @note it is important to only add new subtargets to the list of targets as it must not contain
# *       duplicats; this is necessary as subtargets may be included multiple times and thus can
# *       be listed more than once
# */
define dfn_update_target
  new_$1 := $$(filter-out $$(trg_$1),$3)
  trg_$1 := $$(trg_$1) $$(new_$1)

  $$(foreach target,$$(new_$1),$$(eval $$(call dfn_update_target_var,$$(target),$2)))

  TARGETS_$1 :=
endef

#/**
# * This function calls the dfn_update_target function for every valid target type.
# * @param 1 target directory
# */
define dfn_update_targets
  $$(foreach target,$$(TYPES_TRG),$$(if $$(TARGETS_$$(target)),$$(eval\
    $$(call dfn_update_target,$$(target),$1,$$(TARGETS_$$(target))))))
endef

#/**
# * @param 1 subtarget (path to makefile)
# */
define dfn_subtarget
  sub_trg    := $1
  sub_dir_$1 := $$(patsubst ./%,%,$$(patsubst %/,%,$$(dir $1)))

  include $1

  trg_exclude      := $$(trg_exclude) $$(EXCLUDE_FROM_ALL)
  EXCLUDE_FROM_ALL :=

  $$(eval $$(call dfn_update_targets,$$(sub_dir_$1)))
endef


sub_trg            ?= __this__
sub_trg            := $(sub_trg)
sub_dir_$(sub_trg) ?= .
sub_dir_$(sub_trg) := $(sub_dir_$(sub_trg))
trg_exclude        ?= $(EXCLUDE_FROM_ALL)
trg_exclude        := $(trg_exclude)

# we need to update all non-sub-targets first
$(eval $(call dfn_update_targets,$(sub_dir_$(sub_trg))))

subtargets := $(patsubst ./%,%,$(addprefix $(sub_dir_$(sub_trg))/,$(SUBTARGETS)))
SUBTARGETS :=

# next process the subtargets
$(foreach subtarget,$(subtargets),$(eval $(call dfn_subtarget,$(subtarget))))
