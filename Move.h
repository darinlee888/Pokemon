//
// Created by Darin Lee on 6/14/2020.
//

#ifndef POKEMON_MOVE_H
#define POKEMON_MOVE_H

#include <string>

class Move {
 public:
  Move(std::string name, std::string type, std::string cat, int pwr, int acc, int pp);
  std::string getName();
  std::string getType();
  std::string getCat();
  int getPwr() const;
  int getAcc() const;
  int getPP() const;

  int currentPP;

 private:
  std::string name;
  std::string type;
  std::string cat;
  int pwr;
  int acc;
  int pp;

};

#endif //POKEMON_MOVE_H
