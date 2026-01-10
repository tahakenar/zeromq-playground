#pragma once

#include <zmq.hpp>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

class Req {
 public:
  explicit Req(const std::string& addr);
  void sendPayload(const Payload& payload);
  void getPayloadResponse();

 private:
  std::string connection_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  util::logger_ptr logger_;
};
