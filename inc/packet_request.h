#ifndef PACKET_REQUEST_H
#define PACKET_REQUEST_H

#include <cstring>

class PacketRequest {
  public:
    PacketRequest();
    ~PacketRequest();

    unsigned char *get_data();
    unsigned long get_length();

  private:
    unsigned char *data;
    unsigned long size;
};

#endif // PACKET_REQUEST_H
