#include<iostream>
#include<fstream>
#include <algorithm>

struct Ferry {
  int distance_moved[2] = {0,0};
  int waypoint[2]       = {1,10};
};

void print_ferry(Ferry f);
void move_forward(Ferry &f, int steps);
void process_input(Ferry &f, char dir, int steps);
void handle_rotation(Ferry &f, int steps);

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
    abs(ferry.distance_moved[0]) +
    abs(ferry.distance_moved[1]) <<
    std::endl;

  return 0;
}

void process_input(Ferry &f, char dir, int steps) {
  switch(dir) {
    case 'N' :
      f.waypoint[0] += steps;
      break;
    case 'E' :
      f.waypoint[1] += steps;
      break;
    case 'S' :
      f.waypoint[0] -= steps;
      break;
    case 'W' :
      f.waypoint[1] -= steps;
      break;
    case 'R' :
      handle_rotation(f, steps);
      break;
    case 'L' :
      handle_rotation(f, 360 - steps);
      break;
    case 'F' :
      move_forward(f, steps);
      break;
    default :
      break;
  }
}

void handle_rotation(Ferry &f, int steps) {

  switch(steps) {
    case 90 :
      std::swap(f.waypoint[0], f.waypoint[1]);
      f.waypoint[0] = -f.waypoint[0];
      break;
    case 180:
      f.waypoint[0] = -f.waypoint[0];
      f.waypoint[1] = -f.waypoint[1];
      break;
    case 270:
      std::swap(f.waypoint[0], f.waypoint[1]);
      f.waypoint[1] = -f.waypoint[1];
      break;
    default :
      std::cout << "DEFAULT CASE!" << std::endl;
      break;
  }
}

void move_forward(Ferry &f, int steps) {
  for(int i=0;i<2;i++)
    f.distance_moved[i] += steps*f.waypoint[i];
}

void print_ferry(Ferry f) {
  std::cout << "Waypoint: [ " << f.waypoint[0] << ", " <<
    f.waypoint[1] << "]";
  std::cout << std::endl;
  std::cout << "Location: [ " << f.distance_moved[0] << ", " <<
    f.distance_moved[1] << "]";
  std::cout << std::endl;
}

// Check Left rotation
// Then check movement
