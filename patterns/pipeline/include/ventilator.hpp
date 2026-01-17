#pragma once

#include <zmq.hpp>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

class Ventilator {
 public:
  explicit Ventilator(const std::string& addr);
  void pushPayload(const Payload& payload);

 private:
  std::string bind_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  util::logger_ptr logger_;
};
