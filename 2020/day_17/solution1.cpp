#include<iostream>
#include<fstream>
#include<unordered_set>
#include<vector>

class Coordinate {
public:
  int x;
  int y;
  int z;

  Coordinate(int i1, int i2, int i3) {
    x = i1;
    y = i2;
    z = i3;
  }
  // Overload equals
  bool operator==(const Coordinate& otherPoint) const {
  if (this->x == otherPoint.x && this->y == otherPoint.y && this->z == otherPoint.z) return true;
  else return false;
  }
};

// Overload hash for Coordinate
namespace std {
    template <> struct hash<Coordinate> {
        size_t operator()(const Coordinate & x) const {
            std::hash<std::string> h;
            std::string s = "";
            s = to_string(x.x)  + "-" + to_string(x.y) + "-" + to_string(x.z);
            return h(s);
            // or simply return x.code
            // or do something more interesting,
            // like xor'ing hashes from both members of struct
        }
    };
}

class Cube {
public:
  std::unordered_set<Coordinate> active_squares;
  std::pair<int64_t, int64_t> bounds_x;
  std::pair<int64_t, int64_t> bounds_y;
  std::pair<int64_t, int64_t> bounds_z;
  int generation;

  Cube(std::unordered_set<Coordinate> active, int x1, int x2, int y1, int y2, int z1, int z2) {
    active_squares = active;
    bounds_x = std::make_pair(x1, x2);
    bounds_y = std::make_pair(y1, y2);
    bounds_z = std::make_pair(z1, z2);
    generation = 0;
  }

  void generate_next_step() {
    generation++;
    bounds_x = std::make_pair(bounds_x.first - 1, bounds_x.second+1);
    bounds_y = std::make_pair(bounds_y.first - 1, bounds_y.second+1);
    bounds_z = std::make_pair(bounds_z.first - 1, bounds_z.second+1);

    std::unordered_set<Coordinate> to_check = squares_to_check();
    std::vector<Coordinate> new_active;

    for(const Coordinate c : to_check) {
      int num_active = active_neighbours(c);
      if(active_squares.find(c) != active_squares.end()) {
        if(num_active == 2 || num_active == 3)
          new_active.push_back(c);
      } else {
        if(num_active == 3)
          new_active.push_back(c);
      }
    }
    active_squares.clear();
    for(int i=0;i<new_active.size();i++)
      active_squares.insert(new_active.at(i));

    update_bounds();
  }

  void update_bounds() {
    int max_x{0}, max_y{0}, max_z{0};
    int min_x{0}, min_y{0}, min_z{0};
    int first_loop = 1;
    for(const Coordinate c : active_squares) {
      if(first_loop) {
        first_loop = 0;
        max_x = c.x; min_x = c.x;
        max_y = c.y; min_y = c.y;
        max_z = c.z; min_z = c.z;
        continue;
      }
      max_x = (c.x > max_x) ? c.x : max_x; min_x = (c.x < min_x) ? c.x : min_x;
      max_y = (c.y > max_y) ? c.y : max_y; min_y = (c.y < min_y) ? c.y : min_y;
      max_z = (c.z > max_z) ? c.z : max_z; min_z = (c.z < min_z) ? c.z : min_z;
    }
    bounds_x.first = min_x; bounds_x.second = max_x;
    bounds_y.first = min_y; bounds_y.second = max_y;
    bounds_z.first = min_z; bounds_z.second = max_z;
  }

  // Check any active or neighbour of active
  std::unordered_set<Coordinate> squares_to_check() {
    std::unordered_set<Coordinate> to_check;
    for(const Coordinate &c : active_squares) {
      for(int i=-1;i<=1;i++) {
        for(int j=-1;j<=1;j++) {
          for(int k=-1;k<=1;k++) {
            Coordinate new_coord = Coordinate(c.x+i, c.y+j, c.z+k);;
            to_check.insert(new_coord);
          }
        }
      }
    }
    return(to_check);
  }

  int active_neighbours(Coordinate c) {
    int active{0};
    // Check above
    for(int i=-1;i<=1;i++) {
      for(int j=-1;j<=1;j++) {
        for(int k=-1;k<=1;k++) {
          if(i == 0 && j == 0 && k == 0) continue;
          Coordinate nbr = Coordinate(c.x+i, c.y+j, c.z+k);
          if(active_squares.find(nbr) != active_squares.end()) {
            active++;
          }
        }
      }
    }
    return active;
  }

  void print() {
    std::cout << "generation: " << generation << std::endl;
    for(int i=bounds_z.first; i<=bounds_z.second;i++) {
      std::cout << "z=" << i << std::endl;
      for(int j=bounds_x.first; j<=bounds_x.second;j++) {
        for(int k=bounds_y.first; k<=bounds_y.second;k++) {
          Coordinate coord = Coordinate(j,k,i);
          if(active_squares.find(coord) != active_squares.end()) {
            std::cout << "#";
          } else {
            std::cout << ".";
          }
        }
        std::cout << std::endl;
      }
      std::cout << "\n\n";
    }
  }

};


int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  int line_num{0};
  int depth{0};
  std::unordered_set<Coordinate> initial_active;
  int max_x{0};

  while(getline(input, line)) {
    int char_num{0};
    for(char &c : line) {
      if(c == '#') {
        Coordinate coord = Coordinate(line_num, char_num, 0);
        initial_active.insert(coord);
      }
      char_num++;
      max_x = char_num;
    }
    line_num++;
  }

  // Part 1
  Cube cube = Cube(initial_active, 0, max_x-1, 0, line_num-1, 0,0);
  while(cube.generation != 6) {
    cube.generate_next_step();
  }
  std::cout << cube.active_squares.size() << std::endl;


  return 0;
}
