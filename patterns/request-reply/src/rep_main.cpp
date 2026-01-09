#include "rep.hpp"

int main() {
  Rep rep{"tcp://*:5555"};
  rep.start();
}
