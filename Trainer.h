//
// Created by Darin Lee on 6/15/2020.
//

#ifndef POKEMON_TRAINER_H
#define POKEMON_TRAINER_H

#include <string>
#include <vector>
#include "Pokemon.h"

class Trainer {
 public:
  Trainer(std::string name, int numPokemon, std::vector<Pokemon> pokemon);
  std::string getName();
  int getNumPokemon() const;
  void displayPokemonList();
  void displayTrainer();
  bool loses();
  virtual void selectPokemon(Trainer& opponent);
  virtual int selectMove(Trainer& opponent);
  virtual int optionSelect(Trainer& opponent);

  Pokemon* currentPokemon;

 protected:
  std::string name;
  int numPokemon;
  std::vector<Pokemon> pokemon;

};

#endif //POKEMON_TRAINER_H
