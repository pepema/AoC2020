#include <vector>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <iostream>

using Operation = std::tuple<std::string,int,bool>;
using Program = std::vector<Operation>;

void PrintInstructions(const Program& p){
  for(const auto& a : p){
    std::cout << std::get<0>(a) << " " << std::get<1>(a) << " " << std::get<2>(a) << std::endl;
  }
}

bool ProgramTerminates(Program p){
  for(int i=0;i<p.size();){
    bool& visited = std::get<2>(p[i]);
    if(visited) return false;
    else{
      visited = true;
      if(std::get<0>(p[i]) == "nop") i++;
      else if(std::get<0>(p[i]) == "acc") i++;
      else if (std::get<0>(p[i]) == "jmp"){
        i += std::get<1>(p[i]);
      }
    }
  }
  return true;
}

void SwapJump(Program& p){
  for(int i=0;i<p.size();i++){
    std::string& op = std::get<0>(p[i]);
    if(op == "jmp"){
      op = "nop";
      if(ProgramTerminates(p)) break;
      else op = "jmp";
    }
  }
}

int GetAccumulatorValue(Program p){
  int accumulator = 0;
  for(int i=0;i<p.size();){
    bool& visited = std::get<2>(p[i]);
    if(visited) break;
    else{
      visited = true;
      if(std::get<0>(p[i]) == "nop") i++;
      else if(std::get<0>(p[i]) == "acc"){
        accumulator += std::get<1>(p[i]);
        i++;
      }
      else if (std::get<0>(p[i]) == "jmp"){
        i += std::get<1>(p[i]);
      }
    }
  }
  return accumulator;
}

void GetInstructions(Program& p){
  std::ifstream file("input.txt");
  std::string line;
  Operation o;
  std::size_t pos;
  while(std::getline(file,line)){
    pos = line.find(" ");
    o = std::make_tuple(line.substr(0,pos),stoi(line.substr(pos+1)),false);
    p.push_back(o);
  }
  file.close();
}

int main(){
  Program p;
  GetInstructions(p);
  SwapJump(p);
  std::cout << "This is the value " << GetAccumulatorValue(p) << std::endl;
}
