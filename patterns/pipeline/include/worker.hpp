#pragma once

#include <zmq.hpp>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

class Worker {
 public:
  explicit Worker(const std::string& pull_addr, const std::string& push_addr);
  void connectToPullAndPush();

 private:
  std::optional<Payload> receivePayload();
  PayloadSolution getSolution(const Payload& payload);
  void pushSolution(const PayloadSolution& solution);

  std::string pull_connection_addr_;
  std::string push_connection_addr_;
  zmq::context_t context_;
  zmq::socket_t pull_socket_;
  zmq::socket_t push_socket_;
  util::logger_ptr logger_;
};
