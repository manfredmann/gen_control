#ifndef PACKET_COMMAND_H
#define PACKET_COMMAND_H

#include <string>

using namespace std;

class PacketCommand {
  public:
    PacketCommand(string cmd);
    ~PacketCommand();
    unsigned long get_length();
    string        get_cmd();
    unsigned char *get_data();

  private:
    unsigned char *data;
    string        cmd;
    unsigned long len;
};

#endif // PACKET_COMMAND_H
