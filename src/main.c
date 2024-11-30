// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "headers/renderer.h"
#include "headers/snake.h"
#include "headers/score.h"



int main() {
    int mapSize = 25;

    // get size of window for centering
    struct winsize winSize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &winSize);

    if (winSize.ws_col < mapSize || winSize.ws_row < mapSize) {
        printf("Terminal too small to run snake!\n");
        return 1;
    }

    // initiate variables
    struct Food *food = (struct Food *)malloc(sizeof(struct Food));
    struct Snake *snake = (struct Snake *)malloc(sizeof(struct Snake));
    snake->pos.x = (mapSize - 2)/2;
    snake->pos.y = (mapSize - 2)/2;
    snake->prev = NULL;
    snake->next = NULL;


    gameLoop(mapSize, snake, food);

    free(food);
    while(snake->next) {
        struct Snake *temp = snake;
        snake = snake->next;
        free(temp);
    }

    return 0;
}
