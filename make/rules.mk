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
# * This define evaluates to a sed command that corrects the compiler dependency output:
# * - it replaces the .o extension emited by gcc with the one we want
# * - it adds the generated dependency file to the list of dependent files
# */
define dfn_trg_sed
  $(SED) '1,1 s!^[^:]\+:!$(@:$(EXT_DEP)=$(EXT_OBJ)): $@!' > $@
endef

define dfn_dir_marker
  $$(@D)/$(DIR_MARKER)
endef


#/**
# * @param 1 build directory
# * @param 2 source root directory
# * @param 3 extension to use
# * @param 4 target name
# * @param 5 files belonging to this rule
# * @param 6 pre dependencies of the target
# * @todo this rules can be made more compact
# */
define dfn_static_rule_DEP_CXX
  $5: $1/%$3$$(EXT_DEP): $2/%$3 $6 $$(dfn_dir_marker)
	$$(MSG_DEPEND)
	$$(V) $$(CXX) $$(CXXFLAGS) $$(CXXFLAGS_$4) -M $$< | $$(dfn_trg_sed) $$(S)
endef

define dfn_static_rule_DEP_C
  $5: $1/%$3$$(EXT_DEP): $2/%$3 $6 $$(dfn_dir_marker)
	$$(MSG_DEPEND)
	$$(V) $$(CC) $$(CFLAGS) $$(CFLAGS_$4) -M $$< | $$(dfn_trg_sed) $$(S)
endef

define dfn_static_rule_OBJ_CXX
  $5: $1/%$3$$(EXT_OBJ): $2/%$3 $6 $$(dfn_dir_marker)
	$$(MSG_COMPILE)
	$$(V) $$(CXX) -c $$(CXXFLAGS) $$(CXXFLAGS_$4) $$< -o $$@ $$(S)
endef

define dfn_static_rule_OBJ_C
  $5: $1/%$3$$(EXT_OBJ): $2/%$3 $6 $$(dfn_dir_marker)
	$$(MSG_COMPILE)
	$$(V) $$(CC) -c $$(CFLAGS) $$(CFLAGS_$4) $$< -o $$@ $$(S)
endef

#/**
# * @param 1 target file (name including path)
# * @param 2 target name
# * @param 3 files this target depends on
# * @param 4 other targets this target depends on
# * @note target specific variables no longer work since we are using lazy evaluated variables in
# *       user makefiles and thus the flags used are just concatenated in the rule directly
# */
define dfn_target_rule_BIN
  $1: $3 $4 $$(dfn_dir_marker)
	$$(MSG_LINK)
	$$(V) $$(LD) $3 -o $$@ $$(LDFLAGS) $$(LDFLAGS_$2) $$(S)
endef

#/**
# * @note $(AR) is very verbose by default, we redirect all output (even possibly useful) to
# *       /dev/null
# */
define dfn_target_rule_AR
  $1: $3 $4 $$(dfn_dir_marker)
	$$(MSG_ARCHIVE)
	$$(V) $$(AR) $$(ARFLAGS) $$(ARFLAGS_$2) $$@ $3 &> /dev/null
endef

define dfn_target_rule_ABS
  $1:: $3 $4
	$$(MSG_ABSTRACT)
	$$(dfn_ABS_$2)
endef
