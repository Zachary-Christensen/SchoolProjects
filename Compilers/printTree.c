#include <stdio.h>
#include <stdlib.h>
#include "printTree.h"


void printParseTree(Node *root, int level) {
    if (root == NULL) return;

    printf("%*c%c\n", level * 2, ' ', root->label);

    int i;
    // i = 8 because max number of tokens + children for any rule is 7 for rule F
    for (i = 8; i >= 0; i--) {
        if ((root->orderOfTokensAndChildren >> i) % 2 != 0) {
            break;
        }
    }
    

    if (root->child1 == NULL && root->token1 == NULL) {
        printf("%*c%s\n", (level + 1) * 2, ' ', "Empty");
    }
    else {
        level++; // all tokens and children of node are printed on next level
        int tokenCounter = 0;
        int childCounter = 0;
        int numberOfChildrenAndTokens = i - 1;

        for (i = numberOfChildrenAndTokens; i >= 0; i--) {
            if ((root->orderOfTokensAndChildren >> i) % 2 != 0) { // indexed bit = 1, therefore represents child
                switch (childCounter)
                {
                    case 0:
                        if (root->child1 == NULL) {
                            fprintf(stderr, "%c Null Child1\n", root->label);
                            exit(EXIT_FAILURE);
                        }
                        printParseTree(root->child1, level);
                        break;
                    case 1:
                        if (root->child2 == NULL) {
                            fprintf(stderr, "%c Null Child2\n", root->label);
                            exit(EXIT_FAILURE);
                        }
                        printParseTree(root->child2, level);
                        break;
                    case 2:
                        if (root->child3 == NULL) {
                            fprintf(stderr, "%c Null Child3\n", root->label);
                            exit(EXIT_FAILURE);
                        }
                        printParseTree(root->child3, level);
                        break;
                }
                childCounter++;
            }
            else { // indexed bit = 0, therefore represents token
                switch (tokenCounter)
                {
                    case 0:
                        if (root->token1 == NULL) {
                            fprintf(stderr, "%c Null Token1\n", root->label);
                            exit(EXIT_FAILURE);
                        }
                        printTokenValue(root->token1, level);
                        break;
                    case 1:
                    if (root->token2 == NULL) {
                            fprintf(stderr, "%c Null Token2\n", root->label);
                            exit(EXIT_FAILURE);
                        }
                        printTokenValue(root->token2, level);
                        break;
                    case 2:
                    if (root->token3 == NULL) {
                            fprintf(stderr, "%c Null Token3\n", root->label);
                            exit(EXIT_FAILURE);
                        }
                        printTokenValue(root->token3, level);
                        break;
                    case 3:
                        if (root->token4 == NULL) {
                            fprintf(stderr, "%c Null Token4\n", root->label);
                            exit(EXIT_FAILURE);
                        }
                        printTokenValue(root->token4, level);
                        break;
                }
                tokenCounter++;
            }
        }
    }
}

void printTokenValue(Token* token, int level) {
    if (token->tokenID == IDENT_tk) {
        printf("%*cIdentifier %s\n", level * 2, ' ', token->value);
    }
    else {
        printf("%*c%s\n", level * 2, ' ', token->value);
    }
}

