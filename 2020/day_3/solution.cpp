#include<iostream>
#include<fstream>

#define RUNS 5

int main(void) {
  std::ifstream input("input.txt");
  std::string line;

  /*
  int x_inc     = 3;
  int x_max     = 31;
  int x_loc     = 0;
  int trees_hit = 0;
  */

  int x_inc[RUNS]     = {1,3,5,7,1};
  int y_inc[RUNS]     = {1,1,1,1,2};
  int x_max{31};
  int x_loc[RUNS]     = {0,0,0,0,0};
  int trees_hit[RUNS] = {0,0,0,0,0};

  int y_loc = 0;
  while (std::getline(input, line)) {
    for(int i = 0; i < RUNS; i++) {

      if(y_loc % y_inc[i] != 0) continue;

      if(line.at(x_loc[i]) == '#') {
        trees_hit[i]++;
      }

      x_loc[i] = (x_loc[i] + x_inc[i]) % x_max;

      //std::cout << x_loc[i] << std::endl;
    }
    y_loc++;
  }

  long long mult{1};
  for(int i = 0; i < RUNS; i++) {
    std::cout << "Trees Hit: " << trees_hit[i] << std::endl;
    mult*=trees_hit[i];
  }

  std::cout << "Solution: " << mult << std::endl;

  return 0;
}
