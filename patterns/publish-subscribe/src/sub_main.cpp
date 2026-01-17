#include "sub.hpp"

int main() {
  Sub sub{"tcp://localhost:5568"};
  sub.subscribe();
}
