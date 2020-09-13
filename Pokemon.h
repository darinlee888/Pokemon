//
// Created by Darin Lee on 6/14/2020.
//

#ifndef POKEMON_POKEMON_H
#define POKEMON_POKEMON_H

#include <vector>
#include "Move.h"
#include <string>

class Pokemon {
 public:
  Pokemon(int hp, int atk, int mag, int spd, int def, int res, std::string name, std::string type,
          const Move& move1, const Move& move2, const Move& move3, const Move& move4);
  Pokemon(int hp, int atk, int mag, int spd, int def, int res, std::string name, std::string type1,
          std::string type2, const Move& move1, const Move& move2, const Move& move3, const Move& move4);
  int getHp() const;
  int getAtk() const;
  int getMag() const;
  int getSpd() const;
  int getDef() const;
  int getRes() const;
  std::string getName();
  std::string getType1();
  std::string getType2();
  bool isFainted();
  void faint();
  void displayMoveSet();
  void attack(Pokemon& opponent, int choice, int miss, int critical);
  double calcDmg(Pokemon& opponent, int choice);
  double multiplier(const std::string& moveType, std::vector<std::string>& types);
  bool canUseMove(int choice);
  Move getMove(int choice);

  int currentHp;

 private:
  int hp;
  int atk;
  int mag;
  int spd;
  int def;
  int res;

  std::string name;
  std::string type1;
  std::string type2;
  bool fainted;
  std::vector<Move> moves;

};

#endif //POKEMON_POKEMON_H
