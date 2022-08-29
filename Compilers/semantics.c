#include "semantics.h"
#include "errorOutput.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Symbol *rootSym;
Token *tk;

FILE *outputFile;
int labelCounter = 1;
int tempVarCounter = 1;
const int LABEL_LENGTH = 50;
const int ASMSTR_LENGTH = 200;
const int SYMBOLNAME_LENGTH = 25;

void semerror(char *msg) {
    char errorMessage[getErrorMessageSize()];
    sprintf(errorMessage, "Semantic error: %s. line number: %d. value '%s'", msg, tk->lineNumber, tk->value);
    printError(errorMessage);
    exit(EXIT_FAILURE);
}

Symbol *getTable() {
    return rootSym;
}

void printSymbolTable() {
    Symbol *symbol = rootSym;

    fprintf(stderr, "Symbol Table:\n");
    while(symbol != NULL) {
        fprintf(stderr, "   %s\n", symbol->name);
        symbol = symbol->nextSymbol;
    }
}

void insert(Symbol *symbol) {
    if (rootSym == NULL) {
        rootSym = symbol;
    }
    else {
        Symbol *sym = rootSym;
        while (1) {
            if (sym->nextSymbol == NULL) {
                if (strcmp(sym->name, symbol->name) != 0) {
                    sym->nextSymbol = symbol;
                    break;
                }
                else {
                    semerror("Identifiers already declared");
                }
            }
            sym = sym->nextSymbol;
        }
    }
}

int verify(char *value) {
    Symbol *sym = rootSym;

    while (sym != NULL) {
        if (strcmp(sym->name, value) == 0) {
            return 0;
        }
        sym = sym->nextSymbol;
    }
    return 1;
}

Symbol *semantics(Node *root) {
    r_semantics(root);
    return rootSym;
}

void r_semantics(Node* root) {
    if (root == NULL) return;

    int i;
    // i = 8 because max number of tokens + children for any rule is 7 for rule F
    for (i = 9; i >= 0; --i) {
        if ((root->orderOfTokensAndChildren >> i) % 2 != 0) {
            break;
        }
    }
    int numberOfChildrenAndTokens = i - 1;

    if (root->child1 == NULL && root->token1 == NULL) {
        
    }
    else {
        int tokenCounter = 0;
        int childCounter = 0;
        
        for (i = numberOfChildrenAndTokens; i >= 0; i--) {
            
            if ((root->orderOfTokensAndChildren >> i) % 2 != 0) { // indexed bit = 1, therefore represents child
                switch (childCounter)
                {
                    case 0:
                        r_semantics(root->child1);
                        break;
                    case 1:
                        r_semantics(root->child2);
                        break;
                    case 2:
                        r_semantics(root->child3);
                        break;
                }
                childCounter++;
            }
            else { // indexed bit = 0, therefore represents token
                Token *currentToken;
                switch (tokenCounter)
                {
                    case 0:
                        currentToken = root->token1;
                        break;
                    case 1:
                        currentToken = root->token2;
                        break;
                    case 2:
                        currentToken = root->token3;
                        break;
                    case 3:
                        currentToken = root->token4;
                        break;
                }
                tokenCounter++;
                if (currentToken == NULL) {
                    semerror("NULL token error");
                }
                tk = currentToken;


                if (currentToken->tokenID == KW_tk && (strcmp(currentToken->value, "Name") == 0 || strcmp(currentToken->value, "Spot") == 0)) {
                    switch (tokenCounter)
                    {
                        case 0:
                            currentToken = root->token1;
                            break;
                        case 1:
                            currentToken = root->token2;
                            break;
                        case 2:
                            currentToken = root->token3;
                            break;
                        case 3:
                            currentToken = root->token4;
                            break;
                    }
                    // advance beyond consumed identifier token so it is not checked upon further iteration
                    tokenCounter++;
                    i--;
                    if (currentToken == NULL) {
                        semerror("NULL token error");
                    }
                    tk = currentToken;
                
                    if (currentToken->tokenID != IDENT_tk) {
                        if (currentToken->tokenID != NUM_tk) semerror("Name and Spot must be preceded by an identifier");
                    }
                    else if (verify(currentToken->value)) {
                        Symbol *symbol = malloc(sizeof(Symbol));
                        symbol->name = currentToken->value;
                        insert(symbol);
                    }
                    else {
                        semerror("Redefining variable error");
                    }
                }
                else if (currentToken->tokenID == IDENT_tk) {
                    if (verify(currentToken->value)) {
                        semerror("Undefined variable error");
                    }
                }
            }
        }
    }
}



