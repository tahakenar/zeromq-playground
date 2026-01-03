#include "req.hpp"
#include "zeromq_logger.hpp"

#include <cstring>
#include <format>
#include <unistd.h>

Req::Req(const std::string &addr)
    : connection_addr_{addr}, context_(1),
      socket_(context_, zmq::socket_type::req),
      logger_(util::get_logger(std::format("REQ Client with pid: {}", getpid()),
                               util::LoggerColor::Cyan)) {

  logger_->info(std::format("Initialized for address {}", connection_addr_));
  socket_.connect(connection_addr_);
}

void Req::sendString(const std::string& msg) {
    zmq::message_t request(msg.size());
    memcpy(request.data(), &msg, msg.size());
    logger_->info(std::format("Sending message: {}", msg));
    socket_.send(request, zmq::send_flags::none);
}

void Req::getReply() {
    zmq::message_t reply;
    auto res = socket_.recv(reply, zmq::recv_flags::none);
    if (res.has_value()) {
        logger_->info(std::format("Received bytes: {}", res.value()));
    }
}
