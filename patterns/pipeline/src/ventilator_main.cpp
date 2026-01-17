#include "random_generator.hpp"
#include "ventilator.hpp"

int main() {
  Ventilator vent{"tcp://*:5559"};

  for (int i = 0; i < 10; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    auto payload = util::get_random_payload();
    vent.pushPayload(payload);
  }
}
