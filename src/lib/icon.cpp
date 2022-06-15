/*
 * Copyright (C) 2020-2022 Claudio Castiglia
 *
 * This file is part of CAIO.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see http://www.gnu.org/licenses/
 */
#include "icon.hpp"

#include <array>

#include "image.hpp"
#include "rgb.hpp"


namespace caio {

constexpr static const unsigned ICON_WIDTH  = 32;
constexpr static const unsigned ICON_HEIGHT = 27;


std::array<Rgba, ICON_WIDTH * ICON_HEIGHT> icon32_data = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffe1e2ff, 0xffcacbff,
    0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff,
    0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff, 0xffcacbff,
    0xffcacbff, 0xffe1e1ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xffffff00, 0xffffff00, 0xffffff00, 0xffffff00, 0xffffff33, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffff0b, 0xffffff0e, 0xffffff0e, 0xffffff0e, 0xffffff0e,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffe3e3ff, 0xffacacff, 0xffacacff, 0xffacacff, 0xffacacff, 0xff7173ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffb8b9ff, 0xffcbccff, 0xffcbccff, 0xffcbccff, 0xffcbccff,
    0xffcbccff, 0xffcbccff, 0xffcbccff, 0xffcbccff, 0xf1b8b8ff, 0xaa0008ff, 0xaa0008ff, 0xaa0008ff,
    0xaa0008ff, 0xaa6e6fff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xaaaaaaff, 0xd3d3d3ff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xffffffec, 0xffffffc8, 0xffffffc8, 0xffffffc8,
    0xffffffc8, 0xffffffc8, 0xffffffc8, 0xffffffea, 0xe6e6e6ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xffffffa8, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xffffff9d, 0xe6e6e6ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xffffffcb, 0xffffff68, 0xffffff68, 0xffffff68,
    0xffffff68, 0xffffff68, 0xffffff68, 0xffffffc5, 0xe6e6e6ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xe6e6e6ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xdededeff, 0x808080ff, 0x808080ff, 0x808080ff,
    0x808080ff, 0x808080ff, 0x808080ff, 0x808080ff, 0x737373ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xd4d4d4ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xd4d4d4ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xd4d4d4ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xadadadff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xd3d3d3ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff,
    0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0x000000ff, 0xacacacff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xffffffe3, 0xffffff66, 0xffffff66, 0xffffff66,
    0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66,
    0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66, 0xffffff66,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xffffffd0, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xffffffff, 0xffcdcdff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffe7e7ff, 0xfffffff6, 0xffffffce, 0xffffffce, 0xffffffce,
    0xffffffce, 0xffffffce, 0xffffffce, 0xffffffce, 0xffffffce, 0xffffffce, 0xffffffce, 0xffffffce,
    0xffffffce, 0xffffffce, 0xffffffce, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xffffffff, 0xffd8d8ff, 0xff7b7cff, 0xff7b7cff, 0xff7b7cff, 0xff7b7cff, 0xff4f52ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xffcfcfff, 0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff,
    0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff, 0xffe4e4ff,
    0xffe4e4ff, 0xffefefff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xffffff0e, 0xffffff0e, 0xffffff0e, 0xffffff0e, 0xffffff40, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffaaaaff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff, 0xff0012ff,
    0xff0012ff, 0xffa8a9ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffd1d1ff, 0xffa9a9ff,
    0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff,
    0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff, 0xffa9a9ff,
    0xffa9a9ff, 0xffd0d0ff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xffffff34, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};


const Image &icon32()
{
    static const Image caio_icon32 = {
        .width  = ICON_WIDTH,
        .height = ICON_HEIGHT,
        .data   = gsl::span{icon32_data.data(), icon32_data.size()}
    };

    return caio_icon32;
}

}
