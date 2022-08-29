

#ifndef SCANNER_H
#define SCANNER_H
#include <stdio.h>
#include "token.h"

extern FILE* scannerFile;

void serror(char *msg);

void initScanner();

Token *scanner();

Token *FADriver();

int isFinalState(int);

int getIndexFromChar(char);

int isReservedWord(char*);

TokenID getTokenID(int);

char readChar();

#endif // SCANNER_H
