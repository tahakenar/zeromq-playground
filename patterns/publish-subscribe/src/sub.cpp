#include "sub.hpp"

#include <zmq.hpp>

Sub::Sub(const std::string &addr)
    : connection_addr_(addr),
      context_(1),
      socket_(context_, zmq::socket_type::sub),
      logger_(util::get_logger(std::format("SUB with pid: {}", getpid()),
                               util::LoggerColor::Magenta)) {
  socket_.connect(connection_addr_);
  logger_->info(std::format("Initialized for address {}", connection_addr_));
}

void Sub::subscribe() {
  socket_.set(zmq::sockopt::subscribe, "");
  while (true) {
    auto payload = receivePayload();
    if (payload.has_value()) {
      auto solution = getSolution(payload.value());

      logger_->info(std::format("Solution for name: {}, id: {} is: {}",
                                solution.name(), solution.payload_id(),
                                solution.solution()));
    }
  }
}

std::optional<Payload> Sub::receivePayload() {
  zmq::message_t request;
  auto result = socket_.recv(request, zmq::recv_flags::none);

  if (result.value_or(0) != 0) {
    auto payload_as_str = request.to_string();

    Payload payload;
    if (!payload.ParseFromString(payload_as_str.data())) {
      logger_->error("Payload could not be parsed");
      return std::nullopt;
    }

    logger_->info(
        std::format("Received payload: name: {}, id: {}, left "
                    "operand: {}, right operand: {}",
                    payload.name(), payload.payload_id(),
                    payload.left_operand(), payload.right_operand()));

    return std::make_optional(payload);
  }
  return std::nullopt;
}

PayloadSolution Sub::getSolution(const Payload &payload) {
  PayloadSolution solution;
  solution.set_name(payload.name());
  solution.set_payload_id(payload.payload_id());
  solution.set_solution(payload.left_operand() + payload.right_operand());
  return solution;
}
