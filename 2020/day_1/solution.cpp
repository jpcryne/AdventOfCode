#include<iostream>
#include <fstream>

/**
  Find the sums of pairs of 2 and triples of 3 which sum to 2020
  Return product
**/
int main(void) {
  std::ifstream input ("input.txt");

  int a;
  int i{0};
  int x[200];
  bool found2 = false;
  bool found3 = false;

  while (input >> a) {
    x[i] = a;

    // Find sum for each pair read so far
    for(int j = 0; j < i; j++) {

      if(!found3) {
        if(x[i] + x[j] < 2020) {
          for(int k = 0; k < j; k++) {
            if(x[i] + x[j] + x[k] == 2020) {
              std::cout << "Found: " << x[i] << " + " << x[j] << " + " << x[k] << " = " << 2020 << std::endl;
              std::cout << "Answer: " << x[i] * x[j] * x[k] << std::endl;
              found3 = true;
              break;
            }
          }
        }
      }

      if(!found2) {
        if(x[i] + x[j] == 2020) {
          found2 = true;
          std::cout << "Found: " << x[i] << " + " << x[j] << " = " << 2020 << std::endl;
          std::cout << "Answer: " << x[i] * x[j] << std::endl;
          found2 = true;
          break;
        }
      }
    }

    if(found2 && found3) break;
    i++;
  }

  return 0;
}
