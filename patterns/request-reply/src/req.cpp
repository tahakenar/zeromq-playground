#include "req.hpp"

#include <unistd.h>

#include <cstring>
#include <format>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

Req::Req(const std::string &addr)
    : connection_addr_{addr},
      context_(1),
      socket_(context_, zmq::socket_type::req),
      logger_(util::get_logger(std::format("REQ Client with pid: {}", getpid()),
                               util::LoggerColor::Cyan)) {
  logger_->info(std::format("Initialized for address {}", connection_addr_));
  socket_.connect(connection_addr_);
}

void Req::sendPayload(const Payload &payload) {
  std::string buffer;
  if (!payload.SerializeToString(&buffer)) {
    throw std::runtime_error("Failed to serialize payload");
  }
  zmq::message_t request(buffer.size());
  memcpy(request.data(), buffer.data(), buffer.size());
  socket_.send(request, zmq::send_flags::none);
}

void Req::getPayloadResponse() {
  zmq::message_t reply;
  auto res = socket_.recv(reply, zmq::recv_flags::none);
  if (res.has_value()) {
    auto payload_res_as_str = reply.to_string();
    PayloadResponse payload_response;
    if (!payload_response.ParseFromString(payload_res_as_str)) {
      throw std::runtime_error("Failed to parse payload response");
    }
    logger_->info(std::format(
        "REP received. name: {}, id: {}, solution: {}", payload_response.name(),
        payload_response.payload_id(), payload_response.solution()));
  }
}
