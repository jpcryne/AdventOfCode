#include<iostream>
#include<fstream>

int main(void) {

  int fuel;
  std::ifstream input("input.txt");
  int64_t sum1{0},sum2{0};
  while(input >> fuel) {
    sum1 += fuel / 3 - 2;

    int tmp = fuel;
    while(true) {
      tmp = tmp / 3 - 2;
      if(tmp < 0) break;
      sum2 += tmp;
    }
  }

  std::cout << "Part 1: " << sum1 << std::endl;
  std::cout << "Part 2: " << sum2 << std::endl;

  return 0;
}
