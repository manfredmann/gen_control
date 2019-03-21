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

#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <string>
#include <map>
#include <algorithm>

using namespace std;

namespace Waveform {
  typedef enum { SIN, SQU, RAMP }     waveform_t ;
  typedef enum { WF_ERR_UNSUPPORTED } waveform_error_t;
  typedef map<waveform_t, string>     waveform_map_t;

  class Waveform {
    public:
      Waveform(string val);
      Waveform(waveform_t val);

      waveform_t get_type();
      string     get_type_str();

    private:
      waveform_map_t map;
      waveform_t     waveform;

      void       init_map();
  };

  class WaveformException {
    public:
      WaveformException(waveform_error_t err) {
        switch (err) {
          case WF_ERR_UNSUPPORTED: {
            msg = "Unsupported waveform";
            break;
          }
        }
      }
      string getError() {
        return msg;
      }
    private:
      string msg;
  };
}


#endif // WAVEFORM_H
