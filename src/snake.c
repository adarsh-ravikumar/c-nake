// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/snake.h"
#include "headers/cellstate.h"

struct Snake *getTail(struct Snake *head) {
  struct Snake *curPiece = head;

  while (curPiece->next != NULL) {
    curPiece = curPiece->next;
  }

  return curPiece;
}

void directionToDelta(int direction, int *dx, int *dy) {
  switch (direction) {
  case UP:
    *dy = -1;
    *dx = 0;
    break;

  case DOWN:
    *dy = 1;
    *dx = 0;
    break;

  case LEFT:
    *dx = -1;
    *dy = 0;
    break;

  case RIGHT:
    *dx = 1;
    *dy = 0;
    break;
  }
}

// insert item to the front of the doubly linked list
struct Snake *moveSnake(struct Snake *snake, int map[], int mapSize,
                        int direction, bool *grow, bool *gameRunning) {
  int dx, dy = 0;
  directionToDelta(direction, &dx, &dy);

  // check for collision with walls
  if (snake->pos.x + dx <= 0 || snake->pos.x + dx > mapSize - 2 ||
      snake->pos.y + dy <= 0 || snake->pos.y + dy > mapSize - 2) {
    *gameRunning = false;
    return snake;
  }

  // check for collision with self
  if (map[(snake->pos.y + dy) * mapSize + snake->pos.x + dx] == SNAKE_BODY) {
    *gameRunning = false;
    return snake;
  }

  // create new head
  struct Snake *newHead = (struct Snake *)malloc(sizeof(struct Snake *));
  snake->prev = newHead;

  newHead->prev = NULL;
  newHead->next = snake;

  newHead->pos.x = snake->pos.x + dx;
  newHead->pos.y = snake->pos.y + dy;

  // remove the tail
  if (*grow == true) {
    *grow = false;
    return newHead;
  }

  struct Snake *tail = getTail(newHead);
  tail->prev->next = NULL;
  free(tail);

  return newHead;
}

// get length of doubly linked list
int getLength(struct Snake *head) {
  struct Snake *curPiece = head;
  int length = 0;

  do {
    curPiece = curPiece->next;
    length++;
  } while (curPiece != NULL);

  return length;
}
