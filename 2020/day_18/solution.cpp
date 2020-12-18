#include<iostream>
#include<fstream>
#include<vector>

int64_t calculate(std::string s);
int64_t calculate_helper(int64_t x, int64_t y, char op);
int64_t advanced_calculate(std::string s);
int find_bracket_match_index(std::string s);
int64_t solve_recursive(std::string s);

int main(void) {
  std::ifstream input("input.txt");
  std::string line;
  int64_t sum1{0}, sum2{0};
  while(getline(input, line)) {
    sum1 += calculate(line);
    sum2 += solve_recursive(line);
  }

  std::cout << "Part 1: " << sum1 << std::endl;
  std::cout << "Part 2: " << sum2 << std::endl;
  return 0;
}

// Solve here
int64_t solve_recursive(std::string s) {
  int64_t result{0};
  std::vector<int64_t> calculations;
  std::vector<char> operations;
  operations.push_back('+');

  for(int i=0;i<s.size();i++) {
    char c = s.at(i);
    if(c == ' ') {
      continue;
    } else if(c == '(') {
      int bracket_match = find_bracket_match_index(s.substr(i, s.size()));
      int64_t tmp = solve_recursive(s.substr(i+1, bracket_match-1));
      if(operations.back() == '+') {
        result += tmp;
        operations.pop_back();
      } else if(operations.back() == '*') {
        //calculations.push_back(result);
        result = tmp;
      }
      s = s.substr(bracket_match, s.size());
    } else if(c == '+') {
      operations.push_back(c);
    } else if(c == '*') {
      operations.push_back(c);
      calculations.push_back(result);
    } else {
      if(operations.back() == '+') {
        result += (int64_t) c - '0';
        operations.pop_back();
      } else {
        result = (int64_t) c - '0';
      }
    }
  }

  while(operations.size() > 0) {
    if(operations.back() == '*') {
      result *= calculations.back();
    } else {
      result += calculations.back();
    }
    operations.pop_back();
    calculations.pop_back();
  }

  return result;
}

int64_t calculate(std::string s) {
  std::vector<int> calculations;
  std::vector<char> operations;
  operations.push_back('+');
  int64_t result = 0;
  for(char &c : s) {

    if(c == ' ') {
      continue;
    } else if (c == '*' || c == '+') {
      operations.push_back(c);
    } else if(c == '(') {
      calculations.push_back(result);
      operations.push_back('+');
      result = 0;
    } else if(c == ')'){
      result = calculate_helper(result, calculations.back(), operations.back());
      operations.pop_back();
      calculations.pop_back();
    } else {
      result = calculate_helper(result, (int64_t) c-'0', operations.back());
      operations.pop_back();
    }

  }

  return result;
}

int find_bracket_match_index(std::string s) {
  int unmatched{1};
  int i{1};
  for(char &c : s.substr(1,s.size())) {
    if(c == '(') unmatched++;
    if(c == ')') unmatched--;
    if(unmatched == 0) return i;
    i++;
  }
  return -1;
}

int64_t calculate_helper(int64_t x, int64_t y, char op) {
  if(op == '+') {
    return x+y;
  } else if (op == '*') {
    return x*y;
  }
  return 0;
}
