/*
 * Copyright (C) 2020 Claudio Castiglia
 *
 * This file is part of CEMU.
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
#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "rgb.hpp"
#include "ui_config.hpp"
#include "ui_widget.hpp"


namespace cemu {
namespace ui {

/**
 * Panel.
 * A panel is a widget container.
 * @see Widget
 */
class Panel {
public:
    constexpr static const Rgba BACKGROUND_COLOR   = {0x00, 0x00, 0x00, 0x00};
    constexpr static const Rgba FRAME_COLOR        = {0xFF, 0x00, 0x00, 0xFF};
    constexpr static const uint32_t FRAME_TICKNESS = 2; /* Pixels */

    /**
     * Create a panel.
     * @param is_visible Panel visibility (true if visible; false otherwise).
     */
    Panel(bool is_visible = false)
        : _visible{is_visible} {
    }

    virtual ~Panel() {
    }

    /**
     * Set the panel visibility.
     * @param is_visible Panel visibility (true if visible; false otherwise).
     */
    virtual void visible(bool is_visible) {
        _visible = is_visible;
    }

    /**
     * @return True if the panel is visible; false otherwise.
     */
    bool is_visible() const {
        return _visible;
    }

    /**
     * Add a widget into this panel.
     * @param widget Widget to add.
     */
    void add(const std::shared_ptr<Widget> &widget);

    /**
     * Remove a widget from this panel.
     * @param widget Widget to remove.
     */
    void del(const std::shared_ptr<Widget> &widget);

    /**
     * @return A constant reference to the widgets container.
     */
    const std::vector<std::shared_ptr<Widget>> &widgets() const {
        return _widgets;
    }

private:
    std::vector<std::shared_ptr<Widget>>::const_iterator find(const std::shared_ptr<Widget> &widget) const {
        return std::find(_widgets.begin(), _widgets.end(), widget);
    }

    bool                                 _visible{};
    std::vector<std::shared_ptr<Widget>> _widgets{};
};

}
}