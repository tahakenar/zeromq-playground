#pragma once

#include <memory>

#include <zmq.hpp>

#include "zeromq_logger.hpp"

class Req {
public:
  explicit Req(const std::string& addr);
  void sendString(const std::string& msg);
  void getReply();
private:
  std::string connection_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  std::shared_ptr<spdlog::logger> logger_;
};
