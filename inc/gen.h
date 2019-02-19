#ifndef GEN_H
#define GEN_H

#include <libusb-1.0/libusb.h>
#include "errors.h"
#include "waveform.h"
#include "amplitude.h"
#include "command_packet.h"
#include "answer_packet.h"
#include "request_packet.h"
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
    int                   send_packet(CommandPacket pack);
    int                   send_req_packet();

    AnswerPacket          recv_packet();
    unsigned char         *recv_answ(int *recvd);
    void                  set_unit(string type);
    string                get_voltage_unit();
};

#endif // GEN_H
