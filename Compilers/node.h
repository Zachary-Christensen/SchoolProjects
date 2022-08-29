#ifndef NODE_H
#define NODE_H

#include "token.h"

struct node_t *genNode(char label);

struct node_t {
    char label;
    Token *token1;
    Token *token2;
    Token *token3;
    Token *token4;
    struct node_t *child1;
    struct node_t *child2;
    struct node_t *child3;
    int orderOfTokensAndChildren; // {Token = 0, Child = 1} ex. Child Child Token Child = 00000000 00011101. The leftmost one marks the beginning of the sequence
} typedef Node;


#endif // NODE_H