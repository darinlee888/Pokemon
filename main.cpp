#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <functional>
#include "Move.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "AITrainer.h"

int main() {
  Move thunderShock("Thunder Shock", "Electric", "Special", 40, 100, 30);
  Move skullBash("Skull Bash", "Normal", "Physical", 130, 100, 10);
  Move quickAttack("Quick Attack", "Normal", "Physical", 40, 100, 30);
  Move thunder("Thunder", "Electric", "Special", 110, 70, 10);
  Move voltTackle("Volt Tackle", "Electric", "Physical", 120, 100, 15);

  Move rollout("Rollout", "Rock", "Physical", 30, 90, 20);
  Move pound("Pound", "Normal", "Physical", 40, 100, 35);
  Move hyperVoice("Hyper Voice", "Normal", "Special", 90, 100, 10);
  Move rest("Rest", "Normal", "Physical", 60, 55, 10);

  Move shadowBall("Shadow Ball", "Ghost", "Special", 80, 100, 15);
  Move confusion("Confusion", "Psychic", "Special", 50, 100, 25);
  Move disable("Disable", "Normal", "Special", 20, 100, 20);
  Move psyStrike("PsyStrike", "Psychic", "Special", 100, 100, 10);

  Move waterGun("Water Gun", "Water", "Special", 40, 100, 25);
  Move waterfall("Waterfall", "Water", "Physical", 80, 100, 15);
  Move hydroPump("Hydro Pump", "Water", "Special", 110, 80, 5);
  Move waterSpout("Water Spout", "Water", "Special", 150, 100, 5);

  Move bulletSeed("Bullet Seed", "Grass", "Special", 25, 100, 30);
  Move razorLeaf("Razor Leaf", "Grass", "Special", 55, 95, 25);
  Move vineWhip("Vine Whip", "Grass", "Physical", 45, 100, 25);
  Move solarBeam("Solar Beam", "Grass", "Special", 120, 100, 10);

  Move flamethrower("Flamethrower", "Fire", "Special", 90, 100, 15);
  Move flareBlitz("Flare Blitz", "Fire", "Physical", 120, 100, 15);
  Move fly("Fly", "Flying", "Physical", 90, 95, 15);
  Move rockSmash("Rock Smash", "Fighting", "Physical", 40, 100, 15);

  Move auraSphere("Aura Sphere", "Fighting", "Special", 80, 100, 20);
  Move forcePalm("Force Palm", "Fighting", "Physical", 60, 100, 10);
  Move extremeSpeed("Extreme Speed", "Normal", "Physical", 80, 100, 5);
  Move doubleTeam("Double Team", "Normal", "Physical", 65, 100, 15);

  Move waterShuriken("Water Shuriken", "Water", "Special", 15, 100, 20);
  Move shadowSneak("Shadow Sneak", "Ghost", "Physical", 40, 100, 30);
  Move substitute("Substitute", "Normal", "Physical", 55, 100, 10);

  Move darkestLariat("Darkest Lariat", "Dark", "Physical", 85, 100, 10);
  Move throatChop("Throat Chop", "Dark", "Physical", 80, 100, 15);
  Move crossChop("Cross Chop", "Fighting", "Physical", 100, 80, 5);
  Move revenge("Revenge", "Fighting", "Physical", 60, 100, 10);

  Pokemon pikachu(35, 55, 50, 90, 40, 50, "Pikachu",
                  "Electric", thunderShock, skullBash, quickAttack, thunder);
  Pokemon jigglyPuff(115, 45, 45, 20, 20, 25, "JigglyPuff",
                     "Normal", "Fairy", rollout, pound, hyperVoice, rest);
  Pokemon pichu(20, 40, 35, 60, 15, 35, "Pichu",
                "Electric", thunderShock, skullBash, thunder, voltTackle);
  Pokemon mewTwo(106, 110, 154, 130, 90, 90, "MewTwo",
                 "Psychic", shadowBall, confusion, disable, psyStrike);
  Pokemon squirtle(44, 48, 50, 43, 65, 64, "Squirtle",
                   "Water", waterGun, waterfall, hydroPump, waterSpout);
  Pokemon ivysaur(60, 62, 80, 60, 63, 80, "Ivysaur",
                  "Grass", "Poison", bulletSeed, razorLeaf, vineWhip, solarBeam);
  Pokemon charizard(78, 84, 109, 100, 78, 85, "Charizard",
                    "Fire", "Flying", flamethrower, flareBlitz, fly, rockSmash);
  Pokemon lucario(70, 110, 115, 90, 70, 70, "Lucario",
                  "Fighting", "Steel", auraSphere, forcePalm, extremeSpeed, doubleTeam);
  Pokemon greninja(72, 95, 103, 122, 67, 71, "Greninja",
                   "Water", "Dark", waterShuriken, shadowSneak, hydroPump, substitute);
  Pokemon incineroar(95, 115, 80, 60, 90, 90, "Incineroar",
                     "Fire", "Dark", darkestLariat, throatChop, crossChop, revenge);

  std::vector<Pokemon> pokemonList;
  pokemonList.push_back(pikachu);
  pokemonList.push_back(jigglyPuff);
  pokemonList.push_back(pichu);
  pokemonList.push_back(mewTwo);
  pokemonList.push_back(squirtle);
  pokemonList.push_back(ivysaur);
  pokemonList.push_back(charizard);
  pokemonList.push_back(lucario);
  pokemonList.push_back(greninja);
  pokemonList.push_back(incineroar);

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::uniform_int_distribution<int> distribution(0,255);
  auto rng = std::bind( distribution, generator );

  std::string firstName;
  // std::string secondName;
  int numPokemon;
  std::vector<Pokemon> firstList;
  std::vector<Pokemon> secondList;

  std::cout << "Trainer 1, what is your name?" << std::endl;
  std::cin >> firstName;
  // std::cout << "Trainer 2, what is your name?" << std::endl;
  // std::cin >> secondName;
  std::cout << "Will this be a [3] on 3 or a [5] on 5 battle?" << std::endl;
  std::cin >> numPokemon;
  while (numPokemon != 5 && numPokemon != 3) {
    std::cout << "Will this be a [3] on 3 or a [5] on 5 battle?" << std::endl;
    std::cin >> numPokemon;
  }

  for (int i = 0; i < numPokemon; i++) {
    int firstChoice;
    std::cout << firstName << ", please select a Pokemon: " << std::endl;
    for (int j = 0; j < pokemonList.size(); j++) {
      std::cout << j + 1 << ") " << pokemonList[j].getName() << std::endl;
    }
    std::cout << pokemonList.size() + 1 << ") Random" << std::endl;
    std::cin >> firstChoice;
    while (firstChoice < 1 || firstChoice > pokemonList.size() + 1) {
      std::cout << firstName << ", please select a Pokemon: " << std::endl;
      for (int j = 0; j < pokemonList.size(); j++) {
        std::cout << j + 1 << ") " << pokemonList[j].getName() << std::endl;
      }
      std::cout << pokemonList.size() + 1 << ") Random" << std::endl;
      std::cin >> firstChoice;
    }
    if (firstChoice == pokemonList.size() + 1) {
      firstChoice = (rng() % (int) pokemonList.size()) + 1;
    }
    firstList.push_back(pokemonList[firstChoice - 1]);
    pokemonList.erase(pokemonList.begin() + firstChoice - 1);
    int secondChoice;
    /* std::cout << secondName << ", please select a Pokemon: " << std::endl;
    for (int j = 0; j < pokemonList.size(); j++) {
      std::cout << j + 1 << ") " << pokemonList[j].getName() << std::endl;
    }
    std::cout << pokemonList.size() + 1 << ") Random" << std::endl;
    std::cin >> secondChoice;
    while (secondChoice < 1 || secondChoice > pokemonList.size() + 1) {
      std::cout << secondName << ", please select a Pokemon: " << std::endl;
      for (int j = 0; j < pokemonList.size(); j++) {
        std::cout << j + 1 << ") " << pokemonList[j].getName() << std::endl;
      }
      std::cout << pokemonList.size() + 1 << ") Random" << std::endl;
      std::cin >> secondChoice;
    }
    if (secondChoice == pokemonList.size() + 1) {
      secondChoice = (rng() % (int) pokemonList.size()) + 1;
    } */
    secondChoice = (rng() % (int) pokemonList.size()) + 1;
    secondList.push_back(pokemonList[secondChoice - 1]);
    pokemonList.erase(pokemonList.begin() + secondChoice - 1);
  }

  Trainer trainerOne(firstName, numPokemon, firstList);
  // Trainer trainerTwo(secondName, numPokemon, secondList);
  AITrainer trainerTwo("CPU", numPokemon, secondList);

  trainerOne.selectPokemon(trainerTwo);
  trainerTwo.selectPokemon(trainerOne);
  while (!trainerOne.loses() && !trainerTwo.loses()) {
    trainerOne.displayTrainer();
    trainerTwo.displayTrainer();
    if (trainerOne.currentPokemon->isFainted()) {
      trainerOne.selectPokemon(trainerTwo);
    } else if (trainerTwo.currentPokemon->isFainted()) {
      trainerTwo.selectPokemon(trainerOne);
    } else {
      int firstOption = trainerOne.optionSelect(trainerTwo);
      if (firstOption == 2) {
        trainerOne.selectPokemon(trainerTwo);
        trainerOne.displayTrainer();
        trainerTwo.displayTrainer();
        int secondOption = trainerTwo.optionSelect(trainerOne);
        if (secondOption == 2) {
          trainerTwo.selectPokemon(trainerOne);
        } else {
          int move = trainerTwo.selectMove(trainerOne);
          trainerTwo.currentPokemon->attack(*(trainerOne.currentPokemon), move, rng() % 100, rng());
        }
      } else {
        int secondOption = trainerTwo.optionSelect(trainerOne);
        if (secondOption == 2) {
          trainerTwo.selectPokemon(trainerOne);
          trainerOne.displayTrainer();
          trainerTwo.displayTrainer();
          int move = trainerOne.selectMove(trainerTwo);
          trainerOne.currentPokemon->attack(*(trainerTwo.currentPokemon), move, rng() % 100, rng());
        } else {
          int oneMove = trainerOne.selectMove(trainerTwo);
          int twoMove = trainerTwo.selectMove(trainerOne);
          if (trainerOne.currentPokemon->getSpd() > trainerTwo.currentPokemon->getSpd()) {
            trainerOne.currentPokemon->attack(*(trainerTwo.currentPokemon), oneMove, rng() % 100, rng());
            if (!trainerTwo.currentPokemon->isFainted()) {
              trainerTwo.currentPokemon->attack(*(trainerOne.currentPokemon), twoMove, rng() % 100, rng());
            }
          } else if (trainerTwo.currentPokemon->getSpd() > trainerOne.currentPokemon->getSpd()) {
            trainerTwo.currentPokemon->attack(*(trainerOne.currentPokemon), twoMove, rng() % 100, rng());
            if (!trainerOne.currentPokemon->isFainted()) {
              trainerOne.currentPokemon->attack(*(trainerTwo.currentPokemon), oneMove, rng() % 100, rng());
            }
          } else {
            if (rng() % 2 == 0) {
              trainerOne.currentPokemon->attack(*(trainerTwo.currentPokemon), oneMove, rng() % 100, rng());
              if (!trainerTwo.currentPokemon->isFainted()) {
                trainerTwo.currentPokemon->attack(*(trainerOne.currentPokemon), twoMove, rng() % 100, rng());
              }
            } else {
              trainerTwo.currentPokemon->attack(*(trainerOne.currentPokemon), twoMove, rng() % 100, rng());
              if (!trainerOne.currentPokemon->isFainted()) {
                trainerOne.currentPokemon->attack(*(trainerTwo.currentPokemon), oneMove, rng() % 100, rng());
              }
            }
          }
        }
      }
    }
  }

  if (trainerOne.loses()) {
    std::cout << trainerTwo.getName() << " wins!" << std::endl;
  } else {
    std::cout << trainerOne.getName() << " wins!" << std::endl;
  }

  return 0;
}
