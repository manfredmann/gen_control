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

#ifndef AMPLITUDE_H
#define AMPLITUDE_H

#include <string>
#include <map>

using namespace std;

namespace Amplitude {
  typedef enum {V_PP, V_RMS }               voltage_t;
  typedef enum { V_ERR_UNSUPPORTED_TYPE }   voltage_error_t;
  typedef map<voltage_t, string>            voltage_map_t;

  class Amplitude {
    public:
      Amplitude(double voltage, voltage_t type);
      Amplitude(double voltage, string type);

      string        get_type_str();
      voltage_t     get_type();
      double        get_amplitude();
    private:
      voltage_t     type;
      voltage_map_t map;
      double        amp;

      void          init_map();
  };

  class AmplitudeException {
    public:
      AmplitudeException(voltage_error_t err) {
        switch (err) {
          case V_ERR_UNSUPPORTED_TYPE: {
            msg = "Unsupported type";
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

#endif // AMPLITUDE_H
