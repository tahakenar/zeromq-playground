#include "random_generator.hpp"
#include "sink.hpp"

int main() {
  Sink sink{"tcp://*:5568"};
  sink.bindToPull();
}
