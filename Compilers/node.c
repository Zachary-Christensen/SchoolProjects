#include <stdlib.h>
#include <stdio.h>
#include "node.h"


struct node_t *genNode(char label) {
    Node *node = malloc(sizeof(Node));
    node->label = label;

    return node;
}


