#include "sink.hpp"

Sink::Sink(const std::string& addr)
    : bind_addr_(addr),
      context_(1),
      socket_(context_, zmq::socket_type::pull),
      logger_(util::get_logger(std::format("SINK with pid: {}", getpid()),
                               util::LoggerColor::BrightCyan)) {
  logger_->info(std::format("Initialized for address {}", bind_addr_));
  socket_.bind(bind_addr_);
}

void Sink::bindToPull() {
  while (true) {
    getPayloadSolution();
  }
}

void Sink::getPayloadSolution() {
  zmq::message_t reply;
  auto res = socket_.recv(reply, zmq::recv_flags::none);
  if (res.has_value()) {
    auto payload_res_as_str = reply.to_string();
    PayloadSolution payload_solution;
    if (!payload_solution.ParseFromString(payload_res_as_str)) {
      throw std::runtime_error("Failed to parse payload response");
    }
    logger_->info(std::format(
        " Received. name: {}, id: {}, solution: {}", payload_solution.name(),
        payload_solution.payload_id(), payload_solution.solution()));
  }
}
