#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
#define DIM 2

class Coordinate {
  public :
  int x;
  int y;
  int colour;

  Coordinate(int *a) {
    x = a[0];
    y = a[1];
    colour = 1;
  }

  void flip() {
    colour++;
    colour = colour % 2;
  }

  void print_coordinate() {
    std::cout << "Coord: [" << x << ", " << y << "]";
    std::cout << ", Colour: " << ((colour == 1) ? "BLACK" : "WHITE") << std::endl;
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
            s = to_string(x.x)  + "-" + to_string(x.y);
            return h(s);
            // or simply return x.code
            // or do something more interesting,
            // like xor'ing hashes from both members of struct
        }
    };
}

std::vector<std::string> get_directions(std::string s, int *dir) {
  std::vector<std::string> result;

  for(int i=0;i<s.size();i++) {
    char c = s.at(i);
    if(c == 'e') {
      result.push_back("e");
      dir[1]+=2;
    } else if(c == 'w') {
      result.push_back("w");
      dir[1]-=2;
    } else if(c == 'n') {
      if(s.at(i+1) == 'e') {
        result.push_back("ne");
        dir[0]++;
        dir[1]++;
      } else {
        result.push_back("nw");
        dir[0]++;
        dir[1]--;
      }
      i++;
    } else if(c == 's') {
      if(s.at(i+1) == 'e') {
        result.push_back("se");
        dir[0]--;
        dir[1]++;
      } else {
        result.push_back("sw");
        dir[0]--;
        dir[1]--;
      }
      i++;
    }
  }
  return result;
}

int main(void) {

  //Read input
  std::ifstream input("input.txt");
  std::string line;
  std::unordered_set<Coordinate> all_tiles;
  while(getline(input, line)) {
    int coord[DIM] = {0};
    std::vector<std::string> dirs = get_directions(line, coord);
    Coordinate dest_tile = Coordinate(coord);

    // Look if already flipped
    auto search = all_tiles.find(dest_tile);;
    if (search != all_tiles.end()) {
      if((*search).colour) {
        dest_tile.flip();
      }
      all_tiles.erase(search);
    }
    all_tiles.insert(dest_tile);
    dest_tile.print_coordinate();
  }
  // Count number of black tiles
  int sum{0};
  for(auto e : all_tiles)
    sum += e.colour;
  std::cout << "Part 1: " << sum << std::endl;

  return 0;
}
