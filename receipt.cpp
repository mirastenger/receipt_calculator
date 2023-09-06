#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include "comb.h"

void gather_input(std::vector<double>& input_vec){
  double input;
  std::cout << "Welcome. Please input all your receipt prices. Enter 0 when complete." << std::endl;

  std::cin >> input;
  while(input > 0){
    input_vec.push_back(input);
    std::cin >> input;
  }
}

void generate_vals(std::vector<double> input, double& total, double& half_total){
  for(double value : input){
    total += value;
  }
  half_total = (total / 2);
}

void print_result(const std::vector<std::pair<double, std::vector<double>>>& receipt_combs, const double& total, const double& half_total){
  double found_total = 0;
  std::cout << "\n\nThe total of the receipts is " << total << " and the combination closest to the half total of " << half_total << " is:" << std::endl;
  for (double value : receipt_combs[0].second){
    std::cout << value << ", ";
    found_total += value;
  }
  std::cout << std::endl << "with a total of " << found_total;
}

int main(){
  std::vector<double> input;
  double total = 0.0, half_total = 0.0;

  gather_input(input);
  generate_vals(input, total, half_total);
  comb c(input, half_total);
  std::sort(c.v.begin(), c.v.end(),
    [](std::pair<double, std::vector<double>> r1, std::pair<double, std::vector<double>> r2) {return r1.first < r2.first;});
  print_result(c.v, total, half_total);

}
