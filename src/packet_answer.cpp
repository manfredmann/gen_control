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

#include "packet_answer.h"
#include <iostream>
#include <cstring>

PacketAnswer::PacketAnswer(unsigned char *data, unsigned long size) {
  this->len   = size;
  this->data  = new unsigned char[size];

  memcpy(this->data, data, size);
  data[size - 1] = '\0';

  this->data_text = string((const char *)(data + 12));
}

PacketAnswer::~PacketAnswer() {
  //delete[] this->data;
}

unsigned char *PacketAnswer::get_data() {
  return data;
}

string PacketAnswer::get_text() {
  return data_text;
}

unsigned long PacketAnswer::get_length() {
  return len;
}
