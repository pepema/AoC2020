#include <vector>
#include <fstream>
#include <iostream>
#include <array>

using SurroundingRows = std::array<std::string,3>;
using SeatLayout = std::vector<std::string>;

std::string AdjecentSeats(SurroundingRows& sr, int pos){
  std::string adjecent = {sr[0][pos-1],sr[0][pos],sr[0][pos+1],
                          sr[1][pos-1],           sr[1][pos+1],
                          sr[2][pos-1],sr[2][pos],sr[2][pos+1]};
  return adjecent;
}

void PrintLayout(const SeatLayout& sl){
  for(const auto& a : sl){
    std::cout << a << std::endl;
  }
  std::cout << "-------------" << std::endl;
}
int CalculateOccupiedSeats(SeatLayout sl){
  SurroundingRows sr;
  SeatLayout current = sl;
  SeatLayout updated_layout = sl;
  char updated_seat;
  std::string occupied_seats;
  int nr_occupied_seats = 0;
  int total_occupied = 0;
  while(true){
    for(int i=0;i<current.size();i++){
      if(i==0) sr = {"",current[i],current[i+1]};
      else if(i==current.size()-1) sr = {current[i-1],current[i],""};
      else sr = {current[i-1],current[i],current[i+1]};
      for(int j=0;j<current[i].length();j++){
        occupied_seats = AdjecentSeats(sr,j);
        if(current[i][j]=='L' && occupied_seats.find('#') == std::string::npos){
          updated_seat = '#';
        }
        else if(current[i][j]=='#'){
          total_occupied++;
          nr_occupied_seats = 0;
          for(const auto& a : occupied_seats){
            if(a=='#') nr_occupied_seats++;
          }
          if(nr_occupied_seats >=4){
            updated_seat = 'L';
          }
          else{
            updated_seat = '#';
          }
        }
        else{
          updated_seat = current[i][j];
        }
        updated_layout[i][j]=updated_seat;
        nr_occupied_seats = 0;
      }
    }
    if(current == updated_layout) break;
    else {
      current = updated_layout;
      total_occupied = 0;
    }
  }
  return total_occupied;
}

void GetSeatLayout(SeatLayout& sl){
  std::ifstream file("input.txt");
  std::string line;
  std::size_t pos;
  while(std::getline(file,line)){
    sl.push_back(line);
  }
  file.close();
}

int main(){
  SeatLayout sl;
  GetSeatLayout(sl);
  std::cout << CalculateOccupiedSeats(sl) << std::endl;
}