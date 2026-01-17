#pragma once

#include <zmq.hpp>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

class Sink {
 public:
  explicit Sink(const std::string& addr);
  void bindToPull();

 private:
  void getPayloadSolution();
  std::string bind_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  util::logger_ptr logger_;
};
