#
# Copyright (C) 2020 Claudio Castiglia
#
# This file is part of caio.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, see http://www.gnu.org/licenses/
#
ifeq (${ARCH}, x86_64)
ARCH=			amd64
endif

LNDIR=			${TOOLS_BINDIR}/lndir
LNDIR_FLAGS=
EXTRA_3RDPARTY_DIRS+=
SYSDEP_CPPFLAGS+=
UI_CXXFLAGS+=		${shell ${PKG_CONFIG} --cflags sdl2 SDL2_image}
UI_LDADD+=		${shell ${PKG_CONFIG} --libs sdl2 SDL2_image}
LIB_INCLUDE_BEGIN=	-Wl,--whole-archive
LIB_INCLUDE_END=	-Wl,--no-whole-archive
