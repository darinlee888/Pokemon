//
// Created by Darin Lee on 8/17/2020.
//

#include <random>
#include <chrono>
#include <functional>
#include "AITrainer.h"

AITrainer::AITrainer(std::string name, int numPokemon, std::vector<Pokemon> pokemon) :
Trainer(std::move(name), numPokemon, std::move(pokemon)) {}

void AITrainer::selectPokemon(Trainer& opponent) {
  if (opponent.currentPokemon == nullptr) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(0, numPokemon - 1);
    auto rng = std::bind(distribution, generator);
    int choice = rng();
    while (pokemon[choice].isFainted()) {
      choice = rng();
    }
    currentPokemon = &(pokemon[choice]);
  } else {
    int choice = 0;
    for (int i = 1; i < numPokemon; i++) {
      if (!pokemon[i].isFainted()) {
        if (pokemon[choice].isFainted()) {
          choice = i;
        } else {
          std::vector<std::string> types;
          types.push_back(opponent.currentPokemon->getType1());
          if (!opponent.currentPokemon->getType2().empty()) {
            types.push_back(opponent.currentPokemon->getType2());
          }
          std::vector<std::string> typesCopy(types);
          std::vector<std::string> typesTwo(types);
          std::vector<std::string> secondTypes(types);
          double best = pokemon[choice].multiplier(pokemon[choice].getType1(), types);
          if (!pokemon[choice].getType2().empty()) {
            best *= pokemon[choice].multiplier(pokemon[choice].getType2(), typesTwo);
          }
          double current = pokemon[i].multiplier(pokemon[i].getType1(), typesCopy);
          if (!pokemon[choice].getType2().empty()) {
            current *= pokemon[i].multiplier(pokemon[i].getType2(), secondTypes);
          }
          if (current == best) {
            double firstHp = (double) pokemon[choice].currentHp / pokemon[choice].getHp();
            double secondHp = (double) pokemon[i].currentHp / pokemon[i].getHp();
            if (firstHp < secondHp) {
              choice = i;
            }
          } else if (current > best) {
            choice = i;
          }
        }
      }
    }
    currentPokemon = &(pokemon[choice]);
  }
}

int AITrainer::selectMove(Trainer& opponent) {
  int choice = 1;
  for (int i = 2; i <= 4; i++) {
    if (currentPokemon->canUseMove(i)) {
      if (!currentPokemon->canUseMove(choice)) {
        choice = i;
      } else {
        double current = currentPokemon->calcDmg(*(opponent.currentPokemon), i);
        double best = currentPokemon->calcDmg(*(opponent.currentPokemon), choice);
        if (current == best) {
          if (currentPokemon->getMove(i).currentPP > currentPokemon->getMove(choice).currentPP) {
            choice = i;
          }
        } else if (current > best) {
          choice = i;
        }
      }
    }
  }
  return choice;
}

int AITrainer::optionSelect(Trainer& opponent) {
  std::vector<std::string> types;
  types.push_back(opponent.currentPokemon->getType1());
  if (!opponent.currentPokemon->getType2().empty()) {
    types.push_back(opponent.currentPokemon->getType2());
  }
  std::vector<std::string> typesTwo(types);
  double current = currentPokemon->multiplier(currentPokemon->getType1(), types);
  if (!currentPokemon->getType2().empty()) {
    current *= currentPokemon->multiplier(currentPokemon->getType2(), typesTwo);
  }
  if (current < 1.0) {
    for (auto & i : pokemon) {
      std::vector<std::string> secondTypes;
      secondTypes.push_back(opponent.currentPokemon->getType1());
      if (!opponent.currentPokemon->getType2().empty()) {
        secondTypes.push_back(opponent.currentPokemon->getType2());
      }
      std::vector<std::string> typesCopy(secondTypes);
      double next = currentPokemon->multiplier(currentPokemon->getType1(), secondTypes);
      if (!currentPokemon->getType2().empty()) {
        next *= currentPokemon->multiplier(currentPokemon->getType2(), typesCopy);
      }
      if (!i.isFainted() && next > current) {
        return 2;
      }
    }
  }
  return 1;
}
