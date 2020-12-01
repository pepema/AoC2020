#include <vector>
#include <iostream>
#include <fstream>

int Find2020(const std::vector<int>& v){
  int returnvalue = -1;
  for(int i=0;i<v.size()+1;i++){
    for(int j=i+1;j<v.size();j++){
      if(v[i]+v[j] == 2020){
        return v[i]*v[j];
      }
    }
  }
  return returnvalue;
}

int Find2020_3(const std::vector<int>& v){
  int returnvalue = -1;
  for(int i=0;i<v.size()+2;i++){
    for(int j=i+1;j<v.size()+1;j++){
      for(int k=j+1;k<v.size();k++){
        if(v[i]+v[j]+v[k] == 2020){
        return v[i]*v[j]*v[k];
        }
      }
    }
  }
  return returnvalue;
}

void FillReport(std::vector<int>& v){
  std::ifstream file("input.txt");
  std::string line;
  while(std::getline(file,line)){
    v.push_back(std::stoi(line));
  }
  file.close();
}

int main(){
  std::vector<int> expense_report /*= {1721,979,366,299,675,1456}*/;
  FillReport(expense_report);
  std::cout << Find2020(expense_report) << std::endl;
  std::cout << Find2020_3(expense_report) << std::endl;
}