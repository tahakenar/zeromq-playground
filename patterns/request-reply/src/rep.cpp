#include "rep.hpp"

#include <unistd.h>

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
    zmq::message_t request;
    auto result = socket_.recv(request, zmq::recv_flags::none);

    if (result.value_or(0) != 0) {
      auto payload = request.to_string_view();
      logger_->info(std::format("REQ payload received: {}", payload));
    }

    //  Pretend to do some 'work'
    sleep(1);

    constexpr std::string_view kReplyString = "World";
    zmq::message_t reply(kReplyString.length());
    memcpy(reply.data(), kReplyString.data(), kReplyString.length());
    logger_->info(std::format("Sending REP payload: {}", kReplyString));
    socket_.send(reply, zmq::send_flags::none);
  }
}