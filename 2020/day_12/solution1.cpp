#include<iostream>
#include<fstream>

struct Ferry {
  int angle{90};
  int north{0};
  int east{0};
  int south{0};
  int west{0};

};

void print_ferry(Ferry f);
void move_forward(Ferry &f, int steps);
void process_input(Ferry &f, char dir, int steps);

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  Ferry ferry;

  while(getline(input, line)) {

    char direction = line.front();
    int steps      = stoi(line.substr(1, line.length()));
    std::cout << line << std::endl;
    process_input(ferry, direction, steps);
    print_ferry(ferry);

  }

  std::cout << "Manhattan Distance: " <<
    abs(ferry.east - ferry.west) +
    abs(ferry.north - ferry.south) <<
    std::endl;

  return 0;
}

void process_input(Ferry &f, char dir, int steps) {
  switch(dir) {
    case 'N' :
      f.north += steps;
      break;
    case 'E' :
      f.east += steps;
      break;
    case 'S' :
      f.south += steps;
      break;
    case 'W' :
      f.west += steps;
      break;
    case 'R' :
      f.angle = (f.angle + steps) % 360;
      f.angle = (f.angle < 0) ? 360 + f.angle : f.angle;
      break;
    case 'L' :
      f.angle = (f.angle - steps) % 360;
      f.angle = (f.angle < 0) ? 360 + f.angle : f.angle;
      break;
    case 'F' :
      move_forward(f, steps);
      break;
    default :
      break;
  }
}

void move_forward(Ferry &f, int steps) {
  char dirs[4] = {'N', 'E', 'S', 'W'};
  process_input(f, dirs[f.angle / 90], steps);
}

void print_ferry(Ferry f) {
  std::cout << "N: " << f.north << ", ";
  std::cout << "E: " << f.east << ", ";
  std::cout << "W: " << f.west << ", ";
  std::cout << "S: " << f.south << ", ";
  std::cout << "Angle: " << f.angle << ", ";
  std::cout << std::endl;
}
