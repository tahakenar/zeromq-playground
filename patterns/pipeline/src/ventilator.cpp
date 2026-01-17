#include "ventilator.hpp"

#include <zmq.hpp>

Ventilator::Ventilator(const std::string& addr)
    : bind_addr_(addr),
      context_(1),
      socket_(context_, zmq::socket_type::push),
      logger_(util::get_logger(std::format("VENT with pid: {}", getpid()),
                               util::LoggerColor::Gray)) {
  logger_->info(std::format("Initialized for address {}", bind_addr_));
  socket_.bind(bind_addr_);
}

void Ventilator::pushPayload(const Payload& payload) {
  logger_->info(std::format("Pushing payload. name: {}, id: {}", payload.name(),
                            payload.payload_id()));

  std::string buffer;
  if (!payload.SerializeToString(&buffer)) {
    throw std::runtime_error("Failed to serialize payload");
  }
  zmq::message_t request(buffer.size());
  memcpy(request.data(), buffer.data(), buffer.size());
  socket_.send(request, zmq::send_flags::none);
}
