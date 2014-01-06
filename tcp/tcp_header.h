#ifndef NET_TCP_HEADER_H_
#define NET_TCP_HEADER_H_

#include <WinSock2.h>

namespace net {

const unsigned long kTcpPacketFlag = 0xfdfdfdfd;
const unsigned long kMaxTcpPacketSize = 16 * 1024 * 1024;

class TcpHeader {
 public:
  TcpHeader() {
    packet_flag_ = kTcpPacketFlag;
    packet_size_ = 0;
    checksum_ = 0;
  }
  void Init(unsigned long packet_size) {
    set_packet_size(packet_size);
    ::htonl(packet_flag_);
    ::htonl(packet_size_);
    ::htonl(checksum_);
  }
  bool Init(const char* data, int size) {
    if (data == nullptr || size != sizeof(*this)) {
      return false;
    }
    memcpy(this, data, size);
    ::ntohl(packet_flag_);
    ::ntohl(packet_size_);
    ::ntohl(checksum_);
    if (packet_flag_ != kTcpPacketFlag || packet_size_ > kMaxTcpPacketSize) {
      return false;
    }
    return true;
  }
  operator char*() { return (char*)(this); }
  unsigned long packet_size() { return packet_size_; }
  void set_packet_size(unsigned long value) { packet_size_ = value; }

 private:
  unsigned long packet_flag_;
  unsigned long packet_size_;
  unsigned long checksum_;
};
const int kTcpHeaderSize = sizeof(TcpHeader);

} // namespace net

#endif // NET_TCP_HEADER_H_