#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>

struct termios origTermInfo;

void enableCanonicalMode () {
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermInfo);
}

// Disables terminal's default canonical mode just for bitsy. ECHO, ICANON, ISIG , IXON, IEXTEN, ICRNL, OPOST are individual bits in c_lflag.
void disableCanonicalMode () {
  tcgetattr(STDIN_FILENO, &origTermInfo);
  atexit(enableCanonicalMode);

  struct termios termInfo = origTermInfo;
  tcgetattr(STDIN_FILENO, &termInfo);
  termInfo.c_lflag &= ~(IXON | ICRNL);
  termInfo.c_oflag &= ~(OPOST);
  termInfo.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);    // flipping bitflags and then using bitmask c_lflag
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &termInfo);
}

int main () {
  char c ;
  while ( read(STDIN_FILENO, &c, 1) == 1);
  return 0;
}