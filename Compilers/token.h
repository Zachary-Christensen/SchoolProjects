
#ifndef TOKEN_H
#define TOKEN_H

#define NUMBER_OF_TOKENS 5
#define MAX_TOKENNAME_LENGTH 15
#define MAX_TOKENVALUE_LENGTH 100

// IDENT_tk = 1001, KW_tk = 1002, OP_tk = 1003, NUM_tk = 1004, EOF_tk = 1005
enum tokenID_e { IDENT_tk = 0, KW_tk = 1, OP_tk = 2, NUM_tk = 3, EOF_tk = 4 } typedef TokenID;

extern const char tokenNames[NUMBER_OF_TOKENS][MAX_TOKENNAME_LENGTH];

struct token_t { 
    TokenID tokenID; 
    char value[MAX_TOKENVALUE_LENGTH];
    int lineNumber; 
} typedef Token;

#endif // TOKEN_H
