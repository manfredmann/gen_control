#ifndef REQUEST_PACKET_H
#define REQUEST_PACKET_H

#include <cstring>

class RequestPacket {
  public:
    RequestPacket();
    ~RequestPacket();

    unsigned char *get_data();
    unsigned long get_length();

  private:
    unsigned char *data;
    unsigned long size;
};

#endif // REQUEST_PACKET_H
