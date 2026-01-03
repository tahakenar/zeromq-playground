#pragma once

#include <memory>

#include <zmq.hpp>

#include "zeromq_logger.hpp"

class Rep {
public:
  explicit Rep(const std::string& addr);
  void start();
private:
  std::string bind_addr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
  std::shared_ptr<spdlog::logger> logger_;
};
