#include "packet_request.h"

static unsigned char packet_2_data[] = { 0x02, 0xBE, 0xEF, 0x00, 0xE8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

PacketRequest::PacketRequest() {
  this->size = sizeof(packet_2_data);
  this->data = new unsigned char[this->size];

  memcpy(this->data, packet_2_data, sizeof(packet_2_data));
}

PacketRequest::~PacketRequest() {
  delete[] this->data;
}

unsigned char *PacketRequest::get_data() {
  return this->data;
}

unsigned long PacketRequest::get_length() {
  return this->size;
}
