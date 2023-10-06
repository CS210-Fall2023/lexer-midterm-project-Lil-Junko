#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//list of operators
const char operators[] = {'<', '>', '(', ')', '+', '-', '*', '/', '|', '&', ';', ',', ':', '[', ']', '=', '!'};
const char* double_operators [] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=","=>" };
// accessor and array begin bool case character constant else elsif end exit function
// if in integer interface is loop module mutator natural null of or other out
// positive procedure range return struct subtype then type when while
const char* keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
                    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out", "positive",
                    "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};

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
