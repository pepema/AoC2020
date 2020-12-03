#include<fstream>
#include<iostream>
#include<vector>

using TreeMap = std::vector<std::string>;

void PrintMap(const TreeMap& tm){
  for(const auto& elem : tm){
    std::cout << elem << std::endl;
  }
}

int GetIndex(int index, std::string s,int i){
  switch(i){
    case(1):
      return (index+3 < s.length()) ? index+3 : index+3-s.length();
      break;
    case(2):
      return (index+5 < s.length()) ? index+5 : index+5-s.length();
      break;
    case(3):
      return (index+7 < s.length()) ? index+7 : index+7-s.length();
      break;
    default:
      return (index+1 < s.length()) ? index+1 : index+1-s.length();
  }
}

int FindTrees(TreeMap& tm){
  int trees_found = 0;
  int all_trees_found = 1;
  int index = 0;
  tm.erase(tm.begin());
  for(int i=0;i<4;i++){
    for(const auto& elem : tm){
      index = GetIndex(index,elem,i);
      if(elem[index]=='#') trees_found++;
    }
    std::cout << trees_found << std::endl;
    all_trees_found *= trees_found;
    index = trees_found = 0;
  }
  tm.erase(tm.begin());
  for(size_t i = 0; i<tm.size();i+=2){
    index = GetIndex(index,tm[i],0);
    if(tm[i][index]=='#') trees_found++;
  }
  return all_trees_found*trees_found;
}

void FillMap(TreeMap& tm){
  std::ifstream file("input.txt");
  std::string line;
  while(std::getline(file,line)){
    tm.push_back(line);
  }
  file.close();
}

int main(){
  TreeMap tree_map;
  FillMap(tree_map);
  std::cout << FindTrees(tree_map) << std::endl;
  return 0;
}