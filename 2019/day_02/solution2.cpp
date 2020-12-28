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

  std::vector<int64_t> intcode_backup;
  for(int i=0;i<intcode.size();i++) {
    intcode_backup.push_back(intcode.at(i));
  }

  bool complete = false;
  for(int i=0;i<=99;i++) {
    for(int j=0;j<=99;j++) {
      for(int k=0;k<intcode.size();k++) {
        intcode.at(k) = intcode_backup.at(k);
      }

      intcode.at(1) = i;
      intcode.at(2) = j;
      int64_t opcode_index{0};
      while(true) {
        try {
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
        } catch(const std::out_of_range& e) {
          break;
        }
        if(complete && intcode.at(0) == 19690720) {
          std::cout << "i: " << i << ", j: " << j << std::endl;
          std::cout << "Part 2: " << 100*i + j << std::endl;
          return 0;
        }
        opcode_index += 4;
      }
    }
  }
  
  return 0;
}
