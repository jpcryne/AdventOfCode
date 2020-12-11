#include<iostream>
#include<fstream>

#define NO_LINES 11 //13 // 103

void print_array(int* a, int size);
void nth_order_difference(int* a, int size, int n, int result[]);
void part_1_solution(int* a, int size);
int recursive_solution(int* a, int size);

int main(void) {

  std::ifstream input("test_1.txt");
  int a;
  int joltages[NO_LINES + 2];
  int i{0};
  int max{0};

  while(input >> a) {
    joltages[i] = a;
    if(a > max) {
      max = a;
    }
    i++;
  }
  joltages[NO_LINES] = max + 3;
  joltages[NO_LINES + 1] = 0;
  std::sort(joltages, joltages + NO_LINES + 2);

  int diffs_1[NO_LINES+1];
  int diffs_2[NO_LINES];
  int diffs_3[NO_LINES - 1];
  nth_order_difference(joltages, NO_LINES + 2, 1, diffs_1);
  nth_order_difference(joltages, NO_LINES + 2, 2, diffs_2);
  nth_order_difference(joltages, NO_LINES + 2, 3, diffs_3);

  part_1_solution(diffs_1, NO_LINES+1);
  /*
  print_array(diffs_3, NO_LINES-1);
  print_array(diffs_2, NO_LINES);
  print_array(diffs_1, NO_LINES + 1);
  print_array(joltages, NO_LINES + 2);
  */
  int tmp[9] = {0,1,4,5,6,7,10,11,12};
  std::cout << recursive_solution(joltages, NO_LINES + 2) << std::endl;
  std::cout << recursive_solution(tmp, 9) << std::endl;

  return 0;
}

void print_array(int* a, int size) {
  for(int i = 0; i < size; i++) {
    std::cout << i << ": " << *(a+i) << std::endl;
  }
  std::cout << "\n";
}

void nth_order_difference(int* a, int size, int n, int result[]) {

  for(int i = 0; i < size - n; i++) {
    result[i] = *(a+i+n) - *(a+i);
  }
}

/*
  Return no 3s * no 1s
*/
void part_1_solution(int* a, int size) {
  int num_1{0}, num_3{0};
  for(int i = 0; i < size; i++) {
    num_1 += (*(a+i) == 1);
    num_3 += (*(a+i) == 3);
  }
  //std::cout << "Num 1s: " << num_1 << ", Num 3s: " << num_3 << std::endl;
  std::cout << "Solution: " << num_1*num_3 << std::endl;
}

int recursive_solution(int* a, int size) {
  if(size == 3) {
    if(*(a+2) - *(a) <= 3) {
      return 2;
    } else {
      return 1;
    }
  }
  bool b3 = (*(a + size - 1) - *(a + size - 4) <= 3);
  bool b2 = (*(a + size - 1) - *(a + size - 3) <= 3);
  bool b1 = (*(a + size - 1) - *(a + size - 2) <= 3);

  if(b1 && b2 && b3) return 2 + recursive_solution(a, size-1);
  if(b1 && b2) return 1 + recursive_solution(a, size-1);

  return recursive_solution(a, size-1);

}
