#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<sstream>

/*
struct number_game {

};
*/

void print_vec(std::vector<int> v);
std::vector<int> read_input(std::string file_name);
void play_number_game(std::vector<int> start_nums);
void print_map(std::unordered_map<int,int> const &m);
int main(void) {
  std::vector<int> start_nums = read_input("test.txt");
  print_vec(start_nums);

  play_number_game(start_nums);


  return 0;
}

void play_number_game(std::vector<int> start_nums) {
  std::unordered_map<int64_t, int64_t> game;
  // Set up initial map
  // Number and round entered
  int i{1};
  for(int j=0;j<start_nums.size()-1;j++) {
    game.insert({start_nums.at(j), i});
    std::cout << "Turn " << i << ": " << start_nums.at(j) << std::endl;
    i++;
  }
  std::cout << "Turn " << start_nums.size() << ": " << start_nums.back() << std::endl;

  int64_t last_num  = start_nums.back();
  int64_t round = start_nums.size() + 1;

  while(round <= 30000001) {
    // Check if last number already said
    bool already_said = game.find(last_num) != game.end();
    int64_t next_num{0};
    if(already_said) {
      next_num = round - 1 - game.find(last_num) -> second;
    }

    game.insert_or_assign(last_num, round - 1);
    last_num = next_num;

    if(round == 2020 || round == 30000000)
      std::cout << "Turn " << round << ": " << next_num << std::endl;
    round++;

  }

}

std::vector<int> read_input(std::string file_name) {
  std::ifstream input(file_name);
  std::vector<int> v;
  std::string line;

  getline(input, line);
  // line += ',';
  std::stringstream ss(line);

  int i;

  while (ss >> i) {
    v.push_back(i);

    if (ss.peek() == ',')
        ss.ignore();
  }

  return v;
}

void print_map(std::unordered_map<int,int> const &m)
{
    for (auto const& pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

void print_vec(std::vector<int> v) {
  for(int i=0;i<v.size();i++)
    std::cout << v.at(i) << ", ";
  std::cout << std::endl;
}
