#include "req.hpp"

#include <unistd.h>

#include <cstring>
#include <format>

#include "zeromq_logger.hpp"

Req::Req(const std::string& addr)
    : connection_addr_{addr},
      context_(1),
      socket_(context_, zmq::socket_type::req),
      logger_(util::get_logger(std::format("REQ Client with pid: {}", getpid()),
                               util::LoggerColor::Cyan)) {
  logger_->info(std::format("Initialized for address {}", connection_addr_));
  socket_.connect(connection_addr_);
}

void Req::sendString(const std::string& msg) {
  zmq::message_t request(msg.size());
  memcpy(request.data(), msg.data(), msg.size());
  logger_->info(std::format("Sending REQ payload: {}", msg));
  socket_.send(request, zmq::send_flags::none);
}

void Req::getReply() {
  zmq::message_t reply;
  auto res = socket_.recv(reply, zmq::recv_flags::none);
  if (res.has_value()) {
    auto reply_payload = reply.to_string_view();
    logger_->info(std::format("REP payload received: {}", reply_payload));
  }
}
