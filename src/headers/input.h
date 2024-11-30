// C->Nake
// Copyright 2024 Adarsh Ravikumar
// This code is licensed under the MIT license.
// See the LICENSE file in the project root for license terms

#include <stdbool.h>
#include <sys/poll.h>

void set_term_quiet_input();
void handleMovement(int *currentDirection, struct pollfd* poll, bool *gameRunning);
