#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

using Passport = std::unordered_map<std::string,std::string>;
using Passports = std::vector<Passport>;

void PrintPassports(const Passports& pp){
  for(const auto& i : pp){
    for(const auto& j : i){
      std::cout << j.first << " " << j.second << std::endl;
    }
    std::cout << "--------------" << std::endl;
  }
}

bool ValidPassport(const Passport& p){
  return (p.count("byr") && p.count("iyr") && p.count("eyr") && p.count("hgt") 
       && p.count("hcl") && p.count("ecl") && p.count("pid")) ? true : false;
}

int CountValidPassports(const Passports& pp){
  int valid_count = 0;
  for(const auto& p : pp){
    if(ValidPassport(p)) valid_count++;
  }
  return valid_count;
}

void GetPassports(Passports& pp){
  std::ifstream file("input.txt");
  std::string line;
  Passport p;
  std::size_t pos;
  while(std::getline(file,line)){
    std::stringstream ss;
    ss << line;
    std::string field;
    while(!ss.eof()){
      ss >> field;
      pos = field.find(":");
      if(field == ""){
        pp.push_back(p);
        p = {};
      }
      else{
        p[field.substr(0,pos)] = field.substr(pos+1);
      }
    }
  }
  file.close();
}

int main(){
  Passports passports;
  GetPassports(passports);
  std::cout << "valid passports: " << CountValidPassports(passports) << std::endl;
  return 0;
}