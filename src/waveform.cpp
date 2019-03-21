/*
 * Generator control tool
 *
 * Copyright 2019 by Roman Serov <roman@serov.co>
 *
 * This file is part of Generator control tool.
 *
 * Generator control tool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Generator control tool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Generator control tool. If not, see <http://www.gnu.org/licenses/>.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*/

#include "waveform.h"

Waveform::Waveform::Waveform(string val) {
  init_map();
  bool is_valid = false;

  transform(val.begin(), val.end(),val.begin(), ::toupper);

  for (const auto &f : map) {
    if (f.second.compare(val) == 0) {
      waveform = f.first;
      is_valid = true;
      break;
    }
  }

  if (!is_valid) {
    throw WaveformException(WF_ERR_UNSUPPORTED);
  }
}

Waveform::Waveform::Waveform(waveform_t val) {
  init_map();
  waveform = val;
}

Waveform::waveform_t Waveform::Waveform::get_type() {
  return waveform;
}

string Waveform::Waveform::get_type_str() {
  return map[waveform];
}

void Waveform::Waveform::init_map() {
  map[waveform_t::SIN]  = "SIN";
  map[waveform_t::SQU]  = "SQU";
  map[waveform_t::RAMP] = "RAMP";
}
