
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errorOutput.h"


const int ERRORMESSAGE_SIZE = 200;
const int EXECNAME_SIZE = 200;

char *execName;
int isExecnameSet = 0;

void setExecName(char *str) {
    if (isExecnameSet) return;
    isExecnameSet = 1;

    execName = (char*)malloc(sizeof(char) * EXECNAME_SIZE);
    sprintf(execName, "%s", str);
}

void printError(char *msg) {
    perror(msg);
    if (1) return;

    if (isExecnameSet == 0) perror(msg);

    char buffer[EXECNAME_SIZE + ERRORMESSAGE_SIZE];
    memset(buffer, 0, EXECNAME_SIZE + ERRORMESSAGE_SIZE); /* important to reset buffer in between calls otherwise strcat will cause overflow */

    // attach execname to front of errormessage
    if (execName[0] != '.' && execName[1] != '/' && execName[0] != '/') strcat(buffer, "./");
    strcat(buffer, execName);
    strcat(buffer, ": ");

    strcat(buffer, msg);
    perror(buffer);
}

int getErrorMessageSize() {
    return ERRORMESSAGE_SIZE;
}

