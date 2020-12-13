#include<iostream>
#include<fstream>

int get_wait_time(int depart, int bus_num);

int main(void) {

  std::ifstream input("input.txt");

  int depart{0};
  input >> depart;

  std::string line;

  getline(input, line);
  getline(input, line);
  std::cout << line << std::endl;

  int min_wait;
  int best_bus;
  int i{0};
  std::string tmp;

  for(char &c : line) {
    if(c == ',') {
      if(tmp != "x") {
        int bus_num   = stoi(tmp);
        int wait_time = get_wait_time(depart, bus_num);

        if(i == 0) {
          min_wait = wait_time;
          best_bus = bus_num;
        }
        if(wait_time < min_wait) {
          min_wait = wait_time;
          best_bus = bus_num;
        }
        i++;
      }
      tmp.clear();
    } else {
      tmp.push_back(c);
    }
  }
  if(tmp != "x") {
    int bus_num   = stoi(tmp);
    int wait_time = get_wait_time(depart, bus_num);

    if(wait_time < min_wait) {
      min_wait = wait_time;
      best_bus = bus_num;
    }
  }

  std::cout << best_bus * min_wait << std::endl;
  return 0;
}

int get_wait_time(int depart, int bus_num) {
  return bus_num - (depart % bus_num);
}
