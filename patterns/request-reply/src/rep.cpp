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
    // unused variable to test static check pipeline
    int a{3};

    zmq::message_t request;
    //  Wait for next request from client
    auto result = socket_.recv(request, zmq::recv_flags::none);
    assert(result.value_or(0) != 0);  // Check if bytes received is non-zero

    logger_->info("Received Hello");

    //  Pretend to do some 'work'
    sleep(1);

    //  Send reply back to client
    constexpr std::string_view kReplyString = "World";
    zmq::message_t reply(kReplyString.length());
    memcpy(reply.data(), kReplyString.data(), kReplyString.length());
    socket_.send(reply, zmq::send_flags::none);
  }
}