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
