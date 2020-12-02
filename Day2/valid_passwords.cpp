#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>

using Password = std::tuple<int,int,char,std::string>;
using Passmap = std::vector<Password>;

bool ValidPassword(const Password& p){
  std::string pw = std::get<3>(p);
  char letter = std::get<2>(p);
  int roof = std::get<1>(p);
  int floor = std::get<0>(p);
  int count = 0;
  for(const auto& i : pw){
    if(i==letter) count++;
  }
  return (count >= floor && count <= roof) ? true : false;
}

int GetNumberOfValidPasswords(const Passmap& p){
  int valid_passwords = 0;
  for(auto& i : p){
    if(ValidPassword(i)) valid_passwords++;
  }
  return valid_passwords;
}


void FillPassmap(Passmap& p){
  std::ifstream file("input.txt");
  std::string line;

  while(std::getline(file,line)){
    line.replace(line.find("-"),1," ");
    line.replace(line.find(":"),1,"");
    std::stringstream ss;
    ss << line;
    int floor;
    int roof;
    char letter;
    std::string pass;

    while(!ss.eof()){
      ss >> floor;
      ss >> roof;
      ss >> letter;
      ss >> pass;
    }

    Password pw = {floor,roof,letter,pass};
    p.push_back(pw);
  }
  file.close();
}

int main(){
  Passmap passwords;
  FillPassmap(passwords);
  std::cout << GetNumberOfValidPasswords(passwords) << std::endl;
  return 0;
}