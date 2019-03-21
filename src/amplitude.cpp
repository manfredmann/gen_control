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

#include "amplitude.h"

Amplitude::Amplitude::Amplitude(double voltage, voltage_t type) {
  init_map();

  this->type = type;
  this->amp  = voltage;
}

Amplitude::Amplitude::Amplitude(double voltage, string type) {
  init_map();

  bool is_valid = false;

  for (const auto &f : map) {
    if (f.second.compare(type) == 0) {
      this->type = f.first;
      is_valid = true;
      break;
    }
  }

  if (!is_valid) {
    throw AmplitudeException(V_ERR_UNSUPPORTED_TYPE);
  }

  this->amp = voltage;
}

string Amplitude::Amplitude::get_type_str() {
  return map[type];
}

Amplitude::voltage_t Amplitude::Amplitude::get_type() {
  return type;
}

double Amplitude::Amplitude::get_amplitude() {
  return amp;
}

void Amplitude::Amplitude::init_map() {
  map[voltage_t::V_PP]  = "VPP";
  map[voltage_t::V_RMS] = "VRMS";
}
