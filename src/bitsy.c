#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

struct termios origTermInfo;

// Error handler
void die (const char * errorMsg){
  perror(errorMsg);
  exit(1);
}

void enableCanonicalMode () {
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermInfo) == -1 )
      die(tcsetattr);
}

// ECHO, ICANON, ISIG , IXON, IEXTEN, ICRNL are individual bits in c_lflag.
void disableCanonicalMode () {
  if(tcgetattr(STDIN_FILENO, &origTermInfo) == -1)
     die(tcgetattr);
  atexit(enableCanonicalMode);

  struct termios termInfo = origTermInfo;
  tcgetattr(STDIN_FILENO, &termInfo);
  termInfo.c_lflag &= ~(IXON | ICRNL);
  termInfo.c_oflag &= ~(OPOST);
  termInfo.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termInfo) == -1)
     die(tcsetattr);

  //  reads as soon as input is available
  termInfo.c_cc[VMIN] = 0;    
  // Wait 100 ms before returning read().
  termInfo.c_cc[VTIME] = 1;   
}

int main () {
  disableCanonicalMode();

  while (1) {
    char c ;
    if (read(STDIN_FILENO, &c, 1) == -1) 
        die("read");
    // Displaying only non-control characters
    if ( !iscntrl(c) ) {                     
      printf("%c\r\n", c);
    }

    if (c == 'q') break;
  };

  return 0;
}

