// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#include <stdio.h>

#include "headers/score.h"

int readScore() {
    // highscore
    FILE* file = fopen("highscore.bin", "rb");
    if (!file) return 0;

    int highscore;
    fread(&highscore, sizeof(int), 1, file);
    fclose(file);
    return highscore;
}



int writeScore(int highscore) {
    // highscore
    FILE* file = fopen("highscore.bin", "wb");
    if (!file) return 0;

    fwrite(&highscore, sizeof(int), 1, file);
    fclose(file);
    return highscore;
}
