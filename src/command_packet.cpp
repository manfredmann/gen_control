#include "command_packet.h"
#include <iostream>
#include <cstring>

CommandPacket::CommandPacket(string cmd) {
  len = 12 + cmd.length() + 1;

  while (len % 4 != 0) {
    len++;
  }

  if (len < 20) {
    len = 20;
  }

  this->cmd = cmd;
  this->data = new unsigned char[len];
  fill(this->data, this->data + len, 0);

//  memcpy(this->data, data, size);
  this->data[0x00] = 0x01;
  this->data[0x04] = static_cast<unsigned char>(cmd.length() + 1);
  memcpy(this->data + 12, cmd.c_str(), cmd.length());

  this->data[12 + cmd.length()] = 0x0A;
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
