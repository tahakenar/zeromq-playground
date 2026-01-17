#include "random_generator.hpp"
#include "worker.hpp"

int main() {
  Worker worker{"tcp://localhost:5559", "tcp://localhost:5568"};
  worker.connectToPullAndPush();
}
