//
// Created by Darin Lee on 8/17/2020.
//

#ifndef POKEMON_AITRAINER_H
#define POKEMON_AITRAINER_H

#include "Trainer.h"
#include <string>

class AITrainer : public Trainer {
 public:
  AITrainer(std::string name, int numPokemon, std::vector<Pokemon> pokemon);
  void selectPokemon(Trainer& opponent) override;
  int selectMove(Trainer& opponent) override;
  int optionSelect(Trainer& opponent) override;
};

#endif //POKEMON_AITRAINER_H
