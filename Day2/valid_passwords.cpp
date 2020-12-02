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
    if(i==letter) count++;
  }
  return (count >= floor && count <= roof) ? true : false;
}

int GetNumberOfValidPasswords(const Passmap& p){

  return 0;
}


void FillPassmap(const Passmap& p){
  std::ifstream file("testing_input.txt");
  std::string line;
  while(std::getline(file,line)){
    /*std::string pw = 
    char letter = std::get<2>(p);
    int roof = std::get<1>(p);
    int floor = std::get<0>(p);*/
    std::cout << line << std::endl;
  }
  file.close();
}

int main(){
  Passmap passwords;
  FillPassmap(passwords);
  return 0;
}