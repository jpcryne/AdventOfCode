#include<iostream>
#include<fstream>
#include<regex>
#include<sstream>
#include<unordered_set>
#include<set>

struct ticket_field {
  std::string name;
  int range_1[2];
  int range_2[2];
};

std::vector<int> parse_ticket(std::string s);
bool check_ticket(std::vector<int> t, std::vector<ticket_field> temp);
void print_template(std::vector<ticket_field> temp);
std::vector<int> determine_fields(std::vector<std::vector<int>> tickets, std::vector<ticket_field> temp);

int main(void) {

  // Get the fields on the ticket
  std::ifstream input("input.txt");
  std::string line;
  std::regex pieces_regex("([a-z\\s]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
  std::smatch pieces_match;
  std::vector<ticket_field> ticket_template;
  while(getline(input, line)) {
    if (line == "") break;

    std::regex_search(line, pieces_match, pieces_regex);

    ticket_field tf;
    tf.name = pieces_match[1];
    tf.range_1[0] = stoi(pieces_match[2]);
    tf.range_1[1] = stoi(pieces_match[3]);
    tf.range_2[0] = stoi(pieces_match[4]);
    tf.range_2[1] = stoi(pieces_match[5]);

    ticket_template.push_back(tf);

  }

  // Get own ticket
  getline(input, line);
  getline(input, line);
  std::vector<int> my_ticket = parse_ticket(line);

  // Get nearby tickets
  getline(input, line);
  getline(input, line);

  std::vector<std::vector<int>> nearby_tickets;
  while(getline(input, line)) {
    nearby_tickets.push_back(parse_ticket(line));
  }

  // Part 1 check for invalids
  int64_t sum{0};
  std::vector<std::vector<int>> valid_tickets;
  for(int i=0; i<nearby_tickets.size();i++) {
    bool tmp = check_ticket(nearby_tickets.at(i), ticket_template);
    if(tmp) {
      valid_tickets.push_back(nearby_tickets.at(i));
    }
  }

  std::cout << valid_tickets.size() << std::endl;

  // Check valid tickets for columns
  valid_tickets.push_back(my_ticket);
  std::vector<int> poss_cols = determine_fields(valid_tickets, ticket_template);
  int64_t mult{1};
  for(int i=0; i < ticket_template.size(); i++) {
    if(ticket_template.at(i).name.substr(0, 9) == "departure") {
      std::cout << "Field: " << ticket_template.at(i).name <<
        ", Column: " << poss_cols.at(i) <<
        ", Value: " << my_ticket[poss_cols.at(i)] << std::endl;
      mult *= my_ticket[poss_cols.at(i)];
    }
  }
  std::cout << mult << std::endl;

  return 0;
}

std::vector<int> determine_fields(std::vector<std::vector<int>> tickets, std::vector<ticket_field> temp) {

  std::vector<std::set<int>> possible_fields;
  for(int i=0;i<temp.size();i++) {
    std::set<int> fields;
    for(int j=0;j<tickets.at(0).size();j++) {
      int valid = true;
      for(int k=0;k<tickets.size();k++) {
        int num = tickets.at(k)[j];
        if(!((num >= temp.at(i).range_1[0] && num <= temp.at(i).range_1[1]) || (num >= temp.at(i).range_2[0] && num <= temp.at(i).range_2[1]))) {
            if(j == 3 && i == 7) {
              std::cout << "k = " << k << std::endl;
              std::cout << "tickets.at(k)[0] = " << tickets.at(k)[0] << std::endl;
              std::cout << "!((" << num << ">= " << temp.at(j).range_1[0] << " &&  " << num << "<=" << temp.at(j).range_1[1] << ")" << " || " << "(" << num << ">=" <<  temp.at(j).range_2[0] << " && " << num << " <= " << temp.at(j).range_2[1] << "))" << std::endl;
            }
            valid = false;
        }
      }
      if(valid) {
        fields.insert(j);
      }
    }
    possible_fields.push_back(fields);
  }

  int sum{0};
  while(sum != possible_fields.size()) {
    sum = 0;
    for(int i=0;i<possible_fields.size();i++) {
      if(possible_fields.at(i).size() == 1) {
        // extract element
        int el = *possible_fields.at(i).begin();
        for(int j=0;j<possible_fields.size();j++) {
          if(j==i) continue;
          // remove from other sets
          possible_fields.at(j).erase(el);
        }
      }
      sum += possible_fields.at(i).size();
    }
    std::cout << sum << std::endl;
  }

  std::vector<int> tmp;
  for(int i=0;i<possible_fields.size();i++)
    tmp.push_back(*possible_fields.at(i).begin());

  return tmp;
}

bool check_ticket(std::vector<int> t, std::vector<ticket_field> temp) {
  int64_t sum{0};
  bool final_valid = true;
  for(int i=0;i<t.size();i++) {
    int num = t.at(i);
    bool valid = false;
    for(int j=0;j<temp.size();j++) {
      if((num >= temp.at(j).range_1[0] && num <= temp.at(j).range_1[1]) ||
          (num >= temp.at(j).range_2[0] && num <= temp.at(j).range_2[1])) {
            valid = true;
          }
    }
    if(!valid) {
      sum+=num;
      final_valid = false;
    }
  }

  return final_valid;
}


std::vector<int> parse_ticket(std::string s) {
  std::vector<int> v;

  std::stringstream ss(s);

  int i;

  while (ss >> i) {
    v.push_back(i);

    if (ss.peek() == ',')
        ss.ignore();
  }

  return v;
}
