
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "errorOutput.h"

const int MESSAGE_SIZE;
char errorMessage[256];

int isScannerInitialized = 0;
char nextChar;
int lineNumber = 0;

const int NUMBER_OF_RESERVEDWORDS = 13;
const int MAX_RESERVEDWORD_LENGTH = 25;
const char reservedWords[13][25] = {
    "Again", "If", "Assign", "Move", "Show", "Flip", "Name", "Home", "Do", "Spot", "Place", "Here", "There"
};

const int NUMBER_OF_STATES = 7;
const int NUMBER_OF_INPUTS = 15;
const int Table[7][15] = {
    {0,1,3,4,6,6,6,6,6,6,5,-1,1005,-1, 6},
    {-1,2,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {1001,2,2,2,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001},
    {1002,3,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002},
    {1004,1004,1004,4,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,6,-1,-1,-1},
    {1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003}
};

void serror(char *msg) {
    sprintf(errorMessage, "Scanner Error: Line number: %d. %s", lineNumber, msg);
    printError(errorMessage);
    exit(EXIT_FAILURE);
}

char readChar() {
    char ch = getc(scannerFile);

    if (ch == '\n') lineNumber++;
    return ch;
}

Token *FADriver() {

    int state = 0; // initial state
    int nextState = 0;
    Token *token = (Token*)malloc(sizeof(Token));
    char str[MAX_TOKENVALUE_LENGTH];
    strcpy(str, "");

    while (!isFinalState(state)) {
        if (nextChar == '*') { // start of comment. read until end of comment
            while ((nextChar = readChar()) != '*') {
                if (nextChar == EOF) {
                    serror("Reached end of file without reaching end of comment");
                }
            }

            nextChar = readChar();
        }

        nextState = Table[state][getIndexFromChar(nextChar)];
        if (nextState < 0) { // is error
            char errorMsg[getErrorMessageSize()];
            sprintf(errorMsg, "state: %d nextState: %d char: %c", state, nextState, nextChar);
            serror(errorMsg);
        }
        else if (nextState > 1000) { // if next state is final state
            if (getTokenID(nextState) == KW_tk) { // if keyword, then validate that it exists in list otherwise throw error
                if (isReservedWord(str) == 0) {
                    serror("Reserved word not found");
                }
            }

            token->tokenID = getTokenID(nextState);
            sprintf(token->value, "%s", str);

            if (nextChar == '\n' || nextChar == EOF) token->lineNumber = lineNumber - 1;
            else token->lineNumber = lineNumber;

            return token;
        }
        else { // not final
            state = nextState;

            if (nextChar == ' ' || nextChar == '\t' || nextChar == '\n') { // if char is whitespace, then do not add to string but still advance character
                
                nextChar = readChar();
                continue;
            }

            if (strlen(str) >= MAX_TOKENVALUE_LENGTH - 1) {
                serror("Token length was too long");
            }
            sprintf(str, "%s%c", str, nextChar);
            
            nextChar = readChar();
        }
    }
    
    return token; // returning token here to appease the compiler
}

TokenID getTokenID(int number) {
    switch (number)
    {
        case 1001:
            return IDENT_tk;
        case 1002:
            return KW_tk;
        case 1003:
            return OP_tk;
        case 1004:
            return NUM_tk;
        case 1005:
            return EOF_tk;
        default:
            serror("Incorrect code for token");
    }
    return EOF_tk; // I return EOF_tk here to appease the compiler
}

int isReservedWord(char* word) {
    int i;
    for (i = 0; i < NUMBER_OF_RESERVEDWORDS; i++) {
        if (strcmp(reservedWords[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int isFinalState(int state) {
    return state > 1000 || state < 0; // if state > 1000 then is token, if state < 0 then is an error, otherwise points to the next state
}

int getIndexFromChar(char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\n') { // is white space
        return 0;
    }
    else if (ch >= 'a' && ch <= 'z') { // is lower case letter
        return 1;
    }
    else if (ch >= 'A' && ch <= 'Z') { // is upper case letter
        return 2;
    }
    else if (ch >= '0' && ch <= '9') { // is digit
        return 3;
    }
    else if (ch == '&') {
        return 4;
    }
    else if (ch == '+') {
        return 5;
    }
    else if (ch == '/') {
        return 6;
    }
    else if (ch == '%') {
        return 7;
    }
    else if (ch == '{') {
        return 8;
    }
    else if (ch == '}') {
        return 9;
    }
    else if (ch == '<') {
        return 10;
    }
    else if (ch == '-') {
        return 11;
    }
    else if (ch == EOF) {
        return 12;
    }
    else if (ch == '.') {
        return 14;
    }
    else {
        return 13;
    }
}

void initScanner() {
    if (isScannerInitialized) return;

    nextChar = readChar();

    isScannerInitialized = 1;
}

// https://stackoverflow.com/questions/252780/why-should-we-typedef-a-struct-so-often-in-c?noredirect=1&lq=1
Token *scanner() {

    if (!isScannerInitialized) {
        serror("Scanner has not been initialized");
    }

    return FADriver();
}


