#include "lexer.h"

//list of operators
const char operators[] = {'<', '>', '(', ')', '+', '-', '*', '/', '|', '&', ';', ',', ':', '[', ']', '=', '!'};
const char* doubleOperators [] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=","=>" };
// accessor and array begin bool case character constant else elsif end exit function
// if in integer interface is loop module mutator natural null of or other out
// positive procedure range return struct subtype then type when while
const char* keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
                    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out", "positive",
                    "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};

bool containsDoubleOperator(char word[])
{
    //int size = strlen(word);
    int operatorSize = sizeof(doubleOperators)/sizeof(doubleOperators[0]);
    
    for(int i = 0; i < operatorSize; i++)
    {
        if(strstr(word, doubleOperators[i]))
        {
            return true;
        }
    }

    return false;
}

void parseWord(char word[])
{
    if (isNumber(word)) //Numbers
    {
        fprintf(fptr2, "%s (numeric literal)\n", word);
    }
    else if (isDoubleOperator(word)) //Operators
    {
        fprintf(fptr2, "%s (opperator)\n", word);
    }
    else if (isOperator(word)) //Operators
    {
        fprintf(fptr2, "%s (opperator)\n", word);
    }
    else if (isKeyword(word)) //Keywords
    {
        //write to the file
        fprintf(fptr2, "%s (keyword)\n", word);
    }
    else if (isIdentifier(word)) //Identifiers
    {
        //write to the file
        fprintf(fptr2, "%s (identifier)\n", word);
    }
    else //UNK
    {
        fprintf(fptr2, "%s (UNK)\n", word);
    }
}

bool isOperator(char word[])
{
    //total number of characters in word[]
    //int size = strlen(word);
    int operatorSize = sizeof(operators)/sizeof(operators[0]);
    
    for(int j = 0; j < operatorSize; j++)
    {
        for(int i = 0; i < 17; i++)
        {
            if(word[j] == operators[i])
            {
                return true;
            }
        }
    }

    return false;
}

bool isDoubleOperator(char word[])
{
    //total number of characters in word[]
    //int size = strlen(word);
    int operatorSize = sizeof(doubleOperators)/sizeof(doubleOperators[0]);
    
    for(int i = 0; i < operatorSize; i++)
    {
        if(strstr(word, doubleOperators[i]))
        {
            return true;
        }
    }

    return false;
}

int getOperatorIndex(char word[])
{
    //total number of characters in word[]
    int size = strlen(word);
    size_t sizeOperators = sizeof(operators)/sizeof(operators[0]);;
    size_t sizeDoubleOperators = sizeof(doubleOperators)/sizeof(doubleOperators[0]);

    for(int j = 0; j < size; j++)
    {
        for(int i = 0; i < sizeOperators; i++)
        {
            char temp[2];
            temp[0] = word[j];
            temp[1] = word[j + 1];
            for(int k = 0; k < sizeDoubleOperators; k++)
            {
                if(strcmp(temp, doubleOperators[k]) == 0)
                {
                    return j + 2;
                }
            }

            if(word[j] == operators[i])
            {
                return j + 1;
            }
        }
    }

    return 0;
}

bool isNumber(char word[])
{
    int size = strlen(word);
    if(size == 0)
    {
        return false;
    }

    for(int i = 0; i < size; i++)
    {
        if(strstr(word, ".."))
        {
            return false;
        }
        
        bool a = isdigit(word[i]);
        bool b = (word[i] == '.');
        bool c = (word[i] == '-');

        if(!c)
        {
            if(!b)
            {
                if(!a)
                {
                    return false;
                }
            }
        }
    }
    
    return true;
}

//why did I make this so simple? Simple really, I don't how to specifically check for identifiers
//the only real rule for it is that it starts with a letter, can be anything else besides that as long as there is no space in it
//so I'm just going to check if it starts with a letter and if it does, then it's an identifier
bool isIdentifier(char word[])
{
    //does it start with a letter upper or lowercase
    if(word[0] < 'A' || word[0] > 'z') //do you have a better idea for checks?
    {
        return false;
    }

    return true;
}

bool isKeyword(char word[])
{
    size_t size = sizeof(keywords)/sizeof(keywords[0]);;

    for(int i = 0; i < size; i++)
    {
        if(strcmp(word, keywords[i]) == 0)
        {
            return true;
        }
    }
    return false;
}