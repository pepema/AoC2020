#include<bitset>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>

using BoardingPasses = std::vector<std::string>;
using BoardingPassMap = std::unordered_map<std::string,int>;
using BoardingPassList = std::vector<BoardingPassMap>;

void PrintMap(const BoardingPassList& bpl){
  for(const auto& i : bpl){
    for(const auto& j : i){
      std::cout << j.first << " " << j.second << std::endl;
    }
    std::cout << "--------------" << std::endl;
  }
}

int GetRow(const std::string& s){
  std::bitset<7> row;
  for(int i=0;i<7;i++){
    if(s[i]=='B') row[6-i] = 1;
    else row[6-i] = 0;
  }
  return static_cast<int>(row.to_ulong());
}

int GetColumn(const std::string& s){
  std::bitset<3> column;
   for(int i=0;i<3;i++){
    if(s[i]=='R') column[2-i] = 1;
    else column[2-i] = 0;
  }
  return static_cast<int>(column.to_ulong());
}

int GetID(const int& row, const int& column){
  return row*8 + column;
}

BoardingPassList DecodeBoardingPasses(const BoardingPasses& bps){
  BoardingPassMap bpm;
  BoardingPassList bpl;
  for(const auto& bp : bps){
    bpm["Row"] = GetRow(bp.substr(0,7));
    bpm["Column"] = GetColumn(bp.substr(7));
    bpm["ID"] = GetID(GetRow(bp.substr(0,7)),GetColumn(bp.substr(7)));
    bpl.push_back(bpm);
    bpm = {};
  }
  return bpl;
}

int GetHighestID(const BoardingPassList& bpl){
  int highest = -1;
  for(const auto& bp : bpl){
    if(bp.at("ID")>highest) highest = bp.at("ID");
  }
  return highest;
}

void GetBoardingPasses(BoardingPasses& bps){
  std::ifstream file("input.txt");
  std::string line;
  while(std::getline(file,line)){
    bps.push_back(line);
  }
  file.close();
}

bool HasHigherID(const BoardingPassMap& b1, const BoardingPassMap& b2){
  return b1.at("ID") < b2.at("ID");
}

void SortList(BoardingPassList& bpl){
  std::sort (bpl.begin(),bpl.end(),HasHigherID);
}

int FindMySeat(BoardingPassList& bpl){
  SortList(bpl);
  for(int i=0;i<bpl.size();i++){
    if(bpl[i].at("ID")+1 != bpl[i+1].at("ID")) return bpl[i].at("ID")+1;
  }
  return -1;
}

int main(){
  BoardingPasses bps;
  GetBoardingPasses(bps);
  BoardingPassList bpl = DecodeBoardingPasses(bps);
  std::cout << "Highest ID: " << GetHighestID(bpl) << std::endl;
  std::cout << "My seat: " << FindMySeat(bpl) << std::endl;

  return 0;
}