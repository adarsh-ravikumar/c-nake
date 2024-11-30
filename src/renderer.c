// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "headers/renderer.h"
#include "headers/food.h"
#include "headers/input.h"
#include "headers/score.h"
#include "headers/snake.h"

#include "headers/cellstate.h"

void clearScreen(int screenHeight) {
  for (int i = 0; i < screenHeight; i++)
    printf("\n");
}

void centerHor(int screenWidth, int mapSize) {
  int numCols = (screenWidth / 2) - mapSize;
  for (int i = 0; i < numCols; i++)
    printf(" ");
}

void centerVer(int screenHeight, int mapSize) {
  int numRows = (screenHeight - mapSize) / 2;
  for (int i = 0; i < numRows; i++)
    printf("\n");
}

void getTermSize(struct TermSize *termSize) {

  struct winsize winSize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &winSize);

  termSize->rows = winSize.ws_row;
  termSize->cols = winSize.ws_col;
}

void checkFoodEaten(unsigned int *seed, int map[], int mapSize,
                    struct Snake *snake, struct Food *food,
                    bool *snakeMustGrow) {
  if (snake->pos.x != food->x || snake->pos.y != food->y)
    return;
  foodRandomPos(seed, food, map, mapSize);
  *snakeMustGrow = true;
}

void gameLoop(int mapSize, struct Snake *snakeHead, struct Food *food) {
  unsigned int seed = time(0);

  int *map = (int *)malloc(mapSize * mapSize * sizeof(int));
  bool gameRunning = true;

  int direction = RIGHT;

  foodRandomPos(&seed, food, map, mapSize);

  struct pollfd pfd = {.fd = 0, .events = POLLIN};
  set_term_quiet_input();

  bool snakeMustGrow = false;
  int highscore = readScore();

  struct TermSize termSize;

  while (gameRunning) {
    getTermSize(&termSize);
    clearScreen(termSize.rows);

    checkFoodEaten(&seed, map, mapSize, snakeHead, food, &snakeMustGrow);

    snakeHead = moveSnake(snakeHead, map, mapSize, direction, &snakeMustGrow,
                          &gameRunning); // returns the new head

    renderFrame(mapSize, termSize, map, snakeHead, food, highscore);

    usleep(1000 * 1000 / 10); // sleep to run at 10fps
    handleMovement(&direction, &pfd, &gameRunning);
    fflush(stdout);
  }

  // free memory
  free(map);


  // print before exit
  centerHor(termSize.cols, mapSize);
  for (int i = 0; i < mapSize - 9; i++)
    printf(" ");
  printf("\x1b[31;1m   GAME OVER!!!\x1b[0m\n");
  int score = getLength(snakeHead) - 1;

  centerHor(termSize.cols, mapSize);
  for (int i = 0; i < mapSize - 9; i++)
    printf(" ");
  if (score < 10)
    printf("\x1b[32;1mYour score was: 0%d\x1b[0m\n", score);
  else
    printf("\x1b[32;1mYour score was: %d\x1b[0m\n", score);

  centerHor(termSize.cols, mapSize);
  for (int i = 0; i < mapSize - 9; i++)
    printf(" ");
  if (highscore < score) {
    writeScore(score);
    printf("\x1b[32;1mNew Highscore !!!!\n\x1b[0m");
  } else {
    if (highscore < 10)
      printf("\x1b[32;1mHighscore:      0%d\n\x1b[0m", highscore);
    else
      printf("\x1b[32;1mHighscore:      %d\n\x1b[0m", highscore);
  }
}

void renderFrame(int mapSize, struct TermSize termSize, int *gameState,
                 struct Snake *snake, struct Food *food, int highscore) {

  // draw walls
  for (int y = 0; y < mapSize; y++) {
    for (int x = 0; x < mapSize; x++) {
      if (y == 0 || y == mapSize - 1 || x == 0 || x == mapSize - 1)
        gameState[(mapSize * y) + x] = WALL;

      else if (y == food->y && x == food->x)
        gameState[(mapSize * y) + x] = FOOD;

      else
        gameState[(mapSize * y) + x] = EMPTY;
    }
  }

  // draw snake
  struct Snake *curPiece = snake;
  bool isHead = true;

  while (curPiece != NULL) {
    int idx = (mapSize * curPiece->pos.y) + curPiece->pos.x;
    if (isHead) {
      isHead = false;
      gameState[idx] = SNAKE_HEAD;

    } else {
      gameState[idx] = SNAKE_BODY;
    }

    curPiece = curPiece->next;
  }

  // print title
  centerHor(termSize.cols, mapSize);
  for (int i = 0; i < (mapSize)-3; i++)
    printf(" ");
  printf("\x1b[32;1mC->nake\x1b[0m  \n");
  // instructions
  centerHor(termSize.cols, mapSize);
  for (int i = 0; i < mapSize - 7; i++)
    printf(" ");
  printf("\x1b[32;1mw a s d to move\x1b[0m\n\n");

  // print score
  centerHor(termSize.cols, mapSize);
  printf("🍎 %d", getLength(snake) - 1);
  for (int i = 0; i < (mapSize * 2) - 18; i++)
    printf(" ");
  if (highscore < 10)
    printf("\x1b[32;1mHigh Score: 0%d\n\x1b[0m\n", highscore);
  else
    printf("\x1b[32;1mHigh Score: %d\n\x1b[0m\n", highscore);

  for (int y = 0; y < mapSize; y++) {
    // print spaces to center game board on screen
    centerHor(termSize.cols, mapSize);
    for (int x = 0; x < mapSize; x++) {
      switch (gameState[(mapSize * y) + x]) {
      case FOOD:
        printf("🍎");
        break;
      case WALL:
        printf("⬛");
        break;
      case SNAKE_HEAD:
        printf("🟩");
        break;
      case SNAKE_BODY:
        printf("🟩");
        break;

      case EMPTY:
        printf("  ");
        break;
      }
    }
    printf("\n");
  }

  centerVer(termSize.rows, mapSize + 5);
}
