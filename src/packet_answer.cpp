#include "packet_answer.h"
#include <iostream>
#include <cstring>

PacketAnswer::PacketAnswer(unsigned char *data, unsigned long size) {
  this->len   = size;
  this->data  = new unsigned char[size];

  memcpy(this->data, data, size);
  data[size - 1] = '\0';

  this->data_text = string((const char *)(data + 12));
}

PacketAnswer::~PacketAnswer() {
  //delete[] this->data;
}

unsigned char *PacketAnswer::get_data() {
  return data;
}

string PacketAnswer::get_text() {
  return data_text;
}

unsigned long PacketAnswer::get_length() {
  return len;
}
