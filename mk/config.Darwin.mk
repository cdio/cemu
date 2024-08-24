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
EXTRA_3RDPARTY_DIRS+=

SYSDEP_CPPFLAGS+=	-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include

LIB_INCLUDE_BEGIN=	-Wl,-all_load
LIB_INCLUDE_END=

UI_CXXFLAGS+=		-I${ROOT}/3rdparty/sdl_image/SDL_image.subtree/include
UI_CXXFLAGS+=		${shell ${SDL2_CONFIG} --cflags}

UI_LDADD+=		${ROOT}/3rdparty/sdl_image/SDL_image/libSDL2_image.a
UI_LDADD+=		${shell ${SDL2_CONFIG} --static-libs}
