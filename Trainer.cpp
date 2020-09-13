//
// Created by Darin Lee on 6/15/2020.
//

#include "Trainer.h"
#include <iostream>

Trainer::Trainer(std::string name, int numPokemon, std::vector<Pokemon> pokemon) :
name(std::move(name)), numPokemon(numPokemon), pokemon(std::move(pokemon)), currentPokemon(nullptr) {}

std::string Trainer::getName() {
  return name;
}

int Trainer::getNumPokemon() const {
  return numPokemon;
}

void Trainer::displayPokemonList() {
  std::cout << "#  Name        Type             Hp       Atk  Mag  Spd  Def  Res" << std::endl;
  for (int i = 0; i < pokemon.size(); i++) {
    std::cout << i + 1 << ") ";
    std::string pokemonName = pokemon[i].getName();
    while (pokemonName.size() < 10) {
      pokemonName.append(" ");
    }
    std::cout << pokemonName << "  ";
    std::string pokemonType1 = pokemon[i].getType1();
    while (pokemonType1.size() < 8) {
      pokemonType1.append(" ");
    }
    std::cout << pokemonType1 << " ";
    std::string pokemonType2 = pokemon[i].getType2();
    while (pokemonType2.size() < 6) {
      pokemonType2.append(" ");
    }
    std::cout << pokemonType2 << "  ";
    std::string pokemonHp = std::to_string(pokemon[i].currentHp) + "/" + std::to_string(pokemon[i].getHp());
    while (pokemonHp.size() < 7) {
      pokemonHp.append(" ");
    }
    std::cout << pokemonHp << "  " << pokemon[i].getAtk();
    if (pokemon[i].getAtk() / 100 == 0) {
      std::cout << " ";
    }
    std::cout << "  " << pokemon[i].getMag();
    if (pokemon[i].getMag() / 100 == 0) {
      std::cout << " ";
    }
    std::cout << "  " << pokemon[i].getSpd();
    if (pokemon[i].getSpd() / 100 == 0) {
      std::cout << " ";
    }
    std::cout << "  " << pokemon[i].getDef();
    if (pokemon[i].getDef() / 100 == 0) {
      std::cout << " ";
    }
    std::cout << "  " << pokemon[i].getRes();
    std::cout << std::endl;
  }
}

void Trainer::displayTrainer() {
  std::cout << "Trainer: " << name;
  if (currentPokemon != nullptr) {
    std::cout << " Pokemon: " << currentPokemon->getName();
    std::cout << " HP: " << currentPokemon->currentHp << "/" << currentPokemon->getHp();
    std::cout << " Types: " << currentPokemon->getType1();
    if (!currentPokemon->getType2().empty()) {
      std::cout << " " << currentPokemon->getType2();
    }
  }
  std::cout << std::endl;
}

bool Trainer::loses() {
  for (auto & i : pokemon) {
    if (!i.isFainted()) {
      return false;
    }
  }
  return true;
}

void Trainer::selectPokemon(Trainer& opponent) {
  std::string word = "next";
  if (currentPokemon == nullptr) {
    word = "first";
  }
  int choice;
  std::cout << name << ", please select your " << word << " Pokemon: " << std::endl;
  displayPokemonList();
  std::cin >> choice;
  while (choice > numPokemon || choice < 1) {
    std::cout << name << ", please select your " << word << " Pokemon: " << std::endl;
    displayPokemonList();
    std::cin >> choice;
  }
  while (pokemon[choice - 1].isFainted()) {
    std::cout << name << ", please select your " << word << " Pokemon: " << std::endl;
    displayPokemonList();
    std::cin >> choice;
  }
  currentPokemon = &(pokemon[choice - 1]);
}

int Trainer::selectMove(Trainer& opponent) {
  int choice;
  std::cout << name << ", which move would you like to use?" << std::endl;
  currentPokemon->displayMoveSet();
  std::cin >> choice;
  while (choice > 4 || choice < 1) {
    std::cout << name << ", which move would you like to use?" << std::endl;
    currentPokemon->displayMoveSet();
    std::cin >> choice;
  }
  while (!currentPokemon->canUseMove(choice)) {
    std::cout << name << ", which move would you like to use?" << std::endl;
    currentPokemon->displayMoveSet();
    std::cin >> choice;
  }
  return choice;
}

int Trainer::optionSelect(Trainer& opponent) {
  int option;
  std::cout << name << ", would you like to [1] attack or [2] switch Pokemon?" << std::endl;
  std::cin >> option;
  while (option < 1 || option > 2) {
    std::cout << name << ", would you like to [1] attack or [2] switch Pokemon?" << std::endl;
    std::cin >> option;
  }
  return option;
}
