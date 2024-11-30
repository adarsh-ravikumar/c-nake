// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#pragma once
#include <stdbool.h>

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Snake {
  Position pos;
  struct Snake *next;
  struct Snake *prev;
} Snake;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Snake *getTail(struct Snake *head);
int getLength(struct Snake *head);

struct Snake *moveSnake(struct Snake *head, int map[], int mapSize, int direction,
    bool *grow, bool *gameRunning);
