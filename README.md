# C->nake
A simple snake game written in C. Everything is rendered right in the terminal with good old printf. No fancy libraries, no window frameworks, just plain printf :).

This is the first proper project that I am building in C, so the code might be abit rough. Everything was written on and for linux, so I am not sure about it running on windows.

### Implementation Details
- The snake is a doubly linked list. A new head is created in the direction of movement, all the nodes in the old list is moved to the new list and the tail is popped to create the illusion of movement.
- When the snake eats food, it grows by simple not popping the tail when moving, since the movement handler is called every frame.
- The board itself is stored in memory as a 1D int array, with an enum handling the state of each "pixel"
- The highscore is stored in a binary file.

### Resources
- Doubly linked lists    - https://www.geeksforgeeks.org/doubly-linked-list/
- File handling in C     - https://www.geeksforgeeks.org/basics-file-handling-c/
- RNG in C               - https://www.geeksforgeeks.org/c-rand-function/
- Emojis (for rendering) -    https://emojipedia.org/

- The answer to this issue made the input possible, since all other methods were giving me buggy results. https://stackoverflow.com/questions/717572/how-do-you-do-non-blocking-console-i-o-on-linux-in-c
