#ifndef BUFFER_H
#define BUFFER_H

struct appendBuffer {
  char *buf;
  int len;
};

void abufAppend(struct appendBuffer *abuf, const char *s, int len);
void abufFree(struct appendBuffer *abuf);

#endif