// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#pragma once
#include <sys/ioctl.h>

#include "food.h"
#include "snake.h"

typedef struct TermSize {
  int rows;
  int cols;
} termSize;

void checkFoodEaten(unsigned int *seed, int map[], int mapSize,
                    struct Snake *snake, struct Food *food,
                    bool *snakeMustGrow);
void gameLoop(int mapSize, struct Snake *snakeHead, struct Food *food);
void renderFrame(int mapSize, struct TermSize winSize, int *frame,
                 struct Snake *snake, struct Food *food, int highscore);
void centerHor(int screenWidth, int mapSize);
void centerVer(int screenHeight, int mapSize);
