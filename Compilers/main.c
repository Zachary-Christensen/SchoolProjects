
#include <stdlib.h>
#include "scanner.h"
#include "errorOutput.h"
#include "testScanner.h"
#include "token.h"
#include "parser.h"
#include "node.h"
#include "printTree.h"
#include "semantics.h"

FILE *scannerFile; // scanner.h
const char tokenNames[NUMBER_OF_TOKENS][MAX_TOKENNAME_LENGTH]  = { "Identifier", "Keyword", "Operator", "Number", "End of File" }; // token.h

int main(int argc, char **argv) {

    // process arguments
    if (argc == 1) {
        scannerFile = stdin;
    }
    else if (argc == 2) {
        if ((scannerFile = fopen(argv[1], "r")) == NULL) {
            char errorMessage[getErrorMessageSize()];
            sprintf(errorMessage, "Unable to open file %s", argv[1]);
            printError(errorMessage);
            exit(EXIT_FAILURE);
        }
    }
    else {
        printError("Incorrect usage. Example usage ./genCode [filename]");
        exit(EXIT_FAILURE);
    }

    initScanner();

    Node *root = parser();
    // printParseTree(root, 0);
    Symbol *rootSymbol = semantics(root);
    // printSymbolTable();

    setupTranslate("code.asm");
    translate(root);
    endTranslate();
    
    fprintf(stderr, "Assembly code outputted to code.asm\n");

    // FILE* asmFile;
    // if ((asmFile = fopen("file.asm", "r")) != NULL) {
    //     fprintf(stderr, "Assembly file:\n");
    //     char ch;
    //     while((ch = fgetc(asmFile)) != EOF) {
    //         fprintf(stderr, "%c", ch);
    //     }
    // }

    return 0;
}



