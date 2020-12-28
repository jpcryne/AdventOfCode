#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

int main(void) {
  std::ifstream input("input.txt");
  std::vector<int64_t> intcode;
  std::string line;
  while(getline(input, line)) {
    std::stringstream ss(line);
    int i;
    while(ss >> i) {
      intcode.push_back(i);
      if(ss.peek() == ',') {
        ss.ignore();
      }
    }
  }

  // Alterations for P1
  intcode.at(1) = 12;
  intcode.at(2) = 2;

  int64_t opcode_index{0};
  bool complete = false;
  while(true) {
    int64_t opcode = intcode.at(opcode_index);
    switch(opcode) {
      case 1 :
        intcode.at(intcode.at(opcode_index+3)) = intcode.at(intcode.at(opcode_index+1)) + intcode.at(intcode.at(opcode_index+2));
        break;
      case 2 :
        intcode.at(intcode.at(opcode_index+3)) = intcode.at(intcode.at(opcode_index+1)) * intcode.at(intcode.at(opcode_index+2));
        break;
      case 99 :
        complete = true;
        break;
    }
    if(complete) break;
    opcode_index += 4;
  }

  std::cout << "Part 1: " << intcode.at(0) << std::endl;

  return 0;
}
