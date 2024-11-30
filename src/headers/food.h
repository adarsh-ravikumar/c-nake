// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#pragma once
#include "snake.h"

typedef struct Food {
    int x;
    int y;
} Food;

void foodRandomPos(unsigned int *seed, struct Food *food, int map[], int mapSize);
