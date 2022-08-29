
#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "token.h"
#include "node.h"

struct symbol_t {
    struct symbol_t *nextSymbol;
    char *name;
} typedef Symbol;

Symbol *getTable();

void insert(Symbol *symbol);
int verify(char *value);

void semerror(char *msg);

Symbol *semantics(Node *root);
void r_semantics(Node* node);

void printSymbolTable();

void gerror(char *msg, char *msg1);
void printASM(char *code);
void setupTranslate(char *filename);
void endTranslate();
void translate(Node* root);


#endif // SEMANTICS_H