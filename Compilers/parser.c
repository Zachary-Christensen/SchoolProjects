#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "token.h"
#include "errorOutput.h"
#include "scanner.h"
#include "node.h"

Token *tk;
const int MESSSAGE_LEN = 256;
char errorMessage[256];

void error(char *msg) {
    sprintf(errorMessage, "Parser error: %s. line number: %d. Token was type '%s' with value '%s'", msg, tk->lineNumber, tokenNames[(int)tk->tokenID], tk->value);
    printError(errorMessage);
    exit(EXIT_FAILURE);
}

Node *parser() {
    tk = scanner();

    Node *root = S();

    if (tk->tokenID != EOF_tk) { // error
        error("Final token from parser was not EOF");
    }
    else {
        // fprintf(stderr, "Hooray! No errors\n");
    }
    
    return root;
}

Node *S() {
    Node *node = genNode('S');
    node->orderOfTokensAndChildren = (1 << 6) | (1 << 1) | 1;
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Name") == 0) {
        node->token1 = tk;
        tk = scanner();
    }
    else {
        error("<S> must start with 'Name'");
    }

    if (tk->tokenID == IDENT_tk) {
        node->token2 = tk;
        tk = scanner(); 
    }
    else {
        error("In <S>, expected Identity");
    }

    if (tk->tokenID == KW_tk && strcmp(tk->value, "Spot") == 0) {
        node->token3 = tk;
        tk = scanner();
    }
    else {
        error("In <S>, expected keyword Spot");
    }

    if (tk->tokenID == IDENT_tk) {
        node->token4 = tk;
        tk = scanner();
        node->child1 = R();
        node->child2 = E();
    }
    else {
        error("In <S>, expected Identity");
    }

    return node;
}

Node *R() {
    Node *node = genNode('R');
    node->orderOfTokensAndChildren = (1 << 4) | (1 << 2) | (1 << 1);
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Place") == 0) {
        node->token1 = tk;
        tk = scanner();
        node->child1 = A();
        node->child2 = B();
    }
    else {
        error("In <R>, expected keyword 'Place'");
    }

    if (tk->tokenID == KW_tk && strcmp(tk->value, "Home") == 0) {
        node->token2 = tk;
        tk = scanner();
    }
    else {
        error("In <R>, expected keyword 'Home'");
    }

    return node;
}

Node *E() {
    Node *node = genNode('E');
    node->orderOfTokensAndChildren = (1 << 2);
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Show") == 0) {
        node->token1= tk;
        tk = scanner();
    }
    else {
        error("In <E>, expected keyword 'Show'");
    }
    
    if (tk->tokenID == IDENT_tk) {
        node->token2 = tk;
        tk = scanner();
    }
    else {
        error("In <E>, expected Identity");
    }

    return node;
}

Node *A() {
    Node *node = genNode('A');
    node->orderOfTokensAndChildren = (1 << 2);
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Name") == 0) {
        node->token1 = tk;
        tk = scanner();
    }
    else {
        error("In <A>, expected keyword 'Name'");
    }
    
    if (tk->tokenID == IDENT_tk) {
        node->token2 = tk;
        tk = scanner();
    }
    else {
        error("In <A>, expected Identity");
    }

    return node;
}

Node *B() {
    Node *node = genNode('B');
    if (tk->tokenID == OP_tk && strcmp(tk->value, ".") == 0) {
        node->orderOfTokensAndChildren = (1 << 4) | (1 << 2) | 1;

        node->token1 = tk;
        tk = scanner();
        node->child1 = C();
        if (tk->tokenID == OP_tk && strcmp(tk->value, ".") == 0) {
            node->token2 = tk;
            tk = scanner();
            node->child2 = B();
        }
        else {
            error("In <B>, expected .");
        }
    }
    else if ((tk->tokenID == OP_tk && strcmp(tk->value, "/") == 0) || (tk->tokenID == KW_tk && strcmp(tk->value, "Assign") == 0) || (tk->tokenID == KW_tk && strcmp(tk->value, "Spot") == 0) || (tk->tokenID == KW_tk && strcmp(tk->value, "Move") == 0) || (tk->tokenID == KW_tk && strcmp(tk->value, "Flip") == 0) || (tk->tokenID == KW_tk && strcmp(tk->value, "Show") == 0) || (tk->tokenID == OP_tk && strcmp(tk->value, "{") == 0)) {
        node->orderOfTokensAndChildren = (1 << 2) | (1 << 1) | 1;
        node->child1 = D();
        node->child2 = B();
    }
    else { // empty string
        node->orderOfTokensAndChildren = 0;
        return node;
    }
    return node;
}

