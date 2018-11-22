#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "terminal.h"

struct editorConfig E;

// Error handler
void die (const char * errorMsg){
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  perror(errorMsg);
  exit(1);
}

void enableCanonicalMode () {
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.origTermInfo) == -1 )
      die("tcsetattr");
}


void disableCanonicalMode () {
  if(tcgetattr(STDIN_FILENO, &E.origTermInfo) == -1)
     die("tcgetattr");
  atexit(enableCanonicalMode);

  struct termios termInfo = E.origTermInfo;
  tcgetattr(STDIN_FILENO, &termInfo);

  // turning off flags related to canonical mode.
  termInfo.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  termInfo.c_oflag &= ~(OPOST);
  termInfo.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 

  //  reads as soon as input is available
  termInfo.c_cc[VMIN] = 0;    
  // Wait 100 ms before returning read().
  termInfo.c_cc[VTIME] = 1;   

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termInfo) == -1)
     die("tcsetattr");

}

char editorReadKey () {
  int hasRead;
  char input;

  while (( hasRead = read(STDIN_FILENO, &input, 1)) != 1) {
     if (hasRead == -1) die("read");
  }

  return input;
}

int getWindowSize(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}