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
