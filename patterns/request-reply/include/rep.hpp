#pragma once

#include <optional>
#include <zmq.hpp>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

class Rep {
 public:
  explicit Rep(const std::string& addr);
  void start();

 private:
  std::string bind_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  util::logger_ptr logger_;

  std::optional<Payload> receivePayload();
  PayloadSolution getSolution(const Payload& payload);
  void sendPayloadSolution(const PayloadSolution& solution);
};
