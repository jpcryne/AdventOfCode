#include<iostream>
#include<fstream>
#include <unordered_set>

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  int sum1{0};

  bool group_answers[26];
  for(int i = 0; i < 26; i++) group_answers[i] = false;

  bool first_in_group = true;

  while(getline(input, line)) {
    if(line == "") {
      for(int i=0;i<26;i++) sum1+=group_answers[i];
      first_in_group = true;
      continue;
    }

    if(first_in_group) {
      for(int i = 0; i < 26; i++) group_answers[i] = false;
      first_in_group = false;
      for(char &c : line) {
        group_answers[((int) c) - 97] = true;
      }
      continue;
    } else {
      bool person_answers[26];
      for(int i = 0; i < 26; i++) person_answers[i] = false;
      for(char &c : line) {
        person_answers[((int) c) - 97] = true;
      }
      for(int i=0;i<26;i++) {
        group_answers[i] = group_answers[i] && person_answers[i];
      }
    }

  }

  for(int i=0;i<26;i++) sum1+=group_answers[i];

  std::cout << "Part 1: " << sum1 << std::endl;

  return 0;
}