Node *C() {
    Node *node = genNode('C');
    node->orderOfTokensAndChildren = (1 << 1) | 1;
    if (tk->tokenID == OP_tk && strcmp(tk->value, "{") == 0) {
        node->child1 = F();
    }
    else if (tk->tokenID == KW_tk && strcmp(tk->value, "Here") == 0) {
        node->child1 = G();
    }
    else {
        error("In <C>, expected first set from <F> or <G>");
    }

    return node;
}

Node *D() {
    Node *node = genNode('D');
    node->orderOfTokensAndChildren = (1 << 1) | 1;
    if (tk->tokenID == OP_tk && strcmp(tk->value, "/") == 0) {
        node->child1 = H();
    }
    else if (tk->tokenID == KW_tk && strcmp(tk->value, "Assign") == 0) {
        node->child1 = J();
    }
    else if (tk->tokenID == KW_tk && (strcmp(tk->value, "Spot") == 0 || strcmp(tk->value, "Move") == 0)) {
        node->child1 = K();
    }
    else if (tk->tokenID == KW_tk && strcmp(tk->value, "Flip") == 0) {
        node->child1 = L();
    }
    else if (tk->tokenID == KW_tk && strcmp(tk->value, "Show") == 0) {
        node->child1 = E();
    }
    else if (tk->tokenID == OP_tk && strcmp(tk->value, "{") == 0) {
        node->child1 = F();
    }
    else {
        error("In <D>, expected first set from <H>, <J>, <K>, <L>, <E>, or <F>");
    }

    return node;
}

Node *F() {
    Node *node = genNode('F');
    node->orderOfTokensAndChildren = (1 << 7) | (1 << 3) | (1 << 2) | (1 << 1);
    if (tk->tokenID == OP_tk && strcmp(tk->value, "{") == 0) {
        node->token1 = tk;
        tk = scanner();
        if (tk->tokenID == KW_tk && strcmp(tk->value, "If") == 0) {
            node->token2 = tk;
            tk = scanner();
            if (tk->tokenID == IDENT_tk) {
                node->token3 = tk;
                tk = scanner();
                node->child1 = T();
                node->child2 = W();
                node->child3 = D();
                if (tk->tokenID == OP_tk && strcmp(tk->value, "}") == 0) {
                    node->token4 = tk;
                    tk = scanner();
                }
                else {
                    error("In <F>, expected }");
                }
            }
            else {
                error("In <F>, expected Identifier");
            }
        }
        else if (tk->tokenID == KW_tk && strcmp(tk->value, "Do") == 0) {
            node->token2 = tk;
            tk = scanner();
            if (tk->tokenID == KW_tk && strcmp(tk->value, "Again") == 0) {
                node->token3 = tk;
                tk = scanner();
                node->child1 = D();
                node->child2 = T();
                node->child3 = W();
                if (tk->tokenID == OP_tk && strcmp(tk->value, "}") == 0) {
                    node->token4 = tk;
                    tk = scanner();
                }
                else {
                    error("In <F>, expected }");
                }
            }
            else {
                error("In <F>, expected keyword Again");
            }
        }
        else {
            error("In <F>, expected either keyword If or Do");
        }
    }
    else {
        error("In <F>, expected {");
    }

    return node;
}

Node *G() {
    Node *node = genNode('G');
    node->orderOfTokensAndChildren = (1 << 3);
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Here") == 0) {
        node->token1 = tk;
        tk = scanner();
        if (tk->tokenID == NUM_tk) {
            node->token2 = tk;
            tk = scanner();
            if (tk->tokenID == KW_tk && strcmp(tk->value, "There") == 0) {
                node->token3 = tk;
                tk = scanner();
            }
            else {
                error("In <G>, expected keyword 'There'");
            }
        }
        else {
            error("In <G>, expected Number");
        }
    }
    else {
        error("In <G>, expected keyword 'Here'");
    }

    return node;
}

Node *T() {
    Node *node = genNode('T');
    node->orderOfTokensAndChildren = (1 << 1);
    if (tk->tokenID == OP_tk && strcmp(tk->value, "<<") == 0) {
        node->token1 = tk;
        tk = scanner();
    }
    else if (tk->tokenID == OP_tk && strcmp(tk->value, "<-") == 0) {
        node->token1 = tk;
        tk = scanner();
    }
    else {
        error("In <T>, expected operator << or <-");
    }
    
    return node;
}

