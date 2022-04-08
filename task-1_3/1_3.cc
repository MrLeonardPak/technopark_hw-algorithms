#include <iostream>
#include <limits>

bool CheckBits(unsigned int num) {
  int count = 0;
  for (size_t i = 0; i < std::numeric_limits<unsigned int>::digits; ++i) {
    if (num & 0x1) {
      ++count;
    }
    if (count > 1) {
      return false;
    }
    num >>= 1;
  }
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