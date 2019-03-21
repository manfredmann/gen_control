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

#include "packet_request.h"

static unsigned char packet_2_data[] = { 0x02, 0xBE, 0xEF, 0x00, 0xE8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

PacketRequest::PacketRequest() {
  this->size = sizeof(packet_2_data);
  this->data = new unsigned char[this->size];

  memcpy(this->data, packet_2_data, sizeof(packet_2_data));
}

PacketRequest::~PacketRequest() {
  delete[] this->data;
}

unsigned char *PacketRequest::get_data() {
  return this->data;
}

unsigned long PacketRequest::get_length() {
  return this->size;
}
