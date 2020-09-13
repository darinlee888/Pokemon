//
// Created by Darin Lee on 6/14/2020.
//

#include "Pokemon.h"
#include <iostream>

Pokemon::Pokemon(int hp, int atk, int mag, int spd, int def, int res,
                 std::string name, std::string type,
                 const Move& move1, const Move& move2, const Move& move3, const Move& move4) :
                 hp(hp), atk(atk), mag(mag), spd(spd), def(def), res(res), currentHp(hp), fainted(false),
                 name(std::move(name)), type1(std::move(type)), type2(std::string()) {
  moves.push_back(move1);
  moves.push_back(move2);
  moves.push_back(move3);
  moves.push_back(move4);
}

Pokemon::Pokemon(int hp, int atk, int mag, int spd, int def, int res,
                 std::string name, std::string type1, std::string type2,
                 const Move& move1, const Move& move2, const Move& move3, const Move& move4) :
                 hp(hp), atk(atk), mag(mag), spd(spd), def(def), res(res), currentHp(hp), fainted(false),
                 name(std::move(name)), type1(std::move(type1)), type2(std::move(type2)) {
  moves.push_back(move1);
  moves.push_back(move2);
  moves.push_back(move3);
  moves.push_back(move4);
}

int Pokemon::getHp() const {
  return hp;
}

int Pokemon::getAtk() const {
  return atk;
}

int Pokemon::getMag() const {
  return mag;
}

int Pokemon::getSpd() const {
  return spd;
}

int Pokemon::getDef() const {
  return def;
}

int Pokemon::getRes() const {
  return res;
}

std::string Pokemon::getName() {
  return name;
}

std::string Pokemon::getType1() {
  return type1;
}

std::string Pokemon::getType2() {
  return type2;
}

bool Pokemon::isFainted() {
  return fainted;
}

void Pokemon::faint() {
  fainted = true;
}

void Pokemon::displayMoveSet() {
  std::cout << "#  Name            Type      Category  Pwr  Acc  PP" << std::endl;
  int i = 1;
  for (auto & move : moves) {
    std::cout << i << ") ";
    i++;
    std::string moveName = move.getName();
    while (moveName.size() < 14) {
      moveName.append(" ");
    }
    std::cout << moveName << "  ";
    std::string moveType = move.getType();
    while (moveType.size() < 8) {
      moveType.append(" ");
    }
    std::cout << moveType << "  " << move.getCat();
    if (move.getCat() == "Special") {
      std::cout << " ";
    }
    std::cout << "  " << move.getPwr();
    if (move.getPwr() / 100 == 0) {
      std::cout << " ";
    }
    std::cout << "  " << move.getAcc();
    if (move.getAcc() / 100 == 0) {
      std::cout << " ";
    }
    std::cout << "  " << move.currentPP << "/" << move.getPP() << std::endl;
  }
}

void Pokemon::attack(Pokemon& opponent, int choice, int miss, int critical) {
  std::cout << name << " used " << moves[choice - 1].getName() << "!" << std::endl;
  moves[choice - 1].currentPP--;
  double dmg = 0;
  if (miss >= moves[choice - 1].getAcc()) {
    std::cout << name << " missed!" << std::endl;
  }
  else {
    if (moves[choice - 1].getCat() == "Physical") {
      dmg = 2.4 * (moves[choice - 1].getPwr() * ((double) atk / opponent.getDef())) / 50 + 2;
    }
    else if (moves[choice - 1].getCat() == "Special") {
      dmg = 2.4 * (moves[choice - 1].getPwr() * ((double) mag / opponent.getRes())) / 50 + 2;
    }
    std::vector<std::string> types;
    types.push_back(opponent.getType1());
    if (!opponent.getType2().empty()) {
      types.push_back(opponent.getType2());
    }
    double m = multiplier(moves[choice - 1].getType(), types);
    dmg *= m;
    if (m == 0) {
      std::cout << "It's not effective!" << std::endl;
    } else if (m == 0.25) {
      std::cout << "It's barely effective!" << std::endl;
    } else if (m == 0.5) {
      std::cout << "It's not very effective!" << std::endl;
    } else if (m == 2) {
      std::cout << "It's super effective!" << std::endl;
    } else if (m == 4) {
      std::cout << "It's double super effective!" << std::endl;
    }
    if (moves[choice - 1].getType() == type1 || moves[choice - 1].getType() == type2) {
      dmg *= 1.5;
    }
    if (critical < spd / 2) {
      dmg *= 1.5;
      if (dmg != 0) {
        std::cout << "Critical Hit!" << std::endl;
      }
    }
  }
  if (opponent.currentHp <= (int) dmg) {
    opponent.currentHp = 0;
    opponent.faint();
    std::cout << opponent.getName() << " fainted!" << std::endl;
  } else {
    opponent.currentHp -= (int) dmg;
  }
}

