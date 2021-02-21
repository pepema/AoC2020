#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using Adapters = std::vector<int>;

void PrintValues(const Adapters& as){
  std::cout << "------------" << std::endl;
  for(const auto& a : as){
    std::cout << a << std::endl;
  }
  std::cout << "------------" << std::endl;
}

void GetValues(Adapters& a){
  std::ifstream file("input.txt");
  std::string line;
  std::size_t pos;
  while(std::getline(file,line)){
    a.push_back(stoll(line));
  }
  std::sort(a.begin(),a.end());
  file.close();
}

std::pair<int,int> CalculateDiffs(const Adapters& adapters){
  int one_diff = 0;
  //one instance of where the difference will be three will always
  //happen because of build in adapter
  int three_diff = 1;
  int prev = 0;
  for(const auto& a : adapters){
    if(a-prev==3) three_diff++;
    else if(a-prev==1) one_diff++;
    prev = a;
  }

  return std::make_pair(one_diff,three_diff);
}

int main(){
  Adapters adapters;
  GetValues(adapters);
  PrintValues(adapters);
  std::pair<int,int> diffs = CalculateDiffs(adapters);
  std::cout << "one diffs: " << diffs.first << " three diffs: " << diffs.second << std::endl;
  std::cout << "times each other: " << diffs.first*diffs.second << std::endl;
  return 0;
}