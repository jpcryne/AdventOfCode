#include<iostream>
#include<fstream>
#define INPUT_SIZE 2

int64_t find_loop_number(int64_t pk, int64_t subject_number, int64_t modulus) {
  int64_t loop_number{0};
  int64_t value{1};

  while(value != pk) {
    value *= subject_number;
    value = value % modulus;
    loop_number++;
  }

  return loop_number;
}

int64_t find_encryption_key(int64_t subject_number, int64_t loop_number, int64_t modulus) {
  int64_t enc_key{1};
  for(int64_t i=0;i<loop_number;i++) {
    enc_key*=subject_number;
    enc_key = enc_key % modulus;
  }
  return enc_key;
}

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  int64_t pks[INPUT_SIZE];

  int i{0};
  while(getline(input, line)) {
    pks[i] = stoll(line);
    i++;
  }

  int64_t loop_nums[2];
  for(int i=0;i<INPUT_SIZE;i++) {
    loop_nums[i] = find_loop_number(pks[i], 7, 20201227);
  }

  std::cout << "Encryption Key: " << find_encryption_key(pks[0], loop_nums[1], 20201227) << std::endl;

  return 0;
}
