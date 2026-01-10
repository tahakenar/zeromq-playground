#include "payload.pb.h"
#include "req.hpp"

int main() {
  Req req{"tcp://localhost:5555"};

  for (int i = 0; i < 4; i++) {
    Payload random_payload;
    random_payload.set_payload_id(123);
    random_payload.set_name("Nane");
    random_payload.set_left_operand(10);
    random_payload.set_right_operand(25);

    req.sendPayload(random_payload);
    req.getPayloadResponse();
  }
}
