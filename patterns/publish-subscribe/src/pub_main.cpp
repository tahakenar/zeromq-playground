#include <thread>

#include "pub.hpp"
#include "random_payload.hpp"

int main() {
  Pub pub{"tcp://*:5568"};

  for (int i = 0; i < 30; i++) {
    auto payload = util::get_random_payload();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    pub.publishPayload(payload);
  }
}
