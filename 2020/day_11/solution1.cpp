#include<iostream>
#include<fstream>

// MxN arrangement
#define M 90//11//90//10
#define N 93//10//93//10

void print_array(char a[], int rows, int cols);
void update_seating(char current[], char next[], int rows, int cols);
int adjacent_occupied(char current[], int seat, int rows, int cols);

int main(void) {

  std::ifstream input("input.txt");

  std::string line;

  char arrangement[(M+2)*(N+2)];
  int pad_col{N+2}, pad_row(M+2);
  int padded_size = pad_col*pad_row;
  for(int i = 0; i < padded_size; i++) arrangement[i] = 'X';

  int i{0};
  while(std::getline(input, line)) {
    while(i < pad_col || i % pad_col == 0 || i % pad_col == (pad_col - 1) || i >= padded_size - pad_col)
      i++;
    // std::cout << line << std::endl;
    for(char &c : line) {
      arrangement[i] = c;
      i++;
    }
  }


  int num_occ{0};
  int tmp{0};
  while(true) {
    char future[(M+2)*(N+2)];
    update_seating(arrangement, future, pad_row, pad_col);
    bool stable = true;
    num_occ = 0;
    for(int i = 0; i < (M+2)*(N+2); i++) {
      stable = (arrangement[i] == future[i]) && stable;
      num_occ += (future[i] == '#');
      arrangement[i] = future[i];
      //print_array(arrangement, pad_row, pad_col);
    }
    if(stable) break;
  }

  // print_array(arrangement, pad_row, pad_col);

  std::cout << num_occ << std::endl;

  return 0;
}

void print_array(char a[], int rows, int cols) {
  int size = rows*cols;
  std::cout << std::endl;
  for(int i = 0; i < size; i++) {
    std::cout << a[i];
    if(i % cols == cols-1) {
      std::cout << std::endl;
    }
  }
}


void update_seating(char current[], char future[], int rows, int cols) {
  int size = rows*cols;

  for(int i = 0; i < size; i++) {
    if(current[i] == '.' || current[i] == 'X') {
      future[i] = current[i];
      continue;
    }
    int adj_occ = adjacent_occupied(current, i, rows, cols);
    if(current[i] == 'L' && adj_occ == 0) {
      future[i] = '#';
    } else if(current[i] == '#' && adj_occ >= 4) {
      future[i] = 'L';
    } else {
      future[i] = current[i];
    }

  }
}

int adjacent_occupied(char current[], int seat, int rows, int cols) {
  int check[8] = {seat-1, seat+1,
                  seat-cols, seat+cols,
                  seat-cols-1, seat-cols+1,
                  seat+cols-1, seat+cols+1};
  int occupied{0};

  for(int i = 0; i < 8; i++)
    occupied += (current[check[i]] == '#');

  return occupied;
}
