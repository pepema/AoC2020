#include<vector>
#include<iostream>
#include<fstream>
#include<unordered_map>

using Group = std::unordered_map<char,int>;
using Groups = std::vector<Group>;

void PrintForms(const Groups& gs){
  for(const auto& g : gs){
    for(const auto& i : g){
      std::cout << i.first << ": " << i.second << std::endl;
    }
    std::cout << "----------" << std::endl;
  }
}

int GetSum(const Groups& gs){
  int sum=0;
  for(const auto& g : gs){
    sum+=g.size()-1;
  }
  return sum;
}

int GetSum2(const Groups& gs){
  int sum=0;
  for(const auto& g : gs){
    for(const auto& i : g){
      if(i.first != '+' && i.second == g.at('+')) sum++;
    }
  }
  return sum;
}

void GetDeclarationForms(Groups& gs){
  std::ifstream file("input.txt");
  std::string line;
  Group g = {};
  std::size_t pos;
  while(std::getline(file,line)){
    if(line == ""){
      gs.push_back(g);
      g = {};
    }
    else{
      g['+']++;
      for(const auto& ch : line){
        g[ch]++;
      }
    }
  }
  if(!g.empty()){
    gs.push_back(g);
  }
  file.close();
}

int main(){
  Groups groups;
  GetDeclarationForms(groups);
  std::cout << GetSum(groups)  << std::endl;
  std::cout << GetSum2(groups) << std::endl;
  //PrintForms(groups);
  return 0;
}