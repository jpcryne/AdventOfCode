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
int check_ticket(std::vector<int> t, std::vector<ticket_field> temp);
void print_template(std::vector<ticket_field> temp);
std::vector<std::string> determine_fields(std::vector<std::vector<int>> tickets, std::vector<ticket_field> temp);

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
    int tmp = check_ticket(nearby_tickets.at(i), ticket_template);
    sum += tmp;
    if(tmp == 0) {
      valid_tickets.push_back(nearby_tickets.at(i));
    }
  }

  std::cout << valid_tickets.size() << std::endl;

  std::cout << "Invalid Percent: " << sum << std::endl;

  return 0;
}

int check_ticket(std::vector<int> t, std::vector<ticket_field> temp) {
  int64_t sum{0};
  for(int i=0;i<t.size();i++) {
    int num = t.at(i);
    bool valid = false;
    for(int j=0;j<temp.size();j++) {
      if((num >= temp.at(j).range_1[0] && num <= temp.at(j).range_1[1]) ||
          (num >= temp.at(j).range_2[0] && num <= temp.at(j).range_2[1])) {
            valid = true;
          }
    }
    if(!valid)
      sum+=num;
  }

  return sum;
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
