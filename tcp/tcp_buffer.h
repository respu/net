#ifndef NET_TCP_BUFFER_H_
#define NET_TCP_BUFFER_H_

#include "base_buffer.h"

namespace net {

const int kAcceptBuffSize = 64;
const int kTcpBufferSize = 64 * 1024;

class TcpSendBuff : public BaseBuffer {
 public:
	TcpSendBuff() {
		ResetBuffer();
	}
	bool set_buffer(int offset, const char* buffer, int size) {
		auto total_size = size + offset;
		if (buffer == nullptr || total_size > sizeof(buffer_)) {
			return false;
		}
		auto current_pos = buffer_ + offset;
		memcpy(current_pos, buffer, size);
		return true;
	}
	void ResetBuffer() {
		BaseBuffer::ResetBuffer();
		set_async_type(kAsyncTypeTcpSend);
	}
	char* buffer() { return buffer_; }

 private:
	char buffer_[kTcpBufferSize];
};

class TcpRecvBuff : public BaseBuffer {
 public:
	TcpRecvBuff() {
		ResetBuffer();
	}
	void ResetBuffer() {
		BaseBuffer::ResetBuffer();
		set_async_type(kAsyncTypeTcpRecv);
		set_buffer_size(sizeof(buffer_));
	}
	char* buffer() { return buffer_; }

 private:
	char buffer_[kTcpBufferSize];
};

class AcceptBuff : public BaseBuffer {
 public:
	AcceptBuff() {
		ResetBuffer();
	}
	void ResetBuffer() {
		BaseBuffer::ResetBuffer();
		set_async_type(kAsyncTypeAccept);
		set_buffer_size(sizeof(buffer_));
		accept_socket_ = nullptr;
	}
	char* buffer() { return buffer_; }
	void set_accept_socket(void* value) { accept_socket_ = value; }
	void* accept_socket() const { return accept_socket_; }

 private:
	char buffer_[kAcceptBuffSize];
	void* accept_socket_;
};

} // namespace net

#endif	// NET_TCP_BUFFER_H_