#include<iostream>
#include<fstream>

#define NUM_BUSES 9 //5 // 9

void print64_t_array(int64_t a[], int64_t len);
int64_t search_solution(int64_t buses[], int64_t times[], int64_t len);
int64_t crt_solution(int64_t buses[], int64_t times[], int64_t len);
int64_t modInverse(int64_t a, int64_t m);

int main(void) {

  std::ifstream input("input.txt");

  std::string line;

  getline(input, line);
  getline(input, line);
  line+=',';
  //std::cout << line << std::endl;

  int64_t time{0};
  int64_t i{0};
  int64_t bus_nums[NUM_BUSES];
  int64_t arrive_time[NUM_BUSES];
  std::string tmp;

  for(char &c : line) {
    if(c == ',') {
      if(tmp != "x") {
        bus_nums[i]    = stoi(tmp);
        arrive_time[i] = time;
        i++;
        //std::cout << stoi(tmp) << std::endl;
      }
      tmp.clear();
      time++;
    } else {
      tmp.push_back(c);
    }
  }
  
  std::cout <<
    crt_solution(bus_nums, arrive_time, NUM_BUSES) <<
    std::endl;


  return 0;
}

void print64_t_array(int64_t a[], int64_t len) {
  for(int64_t i=0;i<len;i++)
    std::cout << a[i] << ", ";
  std::cout << std::endl;
}

int64_t search_solution(int64_t buses[], int64_t times[], int64_t len) {
  int64_t candidate{0};
  bool found = true;
  // LOOP THROUGH TIMES 0 MOD BUSES[0]
  for(int64_t i = 0; true; i++) {
    candidate += buses[0];
    found = true;

    //std::cout << "Candidate: " << candidate << std::endl;
    for(int64_t j = 1; j < len; j++) {
      //if(candidate == 1068788) std::cout << candidate << " % " << buses[j] << " = " << times[j] << std::endl;
      if(candidate % buses[j] != buses[j]-times[j]) {
        found = false;
        break;
      }
    }
    if(found) {
      break;
    }
  }

  return candidate;
}

int64_t crt_solution(int64_t buses[], int64_t times[], int64_t len) {
  int64_t sol{0};
  int64_t b, inv_b, big_m{1};
  for(int64_t i=0;i<len;i++) big_m *= buses[i];

  for(int64_t i=0;i<len;i++) {

    b     = big_m / buses[i];
    inv_b = modInverse(b, buses[i]);
    int64_t mod =  -times[i] % buses[i];

    while(mod < 0)
      mod += buses[i];

    sol += (mod) * b * inv_b;
    if(sol > big_m) sol = sol % big_m;
  }

  return sol;
}

// Returns modulo inverse of a with respect
// to m using extended Euclid Algorithm
// Assumption: a and m are coprimes, i.e.,
// gcd(a, m) = 1
int64_t modInverse(int64_t a, int64_t m)
{
    int64_t m0 = m;
    int64_t y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        int64_t q = a / m;
        int64_t t = m;

        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;

    return x;
}
