#include "gen.h"

/*
 * ==============================================
 *  Формат пакета 1
 * ==============================================
 *
 * Длина пакета должна быть кратна 4, свободное пространство добивается нулями
 * Байт окончания команды - 0x0A
 *
 * 1      байт - номер в посылке (0x01)
 * 2      байт - счётчик
 * 3      байт - инверсия счётчика
 * 4      байт - 0x00
 * 5      байт - длина команды +1 (Cmd + 0x0A)
 * 6-12   байт - Константа 0x00 0x00 0x00 0x01 0x00 0x00 0x00
 * 13-... байт - Команда
 * ...    байт - 0x0A
 *
 * ===========================================================
 *  Формат пакета 2 (Отправляется в случае запроса параметра)
 * ===========================================================
 *
 * 1    байт - номер в посылке (0x02)
 * 2    байт - счётчик
 * 3    байт - инверсия счётчика
 * 4    байт - 0x00
 * 5    байт - 0xE8 (ХЗ что это)
 * 6    байт - 0x03 (ХЗ что это)
 * 7-12 байт - Константа 0x00 0x00 0x00 0x00 0x00 0x00
 */

#define MAX_PACKET_SIZE     512
#define COUNTER_UP_OFFS     0x01
#define COUNTER_DOWN_OFFS   0x02

string double_to_string(double val) {
  stringstream stream;
  stream << fixed << setprecision(3) << val;

  return stream.str();
}

double exp_to_double(string exp) {
  stringstream s_exp(exp);

  double val;
  s_exp >> val;

  return val;
}

Generator::Generator() {
  srand( static_cast<unsigned int>(time(nullptr)));

  hndl          = nullptr;
  context       = nullptr;
  debug         = false;
  counter_up    = 0x01;
  counter_down  = ~counter_up;
}

Generator::~Generator() {
  if (hndl != nullptr) {
    libusb_close(nullptr);
  }

  if (context != nullptr) {
    libusb_exit(context);
  }
}

void Generator::init() {
  libusb_context *context = nullptr;
  libusb_device **list    = nullptr;

  libusb_init(&context);

  ssize_t devices_count = libusb_get_device_list(context, &list);

  bool is_found = false;

  for (ssize_t i = 0; i < devices_count; ++i) {
    libusb_device *device = list[i];
    libusb_device_descriptor desc;

    int r = libusb_get_device_descriptor(device, &desc);

    if (r != LIBUSB_SUCCESS) {
      throw USBErrors::USBTransferException(r);
    }

    if (desc.idVendor == 0x0957 && desc.idProduct == 0x1507) {
      is_found = true;
      break;
    }
  }

  libusb_free_device_list(list, static_cast<int>(devices_count));

  if (!is_found) {
    throw USBErrors::USBException(-1);
  }

  hndl = libusb_open_device_with_vid_pid(nullptr, 0x0957, 0x1507);

  if (hndl == nullptr) {
    throw USBErrors::USBException(-1);
  }

  if (libusb_kernel_driver_active(hndl, 0)) {
    if (libusb_detach_kernel_driver(hndl, 0) != 0) {
      throw USBErrors::USBException(-2);
    }
  }

  if (libusb_claim_interface(hndl, 0) < 0) {
    throw USBErrors::USBException(-3);
  }

  set_remote();
}

bool Generator::is_init() {
  if (hndl != nullptr) {
    return true;
  } else {
    return false;
  }
}

void Generator::set_debug(bool on) {
  debug = on;
}

int Generator::send_raw_packet(unsigned char *data, unsigned int len) {
  int tr = 0;

  data[COUNTER_UP_OFFS]   = counter_up;
  data[COUNTER_DOWN_OFFS] = counter_down;

  if (debug) {
    printf("Send data. Len: %d\n", len);
    printf("Data: ");
    for (unsigned int i = 0; i < len; ++i) {
      if (i % 8 == 0 && i != 0) {
        printf("\n      ");
      }
      printf("%02X ", data[i]);
    }
  }

  int r  = libusb_bulk_transfer(hndl, ep_in, data, int(len), &tr, 1000);

  if (r != LIBUSB_SUCCESS) {
    throw USBErrors::USBTransferException(r);
  }

  if (debug) {
    printf("\nTransferred %d bytes\n", tr);
  }

  ++counter_up;
  if (counter_up == 0) {
    ++counter_up;
  }

  counter_down = ~counter_up;
  return tr;
}

