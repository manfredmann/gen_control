#ifndef COMMAND_PACKET_H
#define COMMAND_PACKET_H

#include <string>

using namespace std;

class CommandPacket {
  public:
    CommandPacket(string cmd);
    ~CommandPacket();
    unsigned long get_length();
    string        get_cmd();
    unsigned char *get_data();

  private:
    unsigned char *data;
    string        cmd;
    unsigned long len;
};

#endif // COMMAND_PACKET_H
