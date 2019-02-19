#include "answer_packet.h"
#include <iostream>
#include <cstring>

AnswerPacket::AnswerPacket(unsigned char *data, unsigned long size) {
  this->len   = size;
  this->data  = new unsigned char[size];

  memcpy(this->data, data, size);
  data[size - 1] = '\0';

  this->data_text = string((const char *)(data + 12));
}

AnswerPacket::~AnswerPacket() {
  //delete[] this->data;
}

unsigned char *AnswerPacket::get_data() {
  return data;
}

string AnswerPacket::get_text() {
  return data_text;
}

unsigned long AnswerPacket::get_length() {
  return len;
}
