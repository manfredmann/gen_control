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

#ifndef PACKET_ANSWER_H
#define PACKET_ANSWER_H

#include <string>

using namespace std;

class PacketAnswer {
  public:
    PacketAnswer(unsigned char *data, unsigned long size);
    ~PacketAnswer();
    unsigned char *get_data();
    string        get_text();
    unsigned long get_length();

  private:
    unsigned char *data;
    string        data_text;
    unsigned long len;
};

#endif // PACKET_ANSWER_H
