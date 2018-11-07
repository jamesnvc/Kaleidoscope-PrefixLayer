/* -*- mode: c++ -*-
 * Kaleidoscope-PrefixLayer - prefix every key in a layer with some key combo
 * Copyright (C) 2017  James Cash
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-Ranges.h>
#include <kaleidoscope/hid.h>


#define PREFIX_MAX_SEQUENCE_LENGTH 4

#define PREFIX_SEQ(...) { __VA_ARGS__, Key_NoKey }
#define PREFIX_DICT(...) { __VA_ARGS__, {0xFFFF, {Key_NoKey}}}

namespace kaleidoscope {
namespace plugin {
class PrefixLayer : public kaleidoscope::Plugin {
  public:
   typedef struct {
     uint16_t layer;
     Key prefix_seq[PREFIX_MAX_SEQUENCE_LENGTH + 1];
   } dict_t;

   PrefixLayer(void);

   static const dict_t *dict;

   EventHandlerResult onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t keyState);
};
};
};

extern kaleidoscope::plugin::PrefixLayer PrefixLayer;
