#include<iostream>
#include<fstream>
#include<deque>

void print_deque(std::deque<int> d) {
  std::cout << "[";
  for(auto e : d)
    std::cout << e << ", ";
  std::cout << "]" << std::endl;
}

int64_t play(std::deque<int> d1, std::deque<int> d2) {
  while(d1.size() != 0 & d2.size() != 0) {
    int i1 = d1.front();
    int i2 = d2.front();

    if(i1 > i2) {
      d1.push_back(i1);
      d1.push_back(i2);
    }
    if(i2 > i1) {
      d2.push_back(i2);
      d2.push_back(i1);
    }
    d1.pop_front();
    d2.pop_front();
    /*
    std::cout << "P1 Deck: ";print_deque(d1);
    std::cout << "P2 Deck: ";print_deque(d2);
    std::cout << "\n\n";
    */
  }

  int64_t sum{0};
  int count{1};
  std::deque<int> d3;
  if(d1.size() == 0) {
    d3 = d2;
  } else {
    d3 = d1;
  }

  for(auto e : d3) {
    sum += count*d3.back();
    d3.pop_back();
    count++;
  }

  return sum;
}

int main(void) {
  std::ifstream input("input.txt");
  std::string line;
  std::deque<int> deck_1, deck_2;
  bool p1 = true;;
  while(getline(input, line)) {
    if(line == "") {
      p1 = false;
      continue;
    }
    if(line.at(0) == 'P') continue;

    if(p1) {
      deck_1.push_back(stoi(line));
    } else {
      deck_2.push_back(stoi(line));
    }
  }

  std::cout << "Part 1: " << play(deck_1, deck_2) << std::endl;
  return 0;
}
