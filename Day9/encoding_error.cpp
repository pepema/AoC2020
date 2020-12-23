#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <set>

using Values = std::vector<long long>;

void PrintValues(const Values& v){
  std::cout << "------------" << std::endl;
  for(const auto& a : v){
    std::cout << a << std::endl;
  }
  std::cout << "------------" << std::endl;
}

long long FindInvalid(const Values& v,int preamble_size){
  std::vector<long long> preamble_sums = {};
  for(int i=0;i<preamble_size+1;i++){
    for(int j=i+1;j<preamble_size;j++){
      preamble_sums.push_back(v[i]+v[j]);
    }
  }
  bool valid_found = false;
  for(int i=preamble_size;i<v.size();i++){
    //PrintValues(preamble_sums);
    for(const auto& a : preamble_sums){
      if(v[i]==a) valid_found = true;
    }
    if(!valid_found){
      return v[i];
    }
    else{
      valid_found = false;
      preamble_sums.clear();
      for(int j=i-preamble_size+1;j<=i;j++){
        for(int k=j+1;k<=i;k++){
          //std::cout << "sum of " << k << " and " << j << std::endl;
          preamble_sums.push_back(v[j]+v[k]);
        }
      }
    }
  }
  return -1;
}

long long FindContiguousSet(const Values& values, long long sum){
  long long set_sum = 0;
  int first,next = 0;
  for(int i=0;i<values.size();i++){
    first=next=i;
    while(set_sum<sum){
      set_sum += values[next];
      next++;
    }
    if(set_sum==sum){
      int max = 0;
      int min = INT32_MAX;
      for(int j=first;j<next-2;j++){
        if(values[j]<min) min = values[j];
        if(values[j]>max) max = values[j];
      }
      return min+max;
    }
    set_sum = 0;
  }
  return -1;
}

void GetValues(Values& values){
  std::ifstream file("input.txt");
  std::string line;
  std::size_t pos;
  while(std::getline(file,line)){
    values.push_back(stoll(line));
  }
  file.close();
}

int main(){
  Values values;
  GetValues(values);
  std::cout << FindContiguousSet(values,FindInvalid(values,25)) << std::endl;
  return 0;
}