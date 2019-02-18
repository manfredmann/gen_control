#include "amplitude.h"

Amplitude::Amplitude::Amplitude(double voltage, voltage_t type) {
  init_map();

  this->type = type;
  this->amp  = voltage;
}

Amplitude::Amplitude::Amplitude(double voltage, string type) {
  init_map();

  bool is_valid = false;

  for (const auto &f : map) {
    if (f.second.compare(type) == 0) {
      this->type = f.first;
      is_valid = true;
      break;
    }
  }

  if (!is_valid) {
    throw AmplitudeException(V_ERR_UNSUPPORTED_TYPE);
  }

  this->amp = voltage;
}

string Amplitude::Amplitude::get_type_str() {
  return map[type];
}

Amplitude::voltage_t Amplitude::Amplitude::get_type() {
  return type;
}

double Amplitude::Amplitude::get_amplitude() {
  return amp;
}

void Amplitude::Amplitude::init_map() {
  map[voltage_t::V_PP]  = "VPP";
  map[voltage_t::V_RMS] = "VRMS";
}