void printASM(char *code) {
    fprintf(outputFile, "%s", code);
}

void setupTranslate(char *filename) {
    outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        gerror("Unable to open file", filename);
    }
}

void endTranslate() {
    fclose(outputFile);
}

void gerror(char *msg, char *msg1) {
    char buffer[getErrorMessageSize()];
    sprintf(buffer, "Translator Error: %s %s", msg, msg1);
    printError(buffer);
    exit(EXIT_FAILURE);
}

void translate(Node *root) {
    if (root == NULL) return;
    else if (root->child1 == NULL && root->token1 == NULL) return; // is empty

    // Delimiters: {}. Place Home
    // Operators: << is <, <- is >=, / is decrement, + is +, % is divide and truncate remainder, & is *
    // Name Identifier: allocate memory for Identifier and initialize to 0
    // Assign Identifier M: assign value of M to identifier. M does not exist. M is D when D only points to H or L. Can assume tests will only include valid code
    // { If Identifier T W D }: do D if and only if Identifier T W is true
    // { Do Again D T W }: repeat D until T W zero is false
    // Spot Number: load number into ACC
    // Spot Identifier: read int and store in Identifier
    // Show Number: write number to screen
    // Show Identifier: write Identifier to screen
    // Move Identifier: load Identifier into ACC
    // Flip Identifier: multiply Identifier by -1 and store in Identifier
    // Here Number There: print the number to the screen the given number of times

    char labelStr[25];
    sprintf(labelStr, "'%c'", root->label);
    char asmStr[ASMSTR_LENGTH];
    char brlabel[LABEL_LENGTH];
    char symbolName[SYMBOLNAME_LENGTH];
    Symbol *symbol;
    // fprintf(stderr, "Translating <%c>\n", root->label);
    switch (root->label)
    {
    case 'S': // Name Identifier Spot Identifier R E
        printASM("LOAD 0\n");
        sprintf(asmStr, "STORE %s\n", root->token2->value);
        printASM(asmStr);
        
        sprintf(asmStr, "READ %s\n", root->token4->value);
        printASM(asmStr);

        translate(root->child1);
        translate(root->child2);

        printASM("End: STOP\n");
        
        Symbol *symbol = getTable();
        while (symbol != NULL) {
            sprintf(asmStr, "%s 0\n", symbol->name);
            printASM(asmStr);
            symbol = symbol->nextSymbol;
        }
        break;
    case 'R': // Place A B Home
        translate(root->child1);
        translate(root->child2);
        break;
    case 'E': // Show Identifier
        sprintf(asmStr, "WRITE %s\n", root->token2->value);
        printASM(asmStr);
        break;
    case 'A': // Name Identifier
        printASM("LOAD 0\n");
        sprintf(asmStr, "STORE %s\n", root->token2->value);
        printASM(asmStr);
        break;
    case 'B': // empty | . C . B | D B
        translate(root->child1);
        translate(root->child2);
        break;
    case 'C': // F | G
        translate(root->child1);
        break;
    case 'D': // H | J | K | L | E | F
        translate(root->child1);
        break;
    case 'F': // { If Identifier T W D } | { Do Again D T W }
        if (root->token3->tokenID == IDENT_tk) { // { If Identifier T W D }: do D if and only if Identifier T W is true
        
            translate(root->child2); // W is loaded into accumulator
            sprintf(asmStr, "SUB %s\n", root->token3->value);
            printASM(asmStr);

            sprintf(brlabel, "A%d", labelCounter++);
            if (strcmp(root->child1->token1->value, "<<") == 0) { // true when Identifier less than W. Subtract Identifier from W, then use brzneg to jump over D
                sprintf(asmStr, "BRZNEG %s\n", brlabel);
                printASM(asmStr);
            }
            else { // true when Identifier greater than or equal to W, Subtract Identifier from W, then use brpos to jump over D
                sprintf(asmStr, "BRPOS %s\n", brlabel);
                printASM(asmStr);
            }

            translate(root->child2);

            sprintf(asmStr, "%s: NOOP\n", brlabel);
            printASM(asmStr);
        }
        else { // { Do Again D T W }: repeat D until T W zero is false
            labelCounter++;
            labelCounter++;
            sprintf(brlabel, "A%d", labelCounter - 2);
            sprintf(asmStr, "%s: NOOP\n", brlabel);
            printASM(asmStr);
            
            translate(root->child3);

            sprintf(brlabel, "A%d", labelCounter - 1);
            if (strcmp(root->child2->token1->value, "<<") == 0) { // repeat D until W is zero or more
                sprintf(asmStr, "BRZPOS %s\n", brlabel);
                printASM(asmStr);   
            }
            else { // repeat D until W is less than zero
                sprintf(asmStr, "BRNEG %s\n", brlabel);
                printASM(asmStr);
            }

            translate(root->child1);

            sprintf(brlabel, "A%d", labelCounter - 2);
            sprintf(asmStr, "BR %s\n", brlabel);
            printASM(asmStr);

            sprintf(brlabel, "A%d", labelCounter - 1);
            sprintf(asmStr, "%s: NOOP\n", brlabel);
            printASM(asmStr);
        }
        break;
    case 'G': // Here Number There
        symbol = malloc(sizeof(Symbol));
        sprintf(symbolName, "T%d", tempVarCounter++);
        symbol->name = malloc(MAX_TOKENVALUE_LENGTH);
        sprintf(symbol->name, "%s", symbolName);
        insert(symbol);

        sprintf(brlabel, "A%d", labelCounter++);
        sprintf(asmStr, "LOAD %s\n", root->token2->value);
        printASM(asmStr);

        sprintf(asmStr, "STORE %s\n", symbolName);
        printASM(asmStr);
        
        sprintf(asmStr, "%s: NOOP\n", brlabel);
        printASM(asmStr);

        sprintf(asmStr, "WRITE %s\n", symbolName);
        printASM(asmStr);

        printASM("SUB 1\n");
        
        sprintf(asmStr, "BRPOS %s\n", brlabel);
        printASM(asmStr);
        break;
    // case 'T': // << | <-
        
    //     break;
    case 'V': // + | % | &
        if (strcmp(root->token1->value, "+") == 0) {
            printASM("ADD ");
        }
        else if (strcmp(root->token1->value, "%") == 0) {
            printASM("DIV ");
        }
        else if (strcmp(root->token1->value, "&") == 0) {
            printASM("MULT ");
        }
        break;
    case 'H': // / Z
        translate(root->child1);
        printASM("SUB 1\n");
        if (root->child1->token1->tokenID == IDENT_tk) {
            sprintf(asmStr, "STORE %s\n", root->child1->token1->value);
            printASM(asmStr);
        }
        break;
    case 'J': // Assign Identifier D
        // if (root->child1->child1->label != 'H' && root->child1->child1->label != 'L') {
        //     gerror("In rule <J>, M from 'Assign Identifier M' must be a D that points to an H or an L", "");
        // }
        // after H or L executes, their relevant values will be leftover in the accumulator
        translate(root->child1);

        sprintf(asmStr, "STORE %s\n", root->token2->value);
        printASM(asmStr);
        break;
    case 'K': // Spot Number Show Number | Move Identifier Show Identifier
        if (strcmp(root->token1->value, "Spot")) {
            sprintf(asmStr, "LOAD %s\n", root->token2->value);
            printASM(asmStr);

            sprintf(asmStr, "WRITE %s\n", root->token4->value);
            printASM(asmStr);
        }
        else {
            sprintf(asmStr, "LOAD %s\n", root->token2->value);
            printASM(asmStr);

            sprintf(asmStr, "WRITE %s\n", root->token4->value);
            printASM(asmStr);
        }
        break;
    case 'L': // Flip Identifier
        sprintf(asmStr, "LOAD %s\n", root->token2->value);
        printASM(asmStr);

        printASM("MULT -1\n");

        sprintf(asmStr, "STORE %s\n", root->token2->value);
        printASM(asmStr);
        break;
    case 'W': // Number V Number | Number .
        if (root->child1 != NULL) {
            sprintf(asmStr, "LOAD %s\n", root->token1->value);
            printASM(asmStr);
            translate(root->child1); // will add operation from V with no new line
            sprintf(asmStr, "%s\n", root->token2->value); // value for operation
            printASM(asmStr);
        }
        else {
            sprintf(asmStr, "LOAD %s\n", root->token1->value);
            printASM(asmStr);
        }
        break;
    case 'Z': // Identifier | Number
        sprintf(asmStr, "LOAD %s\n", root->token1->value);
        printASM(asmStr);
        break;
    default:
        gerror("Encountered node with invalid label. Label was", labelStr);
        break;
    }
    
}




