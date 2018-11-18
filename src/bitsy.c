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

  termInfo.c_cc[VMIN] = 0;    // Minimum 0 byte : reads as soon as input is available
  termInfo.c_cc[VTIME] = 1;   // Wait 100 ms before returning read().
}

int main () {
  disableCanonicalMode();

  while (1) {
    char c ;
    read(STDIN_FILENO, &c, 1);
    if (!iscntrl(c)) {                     // Displaying only non-control characters
      printf("%c\r\n", c);
    }

    if (c == 'q') break;
  };

  return 0;
}

