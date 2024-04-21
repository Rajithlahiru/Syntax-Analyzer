#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum TokenType {
    NUMBER,
    PLUS,
    MINUS,
    END,
    ERROR
};

struct Token {
    enum TokenType type;
    int value; 
};

struct Token currentToken;
bool error = false;

void getNextToken() {
    int tokenType;
    if (scanf("<%d,%d>", &tokenType, &(currentToken.value)) == 2) {
        currentToken.type = (enum TokenType)tokenType;
    } else {
        currentToken.type = END;
    }
}

void match(enum TokenType expectedType) {
    if (currentToken.type == expectedType) {
        getNextToken();
    } else {
        printf("Syntax Error: Expected token type %d, but found %d\n", expectedType, currentToken.type);
        error = true;
    }
}

void expression();

void term() {
    if (currentToken.type == NUMBER) {
        match(NUMBER);
    } else {
        printf("Syntax Error: Expected NUMBER, but found %d\n", currentToken.type);
        error = true;
    }
}

void expression() {
    term();
    while (currentToken.type == PLUS || currentToken.type == MINUS) {
        match(currentToken.type);
        term();
    }
}

int main() {
    printf("Enter text to parse (Ctrl+D to end):\n");
    getNextToken(); 

    expression();

    if (!error && currentToken.type == END) {
        printf("Parsing successful\n");
    } else {
        printf("Parsing failed\n");
    }

    return 0;
}
