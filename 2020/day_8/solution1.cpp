#include<iostream>
#include<fstream>
#include<unordered_set>
#include<vector>

struct boot_code {
  int64_t acc{0};
  std::vector<char> instruction;
  std::vector<int64_t> value;
  std::unordered_set<int64_t> visited;
};

boot_code read_input(std::string file_name);
int64_t run_program(boot_code bc);

int main(void) {

  boot_code bc = read_input("input.txt");

  std::cout << run_program(bc) << std::endl;

  return 0;
}

int64_t run_program(boot_code bc) {
  int i{0};

  while(true) {
    bc.visited.insert(i);

    if(bc.instruction.at(i) == 'n') {
      i++;
      continue;
    } else if(bc.instruction.at(i) == 'a') {
      bc.acc += bc.value.at(i);
      i++;
    } else {
      i += bc.value.at(i);
    }

    if(bc.visited.find(i) != bc.visited.end())
      break;
  }


  return bc.acc;
}

boot_code read_input(std::string file_name) {
  boot_code bc;

  std::ifstream input(file_name);

  std::string line;

  while(getline(input, line)) {
    bc.instruction.push_back(line.at(0));
    bc.value.push_back(stoll(line.substr(4, line.length())));
  }

  return bc;
}
