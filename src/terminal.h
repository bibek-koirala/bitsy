#ifndef TERMINAL_H
#define TERMINAL_H

void die (const char * errorMsg);
void enableCanonicalMode ();
void disableCanonicalMode ();
char editorReadKey ();

#endif
