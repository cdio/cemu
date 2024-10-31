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
#include "zxsp_keyboard.hpp"

#include "logger.hpp"
#include "utils.hpp"

namespace caio {
namespace sinclair {
namespace zxspectrum {

using MatrixKey = ZXSpectrumKeyboard::MatrixKey;

std::map<std::string, MatrixKey> ZXSpectrumKeyboard::name_to_spectrum{
    { "KEY_1",          MatrixKey::KEY_1        },
    { "KEY_2",          MatrixKey::KEY_2        },
    { "KEY_3",          MatrixKey::KEY_3        },
    { "KEY_4",          MatrixKey::KEY_4        },
    { "KEY_5",          MatrixKey::KEY_5        },
    { "KEY_6",          MatrixKey::KEY_6        },
    { "KEY_7",          MatrixKey::KEY_7        },
    { "KEY_8",          MatrixKey::KEY_8        },
    { "KEY_9",          MatrixKey::KEY_9        },
    { "KEY_0",          MatrixKey::KEY_0        },

    { "KEY_Q",          MatrixKey::KEY_Q        },
    { "KEY_W",          MatrixKey::KEY_W        },
    { "KEY_E",          MatrixKey::KEY_E        },
    { "KEY_R",          MatrixKey::KEY_R        },
    { "KEY_T",          MatrixKey::KEY_T        },
    { "KEY_Y",          MatrixKey::KEY_Y        },
    { "KEY_U",          MatrixKey::KEY_U        },
    { "KEY_I",          MatrixKey::KEY_I        },
    { "KEY_O",          MatrixKey::KEY_O        },
    { "KEY_P",          MatrixKey::KEY_P        },

    { "KEY_A",          MatrixKey::KEY_A        },
    { "KEY_S",          MatrixKey::KEY_S        },
    { "KEY_D",          MatrixKey::KEY_D        },
    { "KEY_F",          MatrixKey::KEY_F        },
    { "KEY_G",          MatrixKey::KEY_G        },
    { "KEY_H",          MatrixKey::KEY_H        },
    { "KEY_J",          MatrixKey::KEY_J        },
    { "KEY_K",          MatrixKey::KEY_K        },
    { "KEY_L",          MatrixKey::KEY_L        },
    { "ENTER",          MatrixKey::KEY_ENTER    },

    { "KEY_SHIFT",      MatrixKey::KEY_SHIFT    },
    { "KEY_Z",          MatrixKey::KEY_Z        },
    { "KEY_X",          MatrixKey::KEY_X        },
    { "KEY_C",          MatrixKey::KEY_C        },
    { "KEY_V",          MatrixKey::KEY_V        },
    { "KEY_B",          MatrixKey::KEY_B        },
    { "KEY_N",          MatrixKey::KEY_N        },
    { "KEY_M",          MatrixKey::KEY_M        },
    { "KEY_SYMBOL",     MatrixKey::KEY_SYMBOL   },
    { "KEY_SPACE",      MatrixKey::KEY_SPACE    }
};

std::map<std::tuple<keyboard::Key, bool, bool>, std::pair<MatrixKey, bool>> ZXSpectrumKeyboard::default_key_to_spectrum{
    {{ keyboard::KEY_1,             NONE,   NONE    }, { MatrixKey::KEY_1,          NONE    }},
    {{ keyboard::KEY_2,             NONE,   NONE    }, { MatrixKey::KEY_2,          NONE    }},
    {{ keyboard::KEY_3,             NONE,   NONE    }, { MatrixKey::KEY_3,          NONE    }},
    {{ keyboard::KEY_4,             NONE,   NONE    }, { MatrixKey::KEY_4,          NONE    }},
    {{ keyboard::KEY_5,             NONE,   NONE    }, { MatrixKey::KEY_5,          NONE    }},
    {{ keyboard::KEY_6,             NONE,   NONE    }, { MatrixKey::KEY_6,          NONE    }},
    {{ keyboard::KEY_7,             NONE,   NONE    }, { MatrixKey::KEY_7,          NONE    }},
    {{ keyboard::KEY_8,             NONE,   NONE    }, { MatrixKey::KEY_8,          NONE    }},
    {{ keyboard::KEY_9,             NONE,   NONE    }, { MatrixKey::KEY_9,          NONE    }},
    {{ keyboard::KEY_0,             NONE,   NONE    }, { MatrixKey::KEY_0,          NONE    }},

    {{ keyboard::KEY_1,             SHIFT,  NONE    }, { MatrixKey::KEY_1,          SHIFT   }},
    {{ keyboard::KEY_2,             SHIFT,  NONE    }, { MatrixKey::KEY_2,          SHIFT   }},
    {{ keyboard::KEY_3,             SHIFT,  NONE    }, { MatrixKey::KEY_3,          SHIFT   }},
    {{ keyboard::KEY_4,             SHIFT,  NONE    }, { MatrixKey::KEY_4,          SHIFT   }},
    {{ keyboard::KEY_5,             SHIFT,  NONE    }, { MatrixKey::KEY_5,          SHIFT   }},
    {{ keyboard::KEY_6,             SHIFT,  NONE    }, { MatrixKey::KEY_6,          SHIFT   }},
    {{ keyboard::KEY_7,             SHIFT,  NONE    }, { MatrixKey::KEY_7,          SHIFT   }},
    {{ keyboard::KEY_8,             SHIFT,  NONE    }, { MatrixKey::KEY_8,          SHIFT   }},
    {{ keyboard::KEY_9,             SHIFT,  NONE    }, { MatrixKey::KEY_9,          SHIFT   }},
    {{ keyboard::KEY_0,             SHIFT,  NONE    }, { MatrixKey::KEY_0,          SHIFT   }},

    {{ keyboard::KEY_Q,             NONE,   NONE    }, { MatrixKey::KEY_Q,          NONE    }},
    {{ keyboard::KEY_W,             NONE,   NONE    }, { MatrixKey::KEY_W,          NONE    }},
    {{ keyboard::KEY_E,             NONE,   NONE    }, { MatrixKey::KEY_E,          NONE    }},
    {{ keyboard::KEY_R,             NONE,   NONE    }, { MatrixKey::KEY_R,          NONE    }},
    {{ keyboard::KEY_T,             NONE,   NONE    }, { MatrixKey::KEY_T,          NONE    }},
    {{ keyboard::KEY_Y,             NONE,   NONE    }, { MatrixKey::KEY_Y,          NONE    }},
    {{ keyboard::KEY_U,             NONE,   NONE    }, { MatrixKey::KEY_U,          NONE    }},
    {{ keyboard::KEY_I,             NONE,   NONE    }, { MatrixKey::KEY_I,          NONE    }},
    {{ keyboard::KEY_O,             NONE,   NONE    }, { MatrixKey::KEY_O,          NONE    }},
    {{ keyboard::KEY_P,             NONE,   NONE    }, { MatrixKey::KEY_P,          NONE    }},

    {{ keyboard::KEY_Q,             SHIFT,  NONE    }, { MatrixKey::KEY_Q,          SHIFT   }},
    {{ keyboard::KEY_W,             SHIFT,  NONE    }, { MatrixKey::KEY_W,          SHIFT   }},
    {{ keyboard::KEY_E,             SHIFT,  NONE    }, { MatrixKey::KEY_E,          SHIFT   }},
    {{ keyboard::KEY_R,             SHIFT,  NONE    }, { MatrixKey::KEY_R,          SHIFT   }},
    {{ keyboard::KEY_T,             SHIFT,  NONE    }, { MatrixKey::KEY_T,          SHIFT   }},
    {{ keyboard::KEY_Y,             SHIFT,  NONE    }, { MatrixKey::KEY_Y,          SHIFT   }},
    {{ keyboard::KEY_U,             SHIFT,  NONE    }, { MatrixKey::KEY_U,          SHIFT   }},
    {{ keyboard::KEY_I,             SHIFT,  NONE    }, { MatrixKey::KEY_I,          SHIFT   }},
    {{ keyboard::KEY_O,             SHIFT,  NONE    }, { MatrixKey::KEY_O,          SHIFT   }},
    {{ keyboard::KEY_P,             SHIFT,  NONE    }, { MatrixKey::KEY_P,          SHIFT   }},

    {{ keyboard::KEY_A,             NONE,   NONE    }, { MatrixKey::KEY_A,          NONE    }},
    {{ keyboard::KEY_S,             NONE,   NONE    }, { MatrixKey::KEY_S,          NONE    }},
    {{ keyboard::KEY_D,             NONE,   NONE    }, { MatrixKey::KEY_D,          NONE    }},
    {{ keyboard::KEY_F,             NONE,   NONE    }, { MatrixKey::KEY_F,          NONE    }},
    {{ keyboard::KEY_G,             NONE,   NONE    }, { MatrixKey::KEY_G,          NONE    }},
    {{ keyboard::KEY_H,             NONE,   NONE    }, { MatrixKey::KEY_H,          NONE    }},
    {{ keyboard::KEY_J,             NONE,   NONE    }, { MatrixKey::KEY_J,          NONE    }},
    {{ keyboard::KEY_K,             NONE,   NONE    }, { MatrixKey::KEY_K,          NONE    }},
    {{ keyboard::KEY_L,             NONE,   NONE    }, { MatrixKey::KEY_L,          NONE    }},
    {{ keyboard::KEY_ENTER,         NONE,   NONE    }, { MatrixKey::KEY_ENTER,      NONE    }},

    {{ keyboard::KEY_A,             SHIFT,  NONE    }, { MatrixKey::KEY_A,          SHIFT   }},
    {{ keyboard::KEY_S,             SHIFT,  NONE    }, { MatrixKey::KEY_S,          SHIFT   }},
    {{ keyboard::KEY_D,             SHIFT,  NONE    }, { MatrixKey::KEY_D,          SHIFT   }},
    {{ keyboard::KEY_F,             SHIFT,  NONE    }, { MatrixKey::KEY_F,          SHIFT   }},
    {{ keyboard::KEY_G,             SHIFT,  NONE    }, { MatrixKey::KEY_G,          SHIFT   }},
    {{ keyboard::KEY_H,             SHIFT,  NONE    }, { MatrixKey::KEY_H,          SHIFT   }},
    {{ keyboard::KEY_J,             SHIFT,  NONE    }, { MatrixKey::KEY_J,          SHIFT   }},
    {{ keyboard::KEY_K,             SHIFT,  NONE    }, { MatrixKey::KEY_K,          SHIFT   }},
    {{ keyboard::KEY_L,             SHIFT,  NONE    }, { MatrixKey::KEY_L,          SHIFT   }},
    {{ keyboard::KEY_ENTER,         SHIFT,  NONE    }, { MatrixKey::KEY_ENTER,      SHIFT   }},

    {{ keyboard::KEY_LEFT_SHIFT,    NONE,   NONE    }, { MatrixKey::KEY_SHIFT,      NONE    }},
    {{ keyboard::KEY_RIGHT_SHIFT,   NONE,   NONE    }, { MatrixKey::KEY_SHIFT,      NONE    }},
    {{ keyboard::KEY_LEFT_CTRL,     NONE,   NONE    }, { MatrixKey::KEY_SYMBOL,     NONE    }},
    {{ keyboard::KEY_RIGHT_CTRL,    NONE,   NONE    }, { MatrixKey::KEY_SYMBOL,     NONE    }},
    {{ keyboard::KEY_Z,             NONE,   NONE    }, { MatrixKey::KEY_Z,          NONE    }},
    {{ keyboard::KEY_X,             NONE,   NONE    }, { MatrixKey::KEY_X,          NONE    }},
    {{ keyboard::KEY_C,             NONE,   NONE    }, { MatrixKey::KEY_C,          NONE    }},
    {{ keyboard::KEY_V,             NONE,   NONE    }, { MatrixKey::KEY_V,          NONE    }},
    {{ keyboard::KEY_B,             NONE,   NONE    }, { MatrixKey::KEY_B,          NONE    }},
    {{ keyboard::KEY_N,             NONE,   NONE    }, { MatrixKey::KEY_N,          NONE    }},
    {{ keyboard::KEY_M,             NONE,   NONE    }, { MatrixKey::KEY_M,          NONE    }},
    {{ keyboard::KEY_SPACE,         NONE,   NONE    }, { MatrixKey::KEY_SPACE,      NONE    }},

    {{ keyboard::KEY_LEFT_CTRL,     SHIFT,  NONE    }, { MatrixKey::KEY_SYMBOL,     SHIFT   }},
    {{ keyboard::KEY_RIGHT_CTRL,    SHIFT,  NONE    }, { MatrixKey::KEY_SYMBOL,     SHIFT   }},
    {{ keyboard::KEY_Z,             SHIFT,  NONE    }, { MatrixKey::KEY_Z,          SHIFT   }},
    {{ keyboard::KEY_X,             SHIFT,  NONE    }, { MatrixKey::KEY_X,          SHIFT   }},
    {{ keyboard::KEY_C,             SHIFT,  NONE    }, { MatrixKey::KEY_C,          SHIFT   }},
    {{ keyboard::KEY_V,             SHIFT,  NONE    }, { MatrixKey::KEY_V,          SHIFT   }},
    {{ keyboard::KEY_B,             SHIFT,  NONE    }, { MatrixKey::KEY_B,          SHIFT   }},
    {{ keyboard::KEY_N,             SHIFT,  NONE    }, { MatrixKey::KEY_N,          SHIFT   }},
    {{ keyboard::KEY_M,             SHIFT,  NONE    }, { MatrixKey::KEY_M,          SHIFT   }},
    {{ keyboard::KEY_SPACE,         SHIFT,  NONE    }, { MatrixKey::KEY_SPACE,      SHIFT   }},

    {{ keyboard::KEY_BACKSPACE,     NONE,   NONE    }, { MatrixKey::KEY_0,          SHIFT   }},
    {{ keyboard::KEY_CURSOR_LEFT,   NONE,   NONE    }, { MatrixKey::KEY_5,          SHIFT   }},
    {{ keyboard::KEY_CURSOR_RIGHT,  NONE,   NONE    }, { MatrixKey::KEY_8,          SHIFT   }},
    {{ keyboard::KEY_CURSOR_UP,     NONE,   NONE    }, { MatrixKey::KEY_7,          SHIFT   }},
    {{ keyboard::KEY_CURSOR_DOWN,   NONE,   NONE    }, { MatrixKey::KEY_6,          SHIFT   }}
};

ZXSpectrumKeyboard::MatrixKey ZXSpectrumKeyboard::to_spectrum(const std::string& name)
{
    auto it = name_to_spectrum.find(name);
    return (it == name_to_spectrum.end() ? MatrixKey::KEY_NONE : it->second);
}

ZXSpectrumKeyboard::ZXSpectrumKeyboard(bool enabled)
    : ZXSpectrumKeyboard{LABEL, enabled}
{
}

ZXSpectrumKeyboard::ZXSpectrumKeyboard(std::string_view label, bool enabled)
    : Keyboard{label, enabled},
      _key_to_spectrum{default_key_to_spectrum}
{
    _matrix.fill(0);
}

ZXSpectrumKeyboard::~ZXSpectrumKeyboard()
{
}

void ZXSpectrumKeyboard::reset()
{
    std::lock_guard<std::mutex> lock{_matrix_mutex};
    _matrix.fill(0);
}

void ZXSpectrumKeyboard::pressed(keyboard::Key key)
{
    std::lock_guard<std::mutex> lock{_matrix_mutex};

    if (key == keyboard::KEY_LEFT_SHIFT || key == keyboard::KEY_RIGHT_SHIFT) {
        _shift_pressed = _shift = true;
        set_matrix(MatrixKey::KEY_SHIFT, true);

    } else {
        std::tuple pc_key{key, _shift_pressed, _altgr_pressed};
        auto it = _key_to_spectrum.find(pc_key);
        if (it != _key_to_spectrum.end()) {
            auto [spectrum_key, spectrum_shifted] = it->second;
            set_matrix(MatrixKey::KEY_SHIFT, spectrum_shifted);
            set_matrix(spectrum_key, true);
            _prev_keys.push_back(std::move(pc_key));
        }
    }
}

void ZXSpectrumKeyboard::released(keyboard::Key key)
{
    std::lock_guard<std::mutex> lock{_matrix_mutex};

    if (key == keyboard::KEY_LEFT_SHIFT || key == keyboard::KEY_RIGHT_SHIFT) {
        _shift = _shift_pressed = false;
        set_matrix(MatrixKey::KEY_SHIFT, false);

    } else if (key == keyboard::KEY_ALT_GR) {
        _altgr_pressed = false;

    } else {
        auto pc_key = std::find_if(_prev_keys.begin(), _prev_keys.end(),
            [&key](const std::tuple<keyboard::Key, bool, bool>& elem) -> bool {
                return (std::get<0>(elem) == key);
        });

        if (pc_key != _prev_keys.end()) {
            auto it = _key_to_spectrum.find(*pc_key);
            if (it != _key_to_spectrum.end()) {
                auto [spectrum_key, _] = it->second;
                set_matrix(spectrum_key, false);
                set_matrix(MatrixKey::KEY_SHIFT, _shift);
                _prev_keys.erase(pc_key);
            }
        }
    }
}

uint8_t ZXSpectrumKeyboard::read()
{
    std::lock_guard<std::mutex> lock{_matrix_mutex};
    uint8_t col = (_scanrow >= std::size(_matrix) ? 0 : _matrix[_scanrow]);
    return (~col);
}

void ZXSpectrumKeyboard::write(uint8_t row)
{
    _scanrow = 255;
    for (uint8_t bit = 0; bit < 8; ++bit) {
        if ((row & (1 << bit)) == 0) {
            _scanrow = bit;
            break;
        }
    }
}

void ZXSpectrumKeyboard::add_key_map(const std::string& key_name, bool key_shift, bool key_altgr,
    const std::string& impl_name, bool impl_shift)
{
    auto key = keyboard::to_key(key_name);
    if (key == keyboard::KEY_NONE) {
        throw InvalidArgument{"Invalid key name: \"" + key_name + "\""};
    }

    MatrixKey impl_key = to_spectrum(impl_name);
    if (impl_key == MatrixKey::KEY_NONE) {
        throw InvalidArgument{"Invalid ZXSpectrum key name: \"" + impl_name + "\""};
    }

    std::tuple pc_key{key, key_shift, key_altgr};
    std::pair spectrum_key{impl_key, impl_shift};

    auto it = _key_to_spectrum.emplace(pc_key, spectrum_key);
    if (it.second == false) {
        /* Replace the existing definition */
        it.first->second = spectrum_key;

        log.warn("ZXSpectrumKeyboard: Key redefined: {}{}{}. Previous value has been replaced\n", key_name,
            (key_shift ? " SHIFT" : ""), (key_altgr ? " ALTGR" : ""));
    }
}

void ZXSpectrumKeyboard::clear_key_map()
{
    _key_to_spectrum.clear();
}

void ZXSpectrumKeyboard::set_matrix(MatrixKey key, bool set)
{
    if (key != MatrixKey::KEY_NONE) {
        uint8_t row = static_cast<uint16_t>(key) >> 8;
        uint8_t col = static_cast<uint16_t>(key) & 0xFF;
        if (row < _matrix.size()) {
            if (set) {
                _matrix[row] |= col;
            } else {
                _matrix[row] &= ~col;
            }
        }
    }
}

}
}
}
