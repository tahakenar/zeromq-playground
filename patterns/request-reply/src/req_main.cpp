#include "payload.pb.h"
#include "random_payload.hpp"
#include "req.hpp"

int main() {
  Req req{"tcp://localhost:5555"};

  for (int i = 0; i < 10; i++) {
    auto payload = util::get_random_payload();
    req.sendPayload(payload);
    req.getPayloadSolution();
  }
}
