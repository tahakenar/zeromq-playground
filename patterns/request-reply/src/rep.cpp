#include "rep.hpp"

#include <chrono>
#include <optional>
#include <thread>

#include "payload.pb.h"
#include "zeromq_logger.hpp"

Rep::Rep(const std::string &addr)
    : bind_addr_(addr),
      context_(2),
      socket_(context_, zmq::socket_type::rep),
      logger_(util::get_logger(std::format("REP Server with pid: {}", getpid()),
                               util::LoggerColor::Magenta)) {
  logger_->info(std::format("Initialized for address {}", bind_addr_));
  socket_.bind(addr);
}

void Rep::start() {
  while (true) {
    auto payload = receivePayload();
    if (payload.has_value()) {
      sendPayloadSolution(getSolution(payload.value()));
    }
  }
}

std::optional<Payload> Rep::receivePayload() {
  zmq::message_t request;
  auto result = socket_.recv(request, zmq::recv_flags::none);

  if (result.value_or(0) != 0) {
    auto payload_as_str = request.to_string();

    Payload payload;
    if (!payload.ParseFromString(payload_as_str.data())) {
      logger_->error("Payload could not be parsed");
      return std::nullopt;
    }

    logger_->info(std::format(
        "REQ received. name: {}, id: {}, left operand: {}, right operand: {}",
        payload.name(), payload.payload_id(), payload.left_operand(),
        payload.right_operand()));

    return std::make_optional(payload);
  }
  return std::nullopt;
}

PayloadSolution Rep::getSolution(const Payload &payload) {
  // Sleep a while
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  PayloadSolution solution;
  solution.set_name(payload.name());
  solution.set_payload_id(payload.payload_id());
  solution.set_solution(payload.left_operand() + payload.right_operand());
  return solution;
}

void Rep::sendPayloadSolution(const PayloadSolution &solution) {
  std::string buffer;
  if (!solution.SerializeToString(&buffer)) {
    logger_->error("Failed to serialize payload solution");
  }
  zmq::message_t request(buffer.size());
  memcpy(request.data(), buffer.data(), buffer.size());
  socket_.send(request, zmq::send_flags::none);
}