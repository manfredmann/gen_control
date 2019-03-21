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

#ifndef GEN_H
#define GEN_H

#include <libusb-1.0/libusb.h>
#include "errors.h"
#include "waveform.h"
#include "amplitude.h"
#include "packet_command.h"
#include "packet_answer.h"
#include "packet_request.h"
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

class Generator {
  public:
    Generator();
    ~Generator();

    void                  init();
    bool                  is_init();
    void                  set_debug(bool on);
    string                get_identifier();
    string                get_error();
    Waveform::Waveform    get_waveform();
    void                  set_waveform(Waveform::Waveform waveform);
    double                get_frequency();
    void                  set_frequency(unsigned int hz);
    Amplitude::Amplitude  get_amplitude();
    void                  set_amplitude(Amplitude::Amplitude amp);
    void                  set_load(int om);
    double                get_load();
    void                  set_output(bool on);
    void                  send_cls();
    void                  set_text(string text);

  private:
    libusb_device_handle  *hndl;
    libusb_context        *context;
    const unsigned char   ep_out = 0x86;
    const unsigned char   ep_in  = 0x02;
    bool                  debug;
    unsigned char         counter_up;
    unsigned char         counter_down;

    int                   send_raw_packet(unsigned char *data, unsigned int len);
    int                   recv_raw_packet(unsigned char *data, unsigned int len);
    int                   send_packet(PacketCommand pack);
    int                   send_req_packet();
    void                  set_remote();

    PacketAnswer          recv_packet();
    unsigned char         *recv_answ(int *recvd);
    void                  set_unit(string type);
    string                get_voltage_unit();
};

#endif // GEN_H
