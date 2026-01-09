#include "req.hpp"

int main() {
  Req req{"tcp://localhost:5555"};

  for (int i = 0; i < 10; i++) {
    req.sendString("Hello");
    req.getReply();
  }
}
