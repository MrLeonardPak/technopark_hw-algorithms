/**
 * @file 1_3.cc
 * @author Leonard Pak
 * @brief Входное число лежит в диапазоне 0..2^32 -1 и вводится в десятичном
 * виде. Если в числе содержится только один бит со значением 1, записать в
 * выходной поток OK. Иначе записать FAIL
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <limits>

bool CheckBits(unsigned int num) {
  int count = 0;
  for (size_t i = 0; i < std::numeric_limits<unsigned int>::digits; ++i) {
    if (num & 0x1) {
      ++count;
    }
    if (count > 1) {
      // Нет смысла считать дальше, тк уже больше
      return false;
    }
    num >>= 1;
  }
  // count будет либо 0, либо 1
  return count;
}

int main() {
  unsigned int num = 0;
  std::cin >> num;
  if (CheckBits(num)) {
    std::cout << "OK" << std::endl;
  } else {
    std::cout << "FAIL" << std::endl;
  }
  return 0;
}