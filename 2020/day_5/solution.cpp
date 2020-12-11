#include<iostream>
#include<fstream>

#define ROWS 127
#define COLS 7

int get_row_number(std::string s);
int get_col_number(std::string s);

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  int max_id{0};
  int ids[774];
  int i{0};
  while (std::getline(input, line)) {
    int r_num = get_row_number(line.substr(0,7));
    int c_num = get_col_number(line.substr(7,10));
    max_id = ((r_num*8 + c_num) > max_id) ? (r_num*8 + c_num) : max_id;
    ids[i] = (r_num*8 + c_num);
    i++;
  }

  std::sort(ids, ids + 774);
  std::cout << "Min ID: " << ids[0] << std::endl;

  int j{0};
  for(int i = ids[0]; i<=max_id; i++) {
    if(ids[j] != i) {
      std::cout << "Missing ID: " << i << std::endl;
      break;
    }
    j++;
  }

  std::cout << "Max ID: " << max_id << std::endl;

  return 0;
}

int get_row_number(std::string s){
  int min{0}, max{ROWS};
  for (char const &c: s) {
    if(c == 'F') {
      max = max - (max - min + 1) / 2;
    } else {
      min = min + (max - min + 1) / 2;
    }
  }

  return max;
}

int get_col_number(std::string s) {
  int min{0}, max{COLS};
  for(char const &c: s) {
    if(c == 'L') {
      max = max - (max - min + 1) / 2;
    } else {
      min = min + (max - min + 1) / 2;
    }
  }

  return max;
}
