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
#include "c64_cart_zaxxon.hpp"

#include "logger.hpp"

#define CART_ZAXXON_DEBUG

#ifdef CART_ZAXXON_DEBUG
#define DEBUG(args...)      log.debug(args)
#else
#define DEBUG(args...)
#endif

namespace caio {
namespace commodore {
namespace c64 {

void CartZaxxon::reset()
{
    /*
     * Cartridge Zaxxon, Super Zaxxon (SEGA)
     *
     * Type     Size    Game    EXROM   LOAD ADDRESS
     * ----------------------------------------------------------------------
     *          20KiB   0       0       $8000-8FFF (Mirrored in $9000-$9FFF)
     *                                  $A000-BFFF
     *
     * The (Super) Zaxxon carts use a 4Kb ($1000) ROM at $8000-$8FFF (mirrored
     * in $9000-$9FFF) along with two 8Kb ($2000) cartridge banks  located  at
     * $A000-$BFFF. One of the two banks is selected by doing a read access to
     * either the $8000-$8FFF area (bank 0 is selected) or to $9000-$9FFF area
     * (bank 1 is selected). EXROM ($18 = $00) and GAME ($19 = $00) lines  are
     * always pulled to GND to select the 16 kB ROM configuration.
     *
     * The CRT file includes three CHIP blocks:
     * a) bank = 0, load address = $8000, size = $1000
     * b) bank = 0, load address = $A000, size = $2000
     * c) bank = 1, load address = $A000, size = $2000
     *
     * @see https://ist.uwaterloo.ca/~schepers/formats/CRT.TXT
     */
    Cartridge::reset();

    const auto& cart = crt();

    if (cart.chips() != TOTAL_ROMS) {
        throw_invalid_cartridge("Invalid number of chips");
    }

    for (size_t entry = 0; entry < cart.chips(); ++entry) {
        const auto& [chip, rom] = cart[entry];

        if (chip.type != Crt::CHIP_TYPE_ROM) {
            throw_invalid_cartridge(entry, "Invalid ROM type {}", chip.type);
        }

        DEBUG("{}({}): Chip entry {}: ROM device, bank {}, load address ${:04X}, size {}\n",
            type(), name(), entry, chip.bank, chip.addr, rom->size());

        if (chip.addr == ROML_BASE_ADDR) {
            /*
             * 4K ROML.
             */
            if (chip.rsiz != ROML_SIZE) {
                throw_invalid_cartridge(entry, "Invalid ROML size {}", chip.rsiz);
            }

            /*
             * Create a mirrored 8K ROM.
             */
            auto ram = std::make_shared<RAM>(rom->label(), 2 * rom->size());
            std::copy_n(static_pointer_cast<ROM>(rom)->begin(), rom->size(), ram->begin());
            std::copy_n(ram->begin(), rom->size(), ram->begin() + rom->size());
            _roml = static_pointer_cast<ROM>(ram);
            _roml->read_observer([this](size_t addr, ReadMode mode) { roml_read_observer(addr, mode); });

        } else if (chip.addr == ROMH_BASE_ADDR) {
            /*
             * 8K ROMH.
             */
            if (chip.rsiz != ROMH_SIZE) {
                throw_invalid_cartridge(entry, "Invalid ROMH size {}", chip.rsiz);
            }

            if (chip.bank > ROMH_BANKS) {
                throw_invalid_cartridge(entry, "Invalid ROMH bank {}", chip.bank);
            }

            _romsh[chip.bank] = static_pointer_cast<ROM>(rom);
        }
    }

    /*
     * Propagate GAME and EXROM output pins.
     */
    _bank = 0;
    mode(MODE_16K);
    propagate(true);    /* Force propagation of mode */
}

uint8_t CartZaxxon::dev_read(size_t, ReadMode)
{
    return 255;
}

void CartZaxxon::dev_write(size_t, uint8_t)
{
}

void CartZaxxon::roml_read_observer(size_t addr, ReadMode mode)
{
    /*
     * Bank selection:
     *   Bank 0: Read access to $8000-$8FFF
     *   Bank 1: Read access to $9000-$9FFF
     */
    _bank = (addr >= ROML_SIZE);
}

std::string CartZaxxon::to_string() const
{
    return std::format("{}, roml: {}; romh bank 0: {}; romh bank 1: {}",
        Name::to_string(),
        _roml->to_string(),
        _romsh[0]->to_string(),
        _romsh[1]->to_string());
}

std::pair<ASpace::devmap_t, ASpace::devmap_t> CartZaxxon::getdev(addr_t addr, bool romh, bool roml)
{
    if (roml) {
       return {{_roml, addr - ROML_BASE_ADDR}, {}};
    }

    if (romh) {
        return {{_romsh[_bank], addr - ROMH_BASE_ADDR}, {}};
    }

    return {{}, {}};
}

size_t CartZaxxon::cartsize() const
{
    return (ROML_SIZE + ROMH_BANKS * ROMH_SIZE);
}

}
}
}