int Generator::recv_raw_packet(unsigned char *data, unsigned int len) {
  int rcv;

  if (debug)
    printf("Recv data. Len: %d\n", len);

  int r = libusb_bulk_transfer(hndl, ep_out, data, int(len), &rcv, 1000);

  if (r != LIBUSB_SUCCESS) {
    throw USBErrors::USBTransferException(r);
  }

  if (debug) {
    printf("Data: ");
    for (int i = 0; i < rcv; ++i) {
      if (i % 8 == 0 && i != 0) {
        printf("\n      ");
      }
      printf("%02X ", data[i]);
    }
  }

  if (debug) {
    printf("\nReceived %d bytes\n", rcv);
  }

  return rcv;
}

int Generator::send_packet(PacketCommand pack) {
  return send_raw_packet(pack.get_data(), static_cast<unsigned int>(pack.get_length()));
}

int Generator::send_req_packet() {
  PacketRequest pack;
  return send_raw_packet(pack.get_data(), static_cast<unsigned int>(pack.get_length()));
}

void Generator::set_remote() {
  string cmd = "SYST:REMOTE";

  PacketCommand packet_cmd(cmd);
  send_packet(packet_cmd);
}

PacketAnswer Generator::recv_packet() {
  unsigned char *recv = new unsigned char[MAX_PACKET_SIZE];
  fill(recv, recv + MAX_PACKET_SIZE, 0);

  int r = recv_raw_packet(recv, MAX_PACKET_SIZE);
  PacketAnswer packet(recv, static_cast<unsigned long>(r));

  delete[] recv;
  return packet;
}


void Generator::send_cls() {
  string cmd = "*CLS";

  PacketCommand packet_cmd(cmd);
  send_packet(packet_cmd);
}

void Generator::set_text(string text) {
  string cmd = "DISP:TEXT '" + text + "'";

  PacketCommand packet_cmd(cmd);
  send_packet(packet_cmd);
}

string Generator::get_identifier() {
  string cmd = "*IDN?";

  PacketCommand packet(cmd);

  send_packet(packet);
  send_req_packet();

  return recv_packet().get_text();
}

string Generator::get_error() {
  string cmd = "SYST:ERR?";

  PacketCommand packet(cmd);

  send_packet(packet);
  send_req_packet();

  return recv_packet().get_text();
}

Waveform::Waveform Generator::get_waveform() {
  string cmd = "FUNC?";

  PacketCommand packet_cmd(cmd);

  send_packet(packet_cmd);
  send_req_packet();

  return Waveform::Waveform(recv_packet().get_text());
}

void Generator::set_waveform(Waveform::Waveform waveform) {
  string waveform_name = waveform.get_type_str();

  stringstream cmd_ss;
  cmd_ss << "FUNC " << waveform_name;
  string cmd = cmd_ss.str();

  PacketCommand packet_cmd(cmd);

  send_packet(packet_cmd);
}

double Generator::get_frequency() {
  string cmd = "FREQ?";

  PacketCommand packet(cmd);

  send_packet(packet);
  send_req_packet();

  return exp_to_double(recv_packet().get_text());
}

void Generator::set_frequency(unsigned int hz) {
  stringstream cmd_ss;

  cmd_ss << "FREQ " << to_string(hz);
  string cmd = cmd_ss.str();

  PacketCommand packet(cmd);

  send_packet(packet);
}

Amplitude::Amplitude Generator::get_amplitude() {
  string cmd = "VOLT?";

  PacketCommand packet(cmd);

  send_packet(packet);
  send_req_packet();

  double ampl = exp_to_double(recv_packet().get_text());

  return Amplitude::Amplitude(ampl, get_voltage_unit());
}

void Generator::set_unit(string type) {
  string cmd = "VOLT:UNIT " + type;

  PacketCommand packet(cmd);
  send_packet(packet);
}

string Generator::get_voltage_unit() {
  string cmd = "VOLT:UNIT?";

  PacketCommand packet(cmd);
  send_packet(packet);
  send_req_packet();

  return recv_packet().get_text();
}

void Generator::set_amplitude(Amplitude::Amplitude amp) {
  this->set_unit(amp.get_type_str());

  stringstream cmd_ss;
  cmd_ss << "VOLT " << double_to_string(amp.get_amplitude());
  string cmd = cmd_ss.str();

  PacketCommand packet(cmd);

  send_packet(packet);
}

void Generator::set_load(int om) {
  stringstream cmd_ss;
  cmd_ss << "OUTP:LOAD " << to_string(om);
  string cmd = cmd_ss.str();

  PacketCommand packet(cmd);

  send_packet(packet);
}

double Generator::get_load() {
  string cmd = "OUTP:LOAD?";

  PacketCommand packet(cmd);

  send_packet(packet);
  send_req_packet();

  return exp_to_double(recv_packet().get_text());
}

void Generator::set_output(bool on) {
  string        cmd;

  if (on) {
    cmd = "OUTP ON";
  } else {
    cmd = "OUTP OFF";
  }

  PacketCommand packet(cmd);

  send_packet(packet);
}
