#include<iostream>
#include<fstream>
#include <string>

bool check_passport(std::string s);

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  int line_count{1};
  std::string passport = "";
  int valid_count = 0;
  while (std::getline(input, line)) {
    // std::cout << line_count << ": " << line << std::endl;
    line_count++;
    passport += " " + line;
    if(line == "") {
      //std::cout << passport << " : " << check_passport(line)  << std::endl;
      valid_count += check_passport(passport);
      passport = "";
    }
  }

  std::cout << "Valid Count: " << valid_count << std::endl;
  return 0;
}

/*
  CHECK FOR PRESENCE OF ALL REQUIRED FIELDS
*/
bool check_passport(std::string s) {
  std::string items[7] = {"byr:", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

  for(int i = 0; i < 7; i++) {
    // std::cout << s << std::endl;
    if(s.find(items[i]) == std::string::npos) {
      // std::cout << items[i] << ": " << s.find(items[i]) << std::endl;
      return false;
    }
  }

  return true;
}