Node *V() {
    Node *node = genNode('V');
    node->orderOfTokensAndChildren = (1 << 1);
    if (tk->tokenID == OP_tk && strcmp(tk->value, "+") == 0) {
        node->token1 = tk;
        tk = scanner();
    }
    else if (tk->tokenID == OP_tk && strcmp(tk->value, "%") == 0) {
        node->token1 = tk;
        tk = scanner();
    }
    else if (tk->tokenID == OP_tk && strcmp(tk->value, "&") == 0) {
        node->token1 = tk;
        tk = scanner();
    }
    else {
        error("In <V>, expected one of operators + % or &");
    }

    return node;
}

Node *H() {
    Node *node = genNode('H');
    node->orderOfTokensAndChildren = (1 << 2) | 1;
    if (tk->tokenID == OP_tk && strcmp(tk->value, "/") == 0) {
        node->token1 = tk;
        tk = scanner();
        node->child1 = Z();
    }
    else {
        error("In <H>, expected /");
    }

    return node;
}

Node *J() {
    Node *node = genNode('J');
    node->orderOfTokensAndChildren = (1 << 3) | 1;
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Assign") == 0) {
        node->token1 = tk;
        tk = scanner();
        if (tk->tokenID == IDENT_tk) {
            node->token2 = tk;
            tk = scanner();
            node->child1 = D();
        }
    }
    else {
        error("In <J>, expected keyword 'Assign'");
    }

    return node;
}

Node *K() {
    Node *node = genNode('K');
    node->orderOfTokensAndChildren = (1 << 4);
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Spot") == 0) {
        node->token1 = tk;
        tk = scanner();
        if (tk->tokenID == NUM_tk) {
            node->token2 = tk;
            tk = scanner();
            if (tk->tokenID == KW_tk && strcmp(tk->value, "Show") == 0) {
                node->token3 = tk;
                tk = scanner();
                if (tk->tokenID == NUM_tk) {
                    node->token4 = tk;
                    tk = scanner();
                }
                else {
                    error("In <K>, expected Number");
                }
            }
            else {
                error("In <K>, expected keyword 'Show'");
            }
        }
        else {
            error("In <K>, expected Number");
        }
    }
    else if (tk->tokenID == KW_tk && strcmp(tk->value, "Move") == 0) {
        node->token1 = tk;
        tk = scanner();
        if (tk->tokenID == IDENT_tk) {
            node->token2 = tk;
            tk = scanner();
            if (tk->tokenID == KW_tk && strcmp(tk->value, "Show") == 0) {
                node->token3 = tk;
                tk = scanner();
                if (tk->tokenID == IDENT_tk) {
                    node->token4 = tk;
                    tk = scanner();
                }
                else {
                    error("In <K>, expected Identifier");
                }
            }
            else {
                error("In <K>, expected keyword 'Show'");
            }
        }
        else {
            error("In <K>, expected Identifier");
        }
    }
    else {
        error("In <K>, expected either keyword 'Spot' or 'Move'");
    }
    return node;
}

Node *L() {
    Node *node = genNode('L');
    node->orderOfTokensAndChildren = (1 << 2);
    if (tk->tokenID == KW_tk && strcmp(tk->value, "Flip") == 0) {
        node->token1 = tk;
        tk = scanner();
        if (tk->tokenID == IDENT_tk) {
            node->token2 = tk;
            tk = scanner();
        }
        else {
            error("In <L>, expected Identifier");
        }
    }
    else {
        error("In <L>, expected keyword 'Flip'");
    }
    return node;
}

Node *W() {
    Node *node = genNode('W');
    if (tk->tokenID == NUM_tk) {
        node->token1 = tk;
        tk = scanner();
        if (tk->tokenID == OP_tk && (strcmp(tk->value, "+") == 0 || strcmp(tk->value, "%") == 0 || strcmp(tk->value, "&") == 0)) {
            node->orderOfTokensAndChildren = (1 << 3) | (1 << 1);
            node->child1 = V();
            if (tk->tokenID == NUM_tk) {
                node->token2 = tk;
                tk = scanner();
            }
            else {
                error("In <W>, expected Number");
            }
        }
        else if (tk->tokenID == OP_tk && strcmp(tk->value, ".") == 0) {
            node->orderOfTokensAndChildren = (1 << 2);
            node->token2= tk;
            tk = scanner();
        }
        else {
            error("In <W>, expected . or first set from <V>");
        }
    }
    else {
        error("In <W>, expected Number");
    }
    return node;
}

Node *Z() {
    Node *node = genNode('Z');
    node->orderOfTokensAndChildren = (1 << 1);
    if (tk->tokenID == IDENT_tk) {
        node->token1 = tk;
        tk = scanner();
    }
    else if (tk->tokenID == NUM_tk) {
        node->token1 = tk;
        tk = scanner();
    }
    else {
        error("In <Z>, expected Identifier or Number");
    }
    
    return node;
}

