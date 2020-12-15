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

struct result {
  bool terminates{false};
  int64_t acc;
};

boot_code read_input(std::string file_name);
result run_program(boot_code bc);
int64_t find_error(boot_code bc);

int main(void) {

  boot_code bc = read_input("input.txt");

  std::cout << find_error(bc) << std::endl;

  return 0;
}

int64_t find_error(boot_code bc) {
  int64_t val = 0;

  for(int i=0;i<bc.instruction.size(); i++) {
    if(bc.instruction.at(i) == 'a')
      continue;

    char original = bc.instruction.at(i);
    char replacement      = (original == 'j') ? 'n' : 'j';

    bc.instruction[i] = replacement;

    result r = run_program(bc);

    if(r.terminates) {
      val = r.acc;
      break;
    }

    bc.acc = 0;
    bc.instruction[i] = original;
    bc.visited.empty();
  }

  return val;
}

result run_program(boot_code bc) {
  int i{0};
  result r;

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
    if(i >= bc.instruction.size()) {
      r.terminates = true;
      break;
    }
  }

  r.acc = bc.acc;

  return r;
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
