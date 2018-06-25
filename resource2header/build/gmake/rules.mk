# rules.mk

#/***************************************************************************
# *   Copyright (C) 2012 Daniel Mueller (deso@posteo.net)                   *
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

TYPES_TRG += RES_H

MSG_RES2HPP = $(if $(Q),,$(if $(V),@$(ECHO) "  RES2HPP    "$@))


define dfn_target_rule_RES_H
  $1: $3 $4 $$(dfn_dir_marker)
	$$(MSG_RES2HPP)
	$$(V) $$(RES2HPP) $4 $1 $$(S)
endef
