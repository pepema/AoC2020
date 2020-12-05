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

bool CheckBYR(const Passport& p){
 return (std::stoi(p.at("byr"))>=1920 && std::stoi(p.at("byr"))<=2002) ? true : false;
}

bool CheckIYR(const Passport& p){
 return (std::stoi(p.at("iyr"))>=2010 && std::stoi(p.at("iyr"))<=2020) ? true : false;
}

bool CheckEYR(const Passport& p){
 return (std::stoi(p.at("eyr"))>=2020 && std::stoi(p.at("eyr"))<=2030) ? true : false;
}

bool CheckHGT(const Passport& p){
 if(p.at("hgt").substr(p.at("hgt").length()-2)=="cm"){
   return (std::stoi(p.at("hgt"))>=150 && std::stoi(p.at("hgt"))<=193) ? true : false;
 }
 else if(p.at("hgt").substr(p.at("hgt").length()-2)=="in"){
   return (std::stoi(p.at("hgt"))>=59 && std::stoi(p.at("hgt"))<=76) ? true : false;
 }
 else return 0;
}

bool CheckHCL(const Passport& p){
  if(p.at("hcl")[0]=='#'){
    for(int i=1;i<7;i++){
      if(!isxdigit(p.at("hcl")[i])) return false;
    }
  return true;
  }
  return false;
}

bool CheckECL(const Passport& p){
 return (p.at("ecl")=="amb" || p.at("ecl")=="blu" || p.at("ecl")=="brn" || p.at("ecl")=="gry" || 
         p.at("ecl")=="grn" || p.at("ecl")=="hzl" || p.at("ecl")=="oth") ? true : false;
}

bool CheckPID(const Passport& p){
  for(int i=0;i<9;i++){
    if(!isdigit(p.at("pid")[i])) return false;
  }
  return p.at("pid").length() == 9;
}

bool CheckALL(const Passport& p){
  return (CheckBYR(p) && CheckIYR(p) && CheckEYR(p) && CheckHGT(p) &&
          CheckHCL(p) && CheckECL(p) && CheckPID(p)) ? true : false;
}

bool ValidPassport(const Passport& p){
  return (p.count("byr") && p.count("iyr") && p.count("eyr") && p.count("hgt") 
       && p.count("hcl") && p.count("ecl") && p.count("pid")) ? true : false;
}

int CountValidPassports(const Passports& pp){
  int valid_count = 0;
  for(const auto& p : pp){
    if(ValidPassport(p)) /*valid_count++;*/{
      if(CheckALL(p)) valid_count++;
    }
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
      if(line == ""){
       pp.push_back(p);
       p = {};
      }
      else{
        p[field.substr(0,pos)] = field.substr(pos+1);
      }
    }
  }
  if(!p.empty()){
    pp.push_back(p);
  }
  file.close();
}

int main(){
  Passports passports;
  GetPassports(passports);
  //PrintPassports(passports);
  std::cout << "valid passports: " << CountValidPassports(passports) << std::endl;
  return 0;
}