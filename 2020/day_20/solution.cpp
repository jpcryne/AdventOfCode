#include<iostream>
#include<fstream>
#include<vector>

class Coordinate {
public:
  int x;
  int y;

  Coordinate(int i1, int i2) {
    x = i1;
    y = i2;
  }
  // Overload equals
  bool operator==(const Coordinate& otherPoint) const {
  if (this->x == otherPoint.x && this->y == otherPoint.y) return true;
  else return false;
  }
};

// Overload hash for Coordinate
namespace std {
    template <> struct hash<Coordinate> {
        size_t operator()(const Coordinate & x) const {
            std::hash<std::string> h;
            std::string s = "";
            s = std::to_string(x.x)  + "-" + std::to_string(x.y);
            return h(s);
            // or simply return x.code
            // or do something more interesting,
            // like xor'ing hashes from both members of struct
        }
    };
}

class Tile {
public:
  int64_t id;
  std::vector<Coordinate> active;
  int dimension;

  Tile(int64_t i, std::vector<Coordinate> act, int dim) {
    id = i;
    active = act;
    dimension = dim;
  }

  std::string make_string() {
    std::string s;
    s += "id: " + std::to_string(id) + ", dim: " + std::to_string(dimension) += ", active coords: [";
    for(int i=0; i<active.size(); i++) {
      s += "(" + std::to_string(active.at(i).x) + ", " + std::to_string(active.at(i).y) + "), ";
    }
    s += "]";
    return s;
  }
};

int main(void) {
  std::ifstream input("test.txt");
  std::string line;
  std::vector<Coordinate> active_coords;
  std::vector<Tile> v;
  int64_t id;
  int dim{0};

  while(getline(input, line)) {
    if(line == "") {
      Tile t = Tile(id, active_coords, dim-1);
      std::cout << t.make_string() << std::endl;;
      v.push_back(t);
      v.clear();
      active_coords.clear();
      dim = 0;
      continue;
    }
    dim++;
    if(line.at(0) == 'T') {
      id = stoll(line.substr(line.find(' '), line.find(':')));
    } else {
      int col{0};
      for(char &c : line) {
        if(c == '#')
          active_coords.push_back(Coordinate(dim-2,col));
        col++;
      }
    }

  }

  return 0;
}
