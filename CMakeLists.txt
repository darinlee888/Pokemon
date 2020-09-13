cmake_minimum_required(VERSION 3.6)
project(Pokemon)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pokemon main.cpp Pokemon.cpp Pokemon.h Move.cpp Move.h Trainer.cpp Trainer.h AITrainer.cpp AITrainer.h)