#include <iostream>
#include <fstream>

#define PREAMBLE 25
bool check_valid1(long long x, std::deque<long long> q);
long long find_weakness(long long x, std::deque<long long> q1, std::deque<long long> q2);
void print_queue(std::deque<long long> q);
long long get_min_max_queue_sum(std::deque<long long> q);

int main(void) {

  std::ifstream input("input.txt");

  long long a;
  std::deque<long long> store_queue;
  std::deque<long long> prev_nums;
  while (input >> a) {

    if(prev_nums.size() >= PREAMBLE) {

      if(!check_valid1(a, prev_nums)) {
        std::cout << "Invalid Number: " << a << std::endl;
        find_weakness(a, prev_nums, store_queue);
        break;
      }

      store_queue.push_back(prev_nums.front());
      prev_nums.pop_front();
    }

    prev_nums.push_back(a);

  }

}

/*
  Check if any members of queue sum to next number
*/
bool check_valid1(long long x, std::deque<long long> q) {
  for(int i = 0; i < q.size(); i++) {
    for(int j = 0; j < i; j++) {
      if(q[i] + q[j] == x) {
        return true;
      }
    }
  }
  return false;
}

/*
  Finds the contigious sequence
*/
long long find_weakness(long long x, std::deque<long long> q1, std::deque<long long> q2){
  // Combine queues
  int q1_size = q1.size();
  for(int i = 0; i < q1_size; i++) {
    q2.push_back(q1.front());
    q1.pop_front();
  }

  // Find contigious sums
  std::deque<long long> tmp;
  for(int i = 0; i < q2.size(); i++) {
    long long sum = q2[i];
    tmp.push_back(q2[i]);
    for(int j = i+1; q2[j] != x; j++) {
      sum+=q2[j];
      tmp.push_back(q2[j]);
      if(sum > x) {
        tmp.clear();
        break;
      } else if(sum == x) {
        print_queue(tmp);
        std::cout << "Weakness is: " << get_min_max_queue_sum(tmp) << std::endl;
        return 0;
      }
    }
  }

  return 1;
}

/*
  Return the weakness
*/
long long get_min_max_queue_sum(std::deque<long long> q) {
  long long max{0}, min{0};

  for(int i = 0; i < q.size(); i++) {
    if(i == 0) {
      max = q[i];
      min = q[i];
    }
    if(q[i] > max) max = q[i];
    if(q[i] < min) min = q[i];
  }

  return min + max;
}

/*
  Prints a long long queue
*/
void print_queue(std::deque<long long> q) {

  for(int i = 0; i < q.size(); i++) {
    std::cout << q[i] << ", ";
  }
  std::cout << std::endl;

}
