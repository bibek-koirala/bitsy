#include <stdio.h>
#include <unistd.h>

void editorRefreshScreen() {
  // clearing the entire screen 
  write(STDOUT_FILENO, "\x1b[2J", 4);
  // Repositioning the cursor to top-left corner
  write(STDOUT_FILENO, "\x1b[H", 3);
}