#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<cmath>
#include<map>

struct mask {
  std::vector<int64_t> index;
  std::vector<int64_t> value;
};

struct base2 {
  std::set<int64_t> power_index;
};

mask get_mask(std::string s);
void print64_t_mask(mask m);
base2 base_two_convert(int64_t n);
void print64_t_base2(base2 b);
int64_t apply_mask(base2 b, mask m);

int main(void) {
  std::ifstream input("input.txt");
  std::string line;
  mask m;
  std::map<int64_t,int64_t> mp;

  while(getline(input, line)) {
    if(line.substr(0,4) == "mask") {
      //std::cout << line.substr(7, 41) << std::endl;
      m = get_mask(line.substr(7, 41));
      print64_t_mask(m);
    } else {
      int64_t key = stoll(line.substr(line.find("[")+1, line.find("]")-4));
      int64_t val = stoll(line.substr(line.find("=") + 2, line.size()));
      //std::cout << line.substr(line.find("=") + 2, line.size()) << std::endl;
      base2 b = base_two_convert(val);
      //print64_t_base2(b);
      //std::cout << "After Mask: " << apply_mask(b, m) << std::endl;
      mp.insert_or_assign(key, apply_mask(b, m));
    }
  }

  // Return sum
  int64_t sum{0};
  for(auto const& [key, val] : mp) {
    sum += val;
    std::cout << key         // string (key)
          << ':'
          << val        // string's value
          << std::endl ;
  }
  std::cout << sum << std::endl;
  return 0;
}


mask get_mask(std::string s) {
  mask m;
  int i{0};

  for(char &c : s) {
    if(c != 'X') {
      m.index.push_back(35-i);
      m.value.push_back((int) c - '0');
    }
    i++;
  }

  return m;
}


int64_t apply_mask(base2 b, mask m) {
  std::cout << "Before:";
  print64_t_base2(b);
  for(int i=0;i<m.index.size();i++) {
    if(m.value.at(i)) {
      b.power_index.insert(m.index.at(i));
    } else {
      b.power_index.erase(m.index.at(i));
    }
  }
  std::cout << "After:";
  print64_t_base2(b);
  int64_t sum{0};
  for(auto i : b.power_index) {
    sum += pow(2, i);
  }
  return sum;
}


base2 base_two_convert(int64_t n) {
  int i{0};
  base2 b;

  while(n > 0) {
    if(n % 2 == 1) {
      b.power_index.insert(i);
    }
    n /= 2;
    i++;
  }

  return b;
}

void print64_t_base2(base2 b) {
  std::cout << "Powers [";
  for(auto i : b.power_index) {
    std::cout << i << ", ";
  }
  std::cout << "]" << std::endl;
}

void print64_t_mask(mask m) {
  std::cout << "Index [";
  for(int i=0;i<m.index.size();i++) {
    std::cout << m.index.at(i) << ", ";
  }
  std::cout << "]" << std::endl;
  std::cout << "Value [";
  for(int i=0;i<m.value.size();i++) {
    std::cout << m.value.at(i) << ", ";
  }
  std::cout << "]" << std::endl;
}
