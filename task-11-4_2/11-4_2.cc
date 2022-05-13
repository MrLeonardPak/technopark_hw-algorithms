/**
 * @file 11-4_2.cc
 * @author Leonard Pak
 * @brief Дано число N и N строк. Каждая строка содержит команду добавления или
 * удаления натуральных чисел, а также запрос на получение k-ой порядковой
 * статистики. Команда добавления числа A задается положительным числом A,
 * команда удаления числа A задается отрицательным числом “-A”. Запрос на
 * получение k-ой порядковой статистики задается числом k. Требования: скорость
 * выполнения запроса - O(log n).
 * @version 0.1
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cassert>
#include <iostream>
#include <sstream>

void Run(std::istream& in, std::ostream& out) {}

void TestContest() {
  {
    std::stringstream in;
    std::stringstream out;
    in << "5 40 0 10 1 4 1 -10 0 50 2" << std::endl;
    Run(in, out);
    assert(out.str() == "40 40 10 4 50");
  }
  std::cout << "TestContest: SUCCESS" << std::endl;
}

int main() {
  TestContest();
  // Run(std::cin, std::cout);
  return 0;
}