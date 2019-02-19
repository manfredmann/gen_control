#ifndef PACKET_ANSWER_H
#define PACKET_ANSWER_H

#include <string>

using namespace std;

class PacketAnswer {
  public:
    PacketAnswer(unsigned char *data, unsigned long size);
    ~PacketAnswer();
    unsigned char *get_data();
    string        get_text();
    unsigned long get_length();

  private:
    unsigned char *data;
    string        data_text;
    unsigned long len;
};

#endif // PACKET_ANSWER_H
