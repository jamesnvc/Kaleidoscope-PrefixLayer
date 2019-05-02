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

#include <Kaleidoscope-PrefixLayer.h>

#define isModifier(key) (key.raw >= Key_LeftControl.raw && key.raw <= Key_RightGui.raw)

namespace kaleidoscope {
namespace plugin {

const PrefixLayer::dict_t *PrefixLayer::dict;

const static PrefixLayer::dict_t defaultmap[] PROGMEM = { {0xFFFF, {Key_NoKey}} };

PrefixLayer::PrefixLayer() {
  dict = defaultmap;
}

EventHandlerResult PrefixLayer::onKeyswitchEvent(Key &mapped_key, byte row, byte col, uint8_t keyState) {
  if (keyState & INJECTED || isModifier(mapped_key)) {
    return EventHandlerResult::OK;
  }

  if (keyToggledOn(keyState) && mapped_key.raw <= kaleidoscope::ranges::FIRST) {
    for (uint8_t i = 0;; i++) {
      uint16_t layer = pgm_read_word(&(dict[i].layer));
      if (layer == 0xFFFF) break;
      if (Layer.isActive(layer)) {
        for (uint8_t j = 0;; j++) {
          Key k;
          k.raw = pgm_read_word(&(dict[i].prefix_seq[j].raw));
          if (k.raw == Key_NoKey.raw) break;
          handleKeyswitchEvent(k, UNKNOWN_KEYSWITCH_LOCATION,
                               IS_PRESSED | INJECTED);
        }
        hid::sendKeyboardReport();
        for (uint8_t j = 0;; j++) {
          Key k;
          k.raw = pgm_read_word(&(dict[i].prefix_seq[j].raw));
          if (k.raw == Key_NoKey.raw) break;
          handleKeyswitchEvent(k, UNKNOWN_KEYSWITCH_LOCATION,
                               WAS_PRESSED | INJECTED);
        }
        hid::sendKeyboardReport();
      }
    }
  }

  return EventHandlerResult::OK;
}

}
}

kaleidoscope::plugin::PrefixLayer PrefixLayer;
