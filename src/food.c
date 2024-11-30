// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#include <stdlib.h>

#include "headers/food.h"
#include "headers/cellstate.h"

int generateRandom(unsigned int *seed, int min, int max) {
  return rand_r(seed) % (max - min + 1) + min;
}

void foodRandomPos(unsigned int *seed, struct Food *food, int map[], int mapSize) {
  int x = 0;
  int y = 0;

  // generate random position in loop to avoid position overlap
  do {
  x = generateRandom(seed, 1, mapSize - 2);
  y = generateRandom(seed, 1, mapSize - 2);
  }
  while(map[(y*mapSize)+x] == SNAKE_HEAD || map[(y*mapSize)+x] == SNAKE_BODY );


  // change position of food
  food->x = x;
  food->y = y;
}
