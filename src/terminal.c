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
  // Wait 100 ms before returning read() inside editorReadKey()
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
  /* Pressing arrow keys send multiple bytes starting with escape sequence
     So, if escape sequence is read, read the following two bytes after it.
  */
  if ( input == '\x1b') {
      char seq[3];
      if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
      if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
      if (seq[0] == '[') {
         switch (seq[1]) {
            case 'A': return ARROW_UP;
            case 'B': return ARROW_DOWN;
            case 'C': return ARROW_RIGHT;
            case 'D': return ARROW_LEFT;
         }
      }
      return '\x1b';
  } 
  else {
    return input;
  }
}

int getCursorPosition(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;
  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    // VT100 response for cursor position query contains "R" in the last bit
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';
  if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  // parsing cursor position from the VT100 response.
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
  return 0;
}

int getWindowSize(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1;
    return getCursorPosition(rows, cols);
  } 
  else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}