#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator () (const std::pair<T1,T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    // Mainly for demonstration purposes, i.e. works but is overly simple
    // In the real world, use sth. like boost.hash_combine
    return h1 ^ h2;
  }
};

std::vector<std::string> store_instruction(std::string s) {
  std::string tmp;
  std::vector<std::string> v;
  for(char &c : s) {
    if(c == ',') {
      v.push_back(tmp);
      tmp.clear();
    } else {
      tmp.push_back(c);
    }
  }
  v.push_back(tmp);
  return v;
}

std::unordered_set<std::pair<int,int>, pair_hash> parse_instruction(std::vector<std::string> instructions, std::unordered_map<std::pair<int,int>, int, pair_hash> &m) {
  std::unordered_set<std::pair<int,int>, pair_hash> result;
  std::pair<int,int> loc = std::make_pair(0,0);
  int steps{0};
  for(auto instruction : instructions) {
    int dest = stoi(instruction.substr(1, instruction.size()-1));
    char dir = instruction.at(0);
    int i{loc.first},j{loc.second};
    for(int k=0;k<dest;k++) {
      switch(dir) {
        case 'U' : i++;
            break;
        case 'D' : i--;
            break;
        case 'R' : j++;
            break;
        case 'L' : j--;
            break;
      }
      steps++;
      result.insert(std::make_pair(i, j));
      loc.first=i;loc.second=j;
      m.insert({std::make_pair(i,j), steps});
    }
  }
  return result;
}

int main(void) {
  std::ifstream input("input.txt");
  std::string line;

  //First Line
  getline(input, line);
  std::vector<std::string> path_1 = store_instruction(line);
  std::unordered_map<std::pair<int,int>,int, pair_hash> steps_taken_1;
  std::unordered_set<std::pair<int,int>, pair_hash> points_1 = parse_instruction(path_1, steps_taken_1);

  //Second Line
  getline(input, line);
  std::vector<std::string> path_2 = store_instruction(line);
  std::unordered_map<std::pair<int,int>,int, pair_hash> steps_taken_2;
  std::unordered_set<std::pair<int,int>, pair_hash> points_2 = parse_instruction(path_2, steps_taken_2);

  int p1{100000};
  for(auto elem : points_2) {
    if(points_1.find(elem) != points_1.end()) {
      int m_dist = abs(elem.first) + abs(elem.second);
      p1 = (p1 > m_dist) ? m_dist : p1;
      //std::cout << "Intersection Found: (" << elem.first << ", " << elem.second << ")\n";
    }
  }
  std::cout << "Part 1: " << p1 << std::endl;

  int p2{100000};
  for(auto elem : points_2) {
    if(points_1.find(elem) != points_1.end()) {
      int dist = steps_taken_1.find(elem) -> second + steps_taken_2.find(elem) -> second;
      p2 = (p2 > dist) ? dist : p2;
    }
  }
  std::cout << "Part 2: " << p2 << std::endl;

  return 0;
}
