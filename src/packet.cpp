#include "packet.h"
#include <iostream>
#include <cstring>

CommandPacket::CommandPacket(unsigned char *data, unsigned long size, string cmd) {
  len = size + cmd.length() + 1;

  while (len % 4 != 0) {
    len++;
  }

  if (len < 20) {
    len = 20;
  }
  this->cmd = cmd;
  this->data = new unsigned char[len];
  fill(this->data, this->data + len, 0);

  memcpy(this->data, data, size);
  this->data[0x04] = static_cast<unsigned char>(cmd.length() + 1);

 // cout << cmd.length() << endl;
  memcpy(this->data + size, cmd.c_str(), cmd.length());

  this->data[size + cmd.length() + 1] = 0x0A;
}

CommandPacket::~CommandPacket() {
  //delete[] this->data;
}

unsigned long CommandPacket::get_length() {
  return len;
}

string CommandPacket::get_cmd() {
  return cmd;
}

unsigned char *CommandPacket::get_data() {
  return data;
}

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
