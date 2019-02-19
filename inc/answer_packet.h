#ifndef ANSWER_PACKET_H
#define ANSWER_PACKET_H

#include <string>

using namespace std;

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

#endif // ANSWER_PACKET_H
