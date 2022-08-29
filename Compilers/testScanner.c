
#include <stdlib.h>
#include "testScanner.h"
#include "scanner.h"

void testScanner() {
    Token *token;

    initScanner();

    do {
        token = scanner();
        fprintf(stderr, "%s %s %d\n", tokenNames[token->tokenID], token->value, token->lineNumber);
    } while (token->tokenID != EOF_tk);

    free(token);
}