double Pokemon::calcDmg(Pokemon& opponent, int choice) {
  double dmg = 0;
  if (moves[choice - 1].getCat() == "Physical") {
    dmg = 2.4 * (moves[choice - 1].getPwr() * ((double) atk / opponent.getDef())) / 50 + 2;
  }
  else if (moves[choice - 1].getCat() == "Special") {
    dmg = 2.4 * (moves[choice - 1].getPwr() * ((double) mag / opponent.getRes())) / 50 + 2;
  }
  std::vector<std::string> types;
  types.push_back(opponent.getType1());
  if (!opponent.getType2().empty()) {
    types.push_back(opponent.getType2());
  }
  dmg *= multiplier(moves[choice - 1].getType(), types);
  if (moves[choice - 1].getType() == type1 || moves[choice - 1].getType() == type2) {
    dmg *= 1.5;
  }
  return dmg;
}

double Pokemon::multiplier(const std::string& moveType, std::vector<std::string>& types) {
  if (types.empty()) {
    return 1;
  }
  std::string opponentType = types.back();
  types.pop_back();
  if (moveType == "Normal") {
    if (opponentType == "Rock") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ghost") {
      return 0;
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Fighting") {
    if (opponentType == "Normal") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Flying") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Poison") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Rock") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Bug") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ghost") {
      return 0;
    } else if (opponentType == "Steel") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Psychic") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ice") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Dark") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fairy") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Flying") {
    if (opponentType == "Fighting") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Rock") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Bug") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Electric") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Poison") {
    if (opponentType == "Poison") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ground") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Rock") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ghost") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0;
    } else if (opponentType == "Grass") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fairy") {
      return 2 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Ground") {
    if (opponentType == "Flying") {
      return 0;
    } else if (opponentType == "Poison") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Rock") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Bug") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Electric") {
      return 2 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Rock") {
    if (opponentType == "Fighting") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Flying") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Ground") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Bug") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Ice") {
      return 2 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Bug") {
    if (opponentType == "Fighting") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Flying") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Poison") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ghost") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Psychic") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Dark") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fairy") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Ghost") {
    if (opponentType == "Normal") {
      return 0;
    } else if (opponentType == "Ghost") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Psychic") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Dark") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Steel") {
    if (opponentType == "Rock") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Water") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Electric") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ice") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fairy") {
      return 2 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Fire") {
    if (opponentType == "Rock") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Bug") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Water") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Ice") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Dragon") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Water") {
    if (opponentType == "Ground") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Rock") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Water") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Dragon") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Grass") {
    if (opponentType == "Flying") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Poison") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ground") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Rock") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Bug") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Water") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Dragon") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Electric") {
    if (opponentType == "Flying") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Ground") {
      return 0;
    } else if (opponentType == "Water") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Electric") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Dragon") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Psychic") {
    if (opponentType == "Fighting") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Poison") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Psychic") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Dark") {
      return 0;
    }
    return multiplier(moveType, types);
  } else if (moveType == "Ice") {
    if (opponentType == "Flying") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Ground") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Water") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Grass") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Ice") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Dragon") {
      return 2 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Dragon") {
    if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Dragon") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Fairy") {
      return 0;
    }
    return multiplier(moveType, types);
  } else if (moveType == "Dark") {
    if (opponentType == "Fighting") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Ghost") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Psychic") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Dark") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Fairy") {
      return 0.5 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  } else if (moveType == "Fairy") {
    if (opponentType == "Fighting") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Poison") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Steel") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Fire") {
      return 0.5 * multiplier(moveType, types);
    } else if (opponentType == "Dragon") {
      return 2 * multiplier(moveType, types);
    } else if (opponentType == "Dark") {
      return 2 * multiplier(moveType, types);
    }
    return multiplier(moveType, types);
  }
  return multiplier(moveType, types);
}

bool Pokemon::canUseMove(int choice) {
  if (moves[choice - 1].currentPP == 0) {
    return false;
  }
  return true;
}

Move Pokemon::getMove(int choice) {
  return moves[choice - 1];
}
