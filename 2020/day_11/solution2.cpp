#include<iostream>
#include<fstream>

// MxN arrangement
#define M 90//90//10
#define N 93//93//10

void print_array(char a[], int rows, int cols);
int occ_check2(char c);
int adjacent_occupied2(char current[], int seat, int rows, int cols);
void update_seating2(char current[], char future[], int rows, int cols);
int look_around(int seat, int increment, char c[]);
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
    for(char &c : line) {
      arrangement[i] = c;
      i++;
    }
  }


  int num_occ{0};
  int tmp{0};
  while(true) {
    char future[(M+2)*(N+2)];
    update_seating2(arrangement, future, pad_row, pad_col);
    bool stable = true;
    num_occ = 0;
    for(int i = 0; i < (M+2)*(N+2); i++) {
      stable = (arrangement[i] == future[i]) && stable;
      num_occ += (future[i] == '#');
      arrangement[i] = future[i];
    }

    if(stable) break;
  }
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


void update_seating2(char current[], char future[], int rows, int cols) {
  int size = rows*cols;

  for(int i = 0; i < size; i++) {
    if(current[i] == '.' || current[i] == 'X') {
      future[i] = current[i];
      continue;
    }
    int adj_occ = adjacent_occupied2(current, i, rows, cols);
    if(current[i] == 'L' && adj_occ == 0) {
      future[i] = '#';
    } else if(current[i] == '#' && adj_occ >= 5) {
      future[i] = 'L';
    } else {
      future[i] = current[i];
    }

  }
}

int adjacent_occupied2(char current[], int seat, int rows, int cols) {
  int occupied{0};
  //Right
  occupied += look_around(seat, 1, current);
  //Left
  occupied += look_around(seat, -1, current);
  //Down
  occupied += look_around(seat, cols, current);
  //Up
  occupied += look_around(seat, -cols, current);
  //Down Right
  occupied += look_around(seat, cols+1, current);
  //Up Right
  occupied += look_around(seat, -cols+1, current);
  //Down Left
  occupied += look_around(seat, cols-1, current);
  //Up left
  occupied += look_around(seat, -cols-1, current);

  return occupied;
}

int occ_check2(char c) {
  if(c == 'X' || c == 'L') return 0;
  if(c == '#') return 1;
  return -1;
}

int look_around(int seat, int increment, char c[]) {
  for(int i = increment; true; i+=increment) {
    int occ = occ_check2(c[seat + i]);
    if(occ == -1) continue;
    return occ;
  }
  std::cout << "Error" << std::endl;
  return 0;
}
