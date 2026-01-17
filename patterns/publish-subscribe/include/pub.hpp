#pragma once

#include <zmq.hpp>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

class Pub {
 public:
  explicit Pub(const std::string& addr);
  void publishPayload(const Payload& payload);

 private:
  std::string bind_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  util::logger_ptr logger_;
};
