#include "pub.hpp"

#include <unistd.h>

Pub::Pub(const std::string &addr)
    : bind_addr_(addr),
      context_(2),
      socket_(context_, zmq::socket_type::pub),
      logger_(util::get_logger(std::format("PUB with pid: {}", getpid()),
                               util::LoggerColor::Blue)) {
  logger_->info(std::format("Initialized for address {}", bind_addr_));
  socket_.bind(bind_addr_);
}

void Pub::publishPayload(const Payload &payload) {
  std::string buffer;
  if (!payload.SerializeToString(&buffer)) {
    throw std::runtime_error("Failed to serialize payload");
  }
  zmq::message_t request(buffer.size());
  memcpy(request.data(), buffer.data(), buffer.size());
  socket_.send(request, zmq::send_flags::none);
}