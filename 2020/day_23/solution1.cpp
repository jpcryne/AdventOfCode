#include<iostream>
#include<cmath>
#include<vector>

int find_destination_cup(std::vector<int> a, int cur_cup);
std::vector<int> move_current_to_front(std::vector<int> a, int current);

void print_vector(std::vector<int> v) {
  std::cout << "[";
  for(auto elem : v)
    std::cout << elem << ", ";
  std::cout << "]" << std::endl;
}

int main(void) {
  std::vector<int> cups = {1,2,3,4,8,7,5,9,6};
  //std::vector<int> cups = {3, 8,  9,  1,  2,  5,  4,  6,  7 };
  std::vector<int> rm_cups;
  int cur_cup = cups.front();
  int move{1};

  while(move <= 100) {
    cups = move_current_to_front(cups, cur_cup);
    for(int i=1;i<=3;i++)
      rm_cups.push_back(cups.at(i));
    cups.erase(cups.begin()+1, cups.begin()+4);
    int dest = find_destination_cup(cups, cur_cup);
    for(int i=0; i<3;i++) {
      cups.emplace(cups.begin()+dest+1, rm_cups.back());
      //rm_cups.erase(rm_cups.begin());
      rm_cups.pop_back();
    }
    //std::cout << "Move "<< move << ": ";
    //std::cout << "\n\n";
    cur_cup = cups.at(1);
    move++;
  }

  cups = move_current_to_front(cups, 1);
  for(auto e : cups) {
    if(e!=1) std::cout << e;
  }
  std::cout << std::endl;
  return 0;
}

std::vector<int> move_current_to_front(std::vector<int> a, int current) {
  while(a.front() != current) {
    a.push_back(a.front());
    a.erase(a.begin());
  }
  return a;
}


int find_destination_cup(std::vector<int> a, int cur_cup) {
  int max1 = -1000;
  int max2 = -1000;

  for(int i=0; i<a.size();i++) {
    if(a.at(i) == cur_cup) continue;
    if(a.at(i) < cur_cup && a.at(i) > max1) max1 = a.at(i);
    if(a.at(i) > max2) max2 = a.at(i);
  }
  int max = (max1 == -1000) ? max2 : max1;

  int ind = -1;
  for(int i=0;i<a.size();i++) {
    if(a.at(i) == max) ind = i;
  }

  return ind;
}
