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

#include "packet_command.h"
#include <iostream>
#include <cstring>

PacketCommand::PacketCommand(string cmd) {
  len = 12 + cmd.length() + 1;

  while (len % 4 != 0) {
    len++;
  }

  if (len < 20) {
    len = 20;
  }

  this->cmd = cmd;
  this->data = new unsigned char[len];
  fill(this->data, this->data + len, 0);

  this->data[0x00] = 0x01;
  this->data[0x04] = static_cast<unsigned char>(cmd.length() + 1);
  memcpy(this->data + 12, cmd.c_str(), cmd.length());

  this->data[12 + cmd.length()] = 0x0A;
}

PacketCommand::~PacketCommand() {
  //delete[] this->data;
}

unsigned long PacketCommand::get_length() {
  return len;
}

string PacketCommand::get_cmd() {
  return cmd;
}

unsigned char *PacketCommand::get_data() {
  return data;
}
