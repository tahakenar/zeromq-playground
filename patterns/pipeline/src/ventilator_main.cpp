#include "random_payload.hpp"
#include "ventilator.hpp"

int main() {
  Ventilator vent{"tcp://*:5559"};

  for (int i = 0; i < 50; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto payload = util::get_random_payload();
    vent.pushPayload(payload);
  }
}
