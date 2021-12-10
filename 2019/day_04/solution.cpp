#include<iostream>
#include<fstream>

bool check_password(int pw) {
  int tmp = pw;
  int cur_digit{0},last_digit{10};
  bool consec = false;
  while(tmp != 0) {
    cur_digit = tmp % 10;
    if(cur_digit > last_digit) return false;
    if(cur_digit == last_digit) consec = true;
    tmp /= 10;
    last_digit = cur_digit;
  }

  return consec;
}

bool check_password2(int pw) {
  int tmp = pw;
  int cur_digit{0},last_digit{10};
  int pair_count{0}, pair_count_tmp{0};
  while(tmp != 0) {
    cur_digit = tmp % 10;

    if(cur_digit > last_digit) return false;
    if(cur_digit == last_digit) pair_count_tmp++;
    if(cur_digit != last_digit) {
      if(pair_count_tmp == 1) pair_count++;
      pair_count_tmp = 0;
    }

    tmp /= 10;
    last_digit = cur_digit;
  }
  if(cur_digit == last_digit && pair_count_tmp == 1)
    pair_count++;

  return (pair_count > 0);
}

int main(void) {
  std::ifstream input("input.txt");
  std::string line;
  getline(input, line);

  int start = stoi(line.substr(0, line.find('-')));
  int end   = stoi(line.substr(1+line.find('-'), line.size()-1));

  int sum{0};
  for(int i=start;i<=end;i++)
    sum += check_password(i);

  std::cout << "Part 1: " << sum << std::endl;

  sum = 0;
  for(int i=start;i<=end;i++) {
    sum += check_password2(i);
  }

  std::cout << "Part 2: " << sum << std::endl;

  return 0;
}
