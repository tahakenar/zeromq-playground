#pragma once

#include <optional>
#include <zmq.hpp>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

class Sub {
 public:
  explicit Sub(const std::string& addr);
  void subscribe();

 private:
  std::optional<Payload> receivePayload();
  PayloadSolution getSolution(const Payload& payload);
  std::string connection_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  util::logger_ptr logger_;
};
