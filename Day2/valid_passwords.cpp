#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>

using Password = std::tuple<int,int,char,std::string>;
using Passmap = std::vector<Password>;

bool ValidPassword(const Password& p){
  std::string pw = std::get<3>(p);
  char letter = std::get<2>(p);
  int roof = std::get<1>(p);
  int floor = std::get<0>(p);
  int count = 0;

  for(const auto& i : pw){
    if(pw[i]==letter);
  }
  return (count >= floor && count <= roof) ? true : false;
}

int GetNumberOfValidPasswords(const Passmap& p){

  return 0;
}


void FillPassmap(const Passmap& p){
  std::ifstream file("input.txt");
  std::string line;
  while(std::getline(file,line)){

  }
  file.close();
}

int main(){
  Passmap passwords;
  passwords.push_back({1,3,'a',"abcde"});
  passwords.push_back({1,3,'b',"cdefg"});
  passwords.push_back({2,9,'a',"ccccccccc"});

  std::cout << ValidPassword(passwords[0]) << std::endl;
  std::cout << "hello" << std::endl;
}