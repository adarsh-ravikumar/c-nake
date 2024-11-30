// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#include <stdbool.h>
#include <stdio.h>
#include <sys/poll.h>
#include <termios.h>

#include "headers/input.h"
#include "headers/snake.h"

// based on answers for:
// https://stackoverflow.com/questions/717572/how-do-you-do-non-blocking-console-i-o-on-linux-in-c
void set_term_quiet_input() {
  struct termios tc;
  tcgetattr(0, &tc);
  tc.c_lflag &= ~(ICANON | ECHO);
  tc.c_cc[VMIN] = 0;
  tc.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &tc);
}

void handleMovement(int *currentDirection, struct pollfd *pfd,
                    bool *gameRunning) {
  if (!gameRunning)
    return;
  if (!(poll(pfd, 1, 0) > 0))
    return;

  switch (getchar()) {
  case 'w': // UP
    if (*currentDirection == DOWN)
      break;
    *currentDirection = UP;
    break;
  case 's': // DOWN
    if (*currentDirection == UP)
      break;
    *currentDirection = DOWN;
    break;
  case 'a': // LEFT
    if (*currentDirection == RIGHT)
      break;
    *currentDirection = LEFT;
    break;
  case 'd': // RIGHT
    if (*currentDirection == LEFT)
      break;
    *currentDirection = RIGHT;
    break;
  default:
    break;
  }
}
