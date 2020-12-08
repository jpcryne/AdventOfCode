#include <iostream>
#include <fstream>

int* get_limits(std::string s);
char get_target(std::string s);
std::string get_password(std::string s);

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  int valid_count1 = 0;
  int valid_count2 = 0;
  while (std::getline(input, line)) {
    int* lims      = get_limits(line);
    char target    = get_target(line);
    std::string pw = get_password(line);

    // Part 1 Check
    int count = 0;
    for(char& c : pw) {
      if(c == target) count++;
    }
    bool valid1 = false;
    if(count >= *lims && count <= *(lims+1)) {
      valid1 = true;
      valid_count1++;
    }

    // Part 2 Check
    bool b1 = target == pw.at(*lims);
    bool b2 = target == pw.at(*(lims + 1));

    bool valid2 = false;
    if((b1 || b2) && !(b1 && b2)) {
      valid_count2++;
      valid2 = true;
    }

  }

  std::cout << "Number Valid P1 = " << valid_count1 << std::endl;
  std::cout << "Number Valid P2 = " << valid_count2 << std::endl;

  return 0;
}

/*
  Returns min and max limits of char occurrence
*/
int* get_limits(std::string s) {
  // Must declare as static otherwise freed when goes out of scope
  static int x[2];
  int hyphen_index = s.find("-");
  int space_index  = s.find(" ");
  int min_app = stoi(s.substr(0, hyphen_index));
  int max_app = stoi(s.substr(hyphen_index+1, space_index));

  x[0] = min_app;
  x[1] = max_app;

  return x;
}

/*
 Get the char to be checked
*/
char get_target(std::string s) {
  int colon_index = s.find(":");

  return s.at(colon_index - 1);
}

/*
 Get password string
*/
std::string get_password(std::string s) {
  int colon_index = s.find(":");
  int string_len  = s.length();

  return s.substr(colon_index + 1, string_len - 1);
}
