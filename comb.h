#include <iostream>
#include <vector>

#ifndef COMB_H
#define COMB_H

class comb {
public:
  comb (std::vector<double> reciepts, double half) : inputs(reciepts), target(half){
    populate_v();
  }
  std::vector<double> inputs;
  double target;
  std::vector<int> indexes;
  std::vector<std::vector<int>> index_v;
  std::vector<std::pair<double, std::vector<double>>> v;

  void populate_index_v();
  void populate_v();
};

void comb::populate_index_v() {
  for (size_t i = 0; i < inputs.size(); i++) {
    indexes.push_back(i); //Populate indexes, attempt to avoid confusion by duplicated numbers
  }

  for (size_t length = 1; length <= indexes.size(); length++) {
    for (size_t i = 0; i < indexes.size() - (length - 1); i++) { // length - 1 is to reduce unnecessary loops
      if (length == 1) {
        std::vector<int> buff{indexes[i]};
        index_v.push_back(buff);
      } else {
        size_t size = index_v.size();
        for (size_t vpos = 0; vpos < size; vpos++) {
          if ((index_v[vpos]).size() == (length - 1) && index_v[vpos][0] > indexes[i]) {
            std::vector<int> buffer = index_v[vpos];
            buffer.insert(buffer.begin(), indexes[i]);
            index_v.push_back(buffer);
          }
        }
      }
    }
  }
}

void comb::populate_v() {
  populate_index_v();
  for (size_t i = 0; i < index_v.size(); i++) {
    std::vector<double> buffer;
    double sub_sum = 0;
    for (size_t j = 0; j < index_v[i].size(); j++) {
      double value = inputs[index_v[i][j]];
      buffer.push_back(value);
      sub_sum = sub_sum + value;
    }
    double dist = target - sub_sum;
    if (dist < 0) {
      dist = dist*(-1);
    }
    v.push_back(std::make_pair(dist, buffer));
    std::cout << "\r[";
    int progress = (i*30 / index_v.size());
    for (size_t j = 0; j < progress; j++) {
      std::cout << "I";
    }
    for (size_t j = 0; j < 30 - progress; j++) {
      std::cout << " ";
    }
    std::cout << "]    ";
    std::cout << i << "/" << index_v.size();
  }
}

#endif
