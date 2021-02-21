#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using BagAndAmount = std::pair<int,std::string>;
using IncludedBags = std::vector<BagAndAmount>;
using Rules = std::unordered_map<std::string,IncludedBags>;

void PrintRules(const Rules& r){
  std::cout << "--------------------" << std::endl;
  for(const auto& a : r){
    std::cout << "rules for: " << a.first << std::endl;
    for(const auto& i : a.second){
      std::cout << "amount: " << i.first << " of type: " << i.second << std::endl;
    }
    std::cout << "--------------------" << std::endl;
  }
}

bool IsDirectHolder(const IncludedBags& ib){
  for(const auto& a : ib){
    if(!a.second.find("shiny gold")) return true;
  }
}

int amount(const Rules& r){
  int amount = 0;
  for(const auto& a : r){
    if(IsDirectHolder(a.second)) amount++;
  }
  return amount;
}

void GetRules(Rules& r){
  std::ifstream file("testing_input.txt");
  std::string line;
  IncludedBags ib = {};
  while(std::getline(file,line)){
    std::size_t pos = line.find("contain");
    std::string bag = line.substr(0,pos);
    BagAndAmount next = {};
    for(pos+=8;pos<line.length();pos++){
      if(isdigit(line[pos])){
        next.first = line[pos] - '0';
        pos++; //skip next space
      } else if(line[pos]==',' || line[pos]=='.'){
        if(line[pos-1]!='s') next.second+='s';
        //check that there's actually a rule
        if(next.first) ib.push_back(next);
        pos++;
        next.second = "";

      } else {
        next.second += line[pos];
      }
    }
    r[bag]=ib;
    ib = {};
  }
  file.close();
}

int main(){
 Rules r;
 GetRules(r);
 std::cout << amount(r) << std::endl;
 //PrintRules(r);
}