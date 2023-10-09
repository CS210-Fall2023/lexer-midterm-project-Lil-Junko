#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


// Prototypes
int getOperatorIndex(char word[]);
bool isNumber(char word[]);
bool isIdentifier(char word[]);
bool isKeyword(char word[]);
void parseWord(char word[]);
bool isOperator(char word[]);
bool isDoubleOperator(char word[]);
bool containsDoubleOperator(char word[]);

FILE *fptr1, *fptr2; //bad practice but whatever, less issues with passing in files

#endif // LEXER_H
