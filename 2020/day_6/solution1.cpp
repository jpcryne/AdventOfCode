#include<iostream>
#include<fstream>
#include <unordered_set>

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  int sum1{0};
  std::unordered_set<char> answers;
  
  while(getline(input, line)) {
    if(line == "") {
      sum1 += answers.size();
      answers.clear();
      continue;
    }
    for(char &c : line) {
      answers.insert(c);
    }
  }
  sum1 += answers.size();

  std::cout << "Part 1: " << sum1 << std::endl;

  return 0;
}
