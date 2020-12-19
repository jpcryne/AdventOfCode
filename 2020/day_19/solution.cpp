#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<string>
#include<sstream>
#include<regex>

enum class RuleType {
  and_rule,
  or_rule,
  letter_rule
};

class Rule {
public :
  RuleType rule_type;
  std::vector<int> or1;
  std::vector<int> or2;
  std::vector<int> ands;
  char letter;

  Rule(RuleType rt, std::vector<int> o1, std::vector<int> o2, std::vector<int> as, char l) {
    rule_type = rt;
    or1 = o1;
    or2 = o2;
    ands = as;
    letter = l;
  }

  bool operator==(const Rule& otherRule) const {
    if(this->rule_type == otherRule.rule_type) {
      if(this->rule_type == RuleType::letter_rule) {
        if (this->letter == otherRule.letter) return true;
      } else if(this->rule_type == RuleType::or_rule) {
        if(this->or1.size() == otherRule.or1.size() && this->or2.size() == otherRule.or2.size()) {
          bool b = true;
          for(int i=0;i<otherRule.or1.size();i++) {
            if(this->or1.at(i) != otherRule.or1.at(i))
              b = false;
          }
          for(int i=0;i<otherRule.or2.size();i++) {
            if(this->or2.at(i) != otherRule.or2.at(i))
              b = false;
          }
          return b;
        }
        } else if(this->rule_type == RuleType::and_rule) {
          if(this->ands.size() == otherRule.ands.size()) {
            bool b = true;
            for(int i=0; i<otherRule.ands.size();i++) {
              if(this->ands.at(i) != otherRule.ands.at(i)) {
                b = false;
              }
            }
            return b;
          }
        }
      }
      return false;
    }
};

std::string make_string(Rule r) {
  std::string s;
  if(r.rule_type == RuleType::and_rule) {
    for(auto e : r.ands) {
      s += std::to_string(e) + " ";
    }
  } else if(r.rule_type == RuleType::or_rule) {
      //s += std::to_string(r.or1.first) + " " + std::to_string(r.or1.second) + " | ";
      //s += std::to_string(r.or2.first) + " " + std::to_string(r.or2.second);
      for(auto e : r.or1) {
        s += std::to_string(e) + " ";
      }
      s+= " | ";
      for(auto e : r.or2) {
        s += std::to_string(e) + " ";
      }
  } else {
    s += "\"";
    s.push_back(r.letter);
    s += "\"";
  }
  return s;
}

// Overload hash for Rule
namespace std {
    template <> struct hash<Rule> {
        size_t operator()(const Rule & x) const {
            std::hash<std::string> h;
            std::string s = "";
            s = make_string(x);
            return h(s);
            // or simply return x.code
            // or do something more interesting,
            // like xor'ing hashes from both members of struct
        }
    };
}

Rule parse_rule(std::string s) {
  std::vector<int> as;
  std::vector<int> o1;
  std::vector<int> o2;
  Rule r = Rule(RuleType::letter_rule, o1, o2, as, '-');

  if(s.find('|') != std::string::npos) {

    std::regex pieces_regex("(\\d+) (\\d+) \\| (\\d+) (\\d+)");
    std::smatch pieces_match;
    std::regex_search(s, pieces_match, pieces_regex);
    if(pieces_match.size() < 5) {
      std::regex pieces_regex1("(\\d+) \\| (\\d+)");
      std::regex_search(s, pieces_match, pieces_regex1);
    }
    for(int i=1;i<pieces_match.size();i++) {
      if(i<=(pieces_match.size() / 2)) {
        o1.push_back(stoi(pieces_match[i]));
      } else {
        o2.push_back(stoi(pieces_match[i]));
      }
    }
    Rule r = Rule(RuleType::or_rule, o1, o2, as, '-');
    return r;

  } else if(s.find('\"') != std::string::npos) {
    Rule r = Rule(RuleType::letter_rule, o1, o2, as, s.at(1));
    return r;
  } else {
    std::stringstream ss(s);
    int x;
    while(ss >> x) {
      as.push_back(x);
    }
    Rule r = Rule(RuleType::and_rule, o1, o2, as, '-');
    return r;
  }

  return r;
}

std::pair<bool, int> follows_rule(std::string s, int rule, std::unordered_map<int, Rule> &m) {
  Rule r = m.find(rule)->second;
  bool b = true;
  int sum{0};

  if(r.rule_type == RuleType::letter_rule) {
    b = (s.at(0) == r.letter);
    sum = 1;

  } else if(r.rule_type == RuleType::and_rule) {
    //bool b = true;
    int x{0};
    for(auto e : r.ands) {

      std::pair<bool, int> tmp = follows_rule(s.substr(sum,s.size()), e, m);
      x = tmp.second;
      sum += x;
      b = (b && tmp.first);
      if(!b) break;
    }
  } else if(r.rule_type == RuleType::or_rule) {
    int x{0};
    for(auto e : r.or1) {
      std::pair<bool, int> tmp = follows_rule(s.substr(sum, s.size()), e, m);
      x = tmp.second;
      sum += x;
      b = (b && tmp.first);
      if(!b) break;
    }
    if(b) return std::make_pair(b, sum);
    b = true;x=0;sum=0;
    for(auto e : r.or2) {
      std::pair<bool, int> tmp = follows_rule(s.substr(sum, s.size()), e, m);
      x = tmp.second;
      sum += x;
      b = (b && tmp.first);
      if(!b) break;
    }
  }
  return std::make_pair(b, sum);
}

bool check_message(std::string s, std::unordered_map<int, Rule> &m) {
  //Rule rule_zero = m.find(0)->second;
  std::pair<bool, int> pr = follows_rule(s, 0, m);

  if(pr.second != s.size() && pr.first) {
    return false;
  }

  return follows_rule(s, 0, m).first;
}

int main(void) {

  std::ifstream input("input.txt");
  std::string line;
  std::unordered_map<int, Rule> rule_map;
  // Get rules
  while(getline(input, line)) {
    if(line == "") break;
    std::string rn_string = line.substr(0, line.find(':'));
    int rule_number = std::stoi(rn_string);
    Rule r = parse_rule(line.substr(line.find(':')+2, line.size()));
    rule_map.insert({rule_number, r});
  }


  std::vector<std::string> messages;
  while(getline(input, line)) {
    messages.push_back(line);
  }

  int sum{0};
  for(auto elem : messages) {

    sum+=check_message(elem, rule_map);
  }

  std::cout << "Part 1: " << sum << std::endl;

  return 0;
}
