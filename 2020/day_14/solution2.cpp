#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<cmath>
#include<map>

struct mask {
  std::vector<int64_t> index;
  std::vector<int64_t> value;
  std::vector<int64_t> floating_index;
};

struct base2 {
  std::set<int64_t> power_index;
};

mask get_mask(std::string s);
void print_mask(mask m);
base2 base_two_convert(int64_t n);
void print_base2(base2 b);
int64_t apply_mask(base2 b, mask m);
std::vector<int64_t> permutations(std::vector<int64_t> pow_ind, std::vector<int64_t> ans);

int main(void) {
  std::ifstream input("input.txt");
  std::string line;
  mask m;
  std::map<int64_t,int64_t> mp;

  while(getline(input, line)) {
    if(line.substr(0,4) == "mask") {
      
      m = get_mask(line.substr(7, 41));
      print_mask(m);
    } else {
      int64_t key = stoll(line.substr(line.find("[")+1, line.find("]")-4));
      int64_t val = stoll(line.substr(line.find("=") + 2, line.size()));
      base2 b = base_two_convert(key);
      int64_t tmp = apply_mask(b, m);
      std::vector<int64_t> perms;
      perms = permutations(m.floating_index, perms);

      for(int i=0; i<perms.size();i++) {
        mp.insert_or_assign(tmp+perms.at(i), val);
        std::cout << perms.at(i) << ' ';
      }
      std::cout << std::endl;
    }
  }

  // Return sum
  std::cout << "Answer:" << std::endl;
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
    if(c == '1') {
      m.index.push_back(35-i);
      m.value.push_back((int) c - '0');
    } else if(c == 'X') {
      m.floating_index.push_back(35-i);
    }
    i++;
  }

  return m;
}


int64_t apply_mask(base2 b, mask m) {

  std::cout << "Before:";
  print_base2(b);
  for(int i=0;i<m.index.size();i++) {
    if(m.value.at(i)) {
      b.power_index.insert(m.index.at(i));
    }
  }
  for(int i=0;i<m.floating_index.size();i++) {
    b.power_index.erase(m.floating_index.at(i));
  }
  std::cout << "After:";
  print_base2(b);
  int64_t sum{0};
  for(auto i : b.power_index) {
    sum += pow(2, i);
  }

  return sum;
}

std::vector<int64_t> permutations(std::vector<int64_t> pow_ind, std::vector<int64_t> ans) {
  if(pow_ind.size() == 1) {
    ans.push_back(0);
    ans.push_back(pow(2, pow_ind.back()));
    return(ans);
  } else {
    int64_t tmp = pow(2, pow_ind.back());
    pow_ind.pop_back();
    ans = permutations(pow_ind, ans);
    int sze = ans.size();
    for(int i=0;i<sze;i++) {
      ans.push_back(ans[i] + tmp);
    }
    return ans;
  }
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

void print_base2(base2 b) {
  std::cout << "Powers [";
  for(auto i : b.power_index) {
    std::cout << i << ", ";
  }
  std::cout << "]" << std::endl;
}

void print_mask(mask m) {
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
