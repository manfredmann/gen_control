#include "request_packet.h"

static unsigned char packet_2_data[] = { 0x02, 0xBE, 0xEF, 0x00, 0xE8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

RequestPacket::RequestPacket() {
  this->size = sizeof(packet_2_data);
  this->data = new unsigned char[this->size];

  memcpy(this->data, packet_2_data, sizeof(packet_2_data));
}

RequestPacket::~RequestPacket() {
  delete[] this->data;
}

unsigned char *RequestPacket::get_data() {
  return this->data;
}

unsigned long RequestPacket::get_length() {
  return this->size;
}
