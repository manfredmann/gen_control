#include "packet_command.h"
#include <iostream>
#include <cstring>

PacketCommand::PacketCommand(string cmd) {
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

  this->data[0x00] = 0x01;
  this->data[0x04] = static_cast<unsigned char>(cmd.length() + 1);
  memcpy(this->data + 12, cmd.c_str(), cmd.length());

  this->data[12 + cmd.length()] = 0x0A;
}

PacketCommand::~PacketCommand() {
  //delete[] this->data;
}

unsigned long PacketCommand::get_length() {
  return len;
}

string PacketCommand::get_cmd() {
  return cmd;
}

unsigned char *PacketCommand::get_data() {
  return data;
}
