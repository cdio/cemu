/*
 * Copyright (C) 2020-2022 Claudio Castiglia
 *
 * This file is part of caio.
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
#include "ui_sdl2/widget_volume.hpp"


namespace caio {
namespace ui {
namespace sdl2 {
namespace widget {

#include "icons/volume_128x11.hpp"


Volume::Volume(SDL_Renderer *renderer, const std::function<float()> &getvol, const std::function<void(float)> &setvol)
    : Widget{renderer},
      _getvol{getvol},
      _setvol{setvol}
{
    Widget::load(volume_128x11_png);
}

Volume::~Volume()
{
}

bool Volume::enabled() const
{
    return (_getvol && _setvol);
}

void Volume::event(const SDL_Event &event, const SDL_Rect &rect)
{
    switch (event.type) {
    case SDL_MOUSEWHEEL:
        volume(event.wheel.y * (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL ? 1 : -1));
        break;

    case SDL_MOUSEMOTION:
        if (pressed_widget == this && SDL_GetMouseState(nullptr, nullptr) == ACTION_BUTTON) {
            volume(event.motion.xrel);
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    default:;
    }

    Widget::event(event, rect);
}

void Volume::render(const SDL_Rect &dstrect)
{
    if (_volidx < 0) {
        volume(0);
        _rect.x = 128 * _volidx;
    }

    Widget::render(_rect, dstrect);
}

void Volume::volume(int incr)
{
    if (enabled()) {
        float vol = _getvol();
        int ivol = std::max(0, std::min(10, static_cast<int>(vol * 10.0f)));
        _volidx = std::max(0, std::min(10, ivol + incr));
        _setvol(_volidx / 10.0f);
        _rect.x = 128 * _volidx;
    }
}

}
}
}
}