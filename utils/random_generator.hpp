#include <random>
#include <string>
#include <vector>

#include "payload.pb.h"

namespace util {

inline std::vector<std::string> names{
    "cat",    "dog",   "rabbit", "donkey", "hamster", "parrot",  "pig",
    "cow",    "horse", "sheep",  "rat",    "goat",    "chicken", "duck",
    "turkey", "deer",  "fox",    "wolf",   "bear",    "lion"};

inline Payload get_random_payload() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<std::size_t> name_dist(0, names.size() - 1);
  std::uniform_int_distribution<int32_t> id_dist(0, 1000);
  std::uniform_int_distribution<int32_t> operand_dist(1, 99);

  Payload payload;

  payload.set_name(names[name_dist(gen)]);
  payload.set_payload_id(id_dist(gen));
  payload.set_left_operand(operand_dist(gen));
  payload.set_right_operand(operand_dist(gen));

  return payload;
}

inline int get_random_integer(int lower_bound = 1, int upper_bound = 10) {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<std::size_t> int_dist(lower_bound, upper_bound);

  return int_dist(gen);
}

}  // namespace util
