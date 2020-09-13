//
// Created by Darin Lee on 6/14/2020.
//

#include "Move.h"

Move::Move(std::string name, std::string type, std::string cat, int pwr, int acc, int pp) :
name(std::move(name)), type(std::move(type)), cat(std::move(cat)), pwr(pwr), acc(acc), pp(pp), currentPP(pp) {}

std::string Move::getName() {
  return name;
}

std::string Move::getType() {
  return type;
}

std::string Move::getCat() {
  return cat;
}

int Move::getPwr() const {
  return pwr;
}

int Move::getAcc() const {
  return acc;
}

int Move::getPP() const {
  return pp;
}
