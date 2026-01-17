#include "worker.hpp"

#include <chrono>
#include <thread>

#include "random_generator.hpp"
#include "zeromq_logger.hpp"

Worker::Worker(const std::string &pull_addr, const std::string &push_addr)
    : pull_connection_addr_(pull_addr),
      push_connection_addr_(push_addr),
      context_(1),
      pull_socket_(context_, zmq::socket_type::pull),
      push_socket_(context_, zmq::socket_type::push),
      logger_(util::get_logger(
          std::format("WORKER with pid: {}", getpid()),
          util::LoggerColor(util::get_random_integer(
              0, static_cast<int>(util::LoggerColor::Magenta))))) {
  pull_socket_.connect(pull_addr);
  push_socket_.connect(push_addr);
  logger_->info(std::format("Initialized"));
}

void Worker::connectToPullAndPush() {
  while (true) {
    auto payload = receivePayload();
    if (payload.has_value()) {
      // Sleep for a random period of time
      std::this_thread::sleep_for(
          std::chrono::milliseconds(100 * util::get_random_integer()));
      auto solution = getSolution(payload.value());
      logger_->info(std::format(
          "Payload solution for name: {}, id: {} is "
          "calculated. Will push to sink",
          solution.name(), solution.payload_id(), solution.solution()));
      pushSolution(solution);
    }
  }
}

std::optional<Payload> Worker::receivePayload() {
  zmq::message_t request;
  auto result = pull_socket_.recv(request);

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

PayloadSolution Worker::getSolution(const Payload &payload) {
  PayloadSolution solution;
  solution.set_name(payload.name());
  solution.set_payload_id(payload.payload_id());
  solution.set_solution(payload.left_operand() + payload.right_operand());
  return solution;
}

void Worker::pushSolution(const PayloadSolution &solution) {
  std::string buffer;
  if (!solution.SerializeToString(&buffer)) {
    logger_->error("Failed to serialize payload solution");
  }
  zmq::message_t request(buffer.size());
  memcpy(request.data(), buffer.data(), buffer.size());
  push_socket_.send(request, zmq::send_flags::none);
}