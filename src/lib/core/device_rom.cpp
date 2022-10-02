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
#include "device_rom.hpp"

#include <fstream>

#include "logger.hpp"


namespace caio {

DeviceROM::DeviceROM(const std::string &label, const std::vector<uint8_t> &data)
    : Device{TYPE, label},
      _data(data)
{
}

DeviceROM::DeviceROM(const std::vector<uint8_t> &data)
    : DeviceROM{{}, data}
{
}

DeviceROM::DeviceROM(const std::string &fname, size_t size)
    : DeviceROM{fname, {}, size}
{
}

DeviceROM::DeviceROM(const std::string &fname, const std::string &label, size_t size)
    : Device{TYPE, label}
{
    std::ifstream is{fname, std::ios::binary | std::ios::in};
    if (!is) {
        throw IOError{*this, "Can't open: " + fname + ": " + Error::to_string()};
    }

    std::vector<uint8_t> data(std::istreambuf_iterator<char>{is}, {});
    if (size && data.size() != size) {
        throw IOError{*this, "Size is " + std::to_string(data.size()) + ", it must be " + std::to_string(size)};
    }

    _data = std::move(data);
}

DeviceROM::DeviceROM(std::istream &is, size_t size)
    : Device{TYPE, {}}
{
    if (!is) {
        throw IOError{*this, "Invalid input stream"};
    }

    if (size) {
        std::vector<uint8_t> data(size);

        if (!is.read(reinterpret_cast<char *>(&data[0]), size)) {
            throw IOError{*this, "Input stream exausted"};
        }

        _data = std::move(data);
    }
}

void DeviceROM::reset()
{
}

size_t DeviceROM::size() const
{
    return _data.size();
}

uint8_t DeviceROM::read(addr_t addr) const
{
    if (addr < _data.size()) {
        return _data[addr];
    }

    throw InvalidReadAddress{*this, addr};
}

void DeviceROM::write(addr_t addr, uint8_t data)
{
    log.warn("%s(%s): Write attempt, address $%04x, data $%02x\n",
        type().c_str(), label().c_str(), addr, data);
}

std::ostream &DeviceROM::dump(std::ostream &os, addr_t base) const
{
    return utils::dump(os, _data, base);
}

}