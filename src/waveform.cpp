#include "waveform.h"

Waveform::Waveform::Waveform(string val) {
  init_map();
  bool is_valid = false;

  transform(val.begin(), val.end(),val.begin(), ::toupper);

  for (const auto &f : map) {
    if (f.second.compare(val) == 0) {
      waveform = f.first;
      is_valid = true;
      break;
    }
  }

  if (!is_valid) {
    throw WaveformException(WF_ERR_UNSUPPORTED);
  }
}

Waveform::Waveform::Waveform(waveform_t val) {
  init_map();
  waveform = val;
}

Waveform::waveform_t Waveform::Waveform::get_type() {
  return waveform;
}

string Waveform::Waveform::get_type_str() {
  return map[waveform];
}

void Waveform::Waveform::init_map() {
  map[waveform_t::SIN]  = "SIN";
  map[waveform_t::SQU]  = "SQU";
  map[waveform_t::RAMP] = "RAMP";
}
