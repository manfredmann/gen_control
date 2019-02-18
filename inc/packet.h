#ifndef PACKET_H
#define PACKET_H

#include <string>

using namespace std;

class CommandPacket {
  public:
    CommandPacket(unsigned char *data, unsigned long size, string cmd);
    ~CommandPacket();
    unsigned long get_length();
    string        get_cmd();
    unsigned char *get_data();

  private:
    unsigned char *data;
    string        cmd;
    unsigned long len;
};

class AnswerPacket {
  public:
    AnswerPacket(unsigned char *data, unsigned long size);
    ~AnswerPacket();
    unsigned char *get_data();
    string        get_text();
    unsigned long get_length();

  private:
    unsigned char *data;
    string        data_text;
    unsigned long len;
};

#endif // PACKET_H
