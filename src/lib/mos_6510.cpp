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
#include "mos_6510.hpp"


namespace cemu {

Mos6510::Mos6510(const std::string &type, const std::string &label)
    : Mos6502{type, label}
{
}

Mos6510::Mos6510(const std::shared_ptr<ASpace> &mmap, const std::string &type, const std::string &label)
    : Mos6502{mmap, type, label}
{
}

Mos6510::~Mos6510()
{
}

void Mos6510::bpadd(addr_t addr, const std::function<void(Mos6510 &, void *)> &cb, void *arg)
{
    Mos6502::bpadd(addr, *reinterpret_cast<const std::function<void(Mos6502 &, void *)> *>(&cb), arg);
}

}