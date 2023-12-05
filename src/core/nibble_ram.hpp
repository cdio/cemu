/*
 * Copyright (C) 2020 Claudio Castiglia
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
#pragma once

#include "ram.hpp"


namespace caio {

/**
 * Nibble RAM.
 * The lower nibble of a byte can be set; the higher nibble of a byte is fixed to 1111b.
 */
class NibbleRAM : public RAM {
public:
    constexpr static const char* TYPE = "4-BIT RAM";

    NibbleRAM(size_t size, const std::string& label)
        : RAM{size, label} {
        type(TYPE);
    }

    virtual ~NibbleRAM() {
    }

    /**
     * @see RAM::write()
     */
    void write(addr_t addr, uint8_t value) override {
        RAM::write(addr, 0xF0 | value);
    }
};

}
