#include "lexer.h"

/*
* brief: these consts don't work in lexer.h, the compiler thinks there are two, here is fine
* I just want this to be done, please
*/
//list of operators
const char operators[] = {'<', '>', '(', ')', '+', '-', '*', '/', '|', '&', ';', ',', ':', '[', ']', '=', '!'}; //yes '.' is missing
const char* doubleOperators [] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=","=>" };
// accessor and array begin bool case character constant else elsif end exit function
// if in integer interface is loop module mutator natural null of or other out
// positive procedure range return struct subtype then type when while
const char* keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
                    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out", "positive",
                    "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};

/*
*@brief: this function checks to see if there is a double operator in the word
*/
bool containsDoubleOperator(char word[])
{
    int operatorSize = sizeof(doubleOperators)/sizeof(doubleOperators[0]); //total number of operators
    
    for(int i = 0; i < operatorSize; i++) //check through all operators
    {
        if(strstr(word, doubleOperators[i])) //also check through all operators
        {
            return true;
        }
    }

    return false;
}

/*
*@brief: this function parses the word and determines what it is it is a mess and I am dissapointed in my ability to code
*/
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
/*
* @brief: this function checks to see if the word is an operator
* @note: you may notice I am not check for '.' here, that is because I am tired and it breaks everything and reading through
*        everything has become a nightmare, I don't think I can fix it without breaking everything else
*/
bool isOperator(char word[])
{
    //total number of characters in word[]
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
/*
* @brief: this function checks to see if the word is a double operator
* @note: this looks similar to containsDoubleOperator, but unlike that function, this one checks to see if the word is a double operator
*        this is accatable to me
*/
bool isDoubleOperator(char word[])
{
    //total number of characters in word[]
    int operatorSize = sizeof(doubleOperators)/sizeof(doubleOperators[0]); //total number of operators
    
    for(int i = 0; i < operatorSize; i++)
    {
        if(strstr(word, doubleOperators[i])) //check through all operators
        {
            return true; //if it is a double operator, return true
        }
    }

    return false;
}

/*
* @brief: this function gets the index of the operator in the word
* @note: this is used to determine how much of the word is an operator and where to end it
*/
int getOperatorIndex(char word[])
{
    //total number of characters in word[]
    int size = strlen(word);
    size_t sizeOperators = sizeof(operators)/sizeof(operators[0]); //total number of operators
    size_t sizeDoubleOperators = sizeof(doubleOperators)/sizeof(doubleOperators[0]); //total number of double operators

    for(int j = 0; j < size; j++)
    {
        for(int i = 0; i < sizeOperators; i++) //check through all operators
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

/*
* @brief: self explanitory, checks to see if the word is a number
* there are some cases when operators fight with isNumber
*/
bool isNumber(char word[])
{
    int size = strlen(word);
    if(size == 0)
    {
        return false;
    }

    for(int i = 0; i < size; i++)
    {
        if(strstr(word, "..")) //this is a special case, it is a double operator, so we can have our decimal
        {
            return false;
        }
        
        bool a = isdigit(word[i]); //is it a digit
        // bool b = (word[i] == '.'); //is it a decimal
        bool c = (word[i] == '-'); //is it a negative sign

        if(!c) //if it is not a negative sign
        {
            // if(!b) //if it is not a decimal            
            // {
                if(!a) //if it is not a digit
                {
                    return false; //it is not a number
                }
            // }
        }
    }
    return true;
}

/*
* @brief: this function checks to see if the word is a keyword
* Hey I'm actually proud of this because it works as designed and I didn't have to change anything
* also these were out of order before I moved them
*/
bool isKeyword(char word[])
{
    size_t size = sizeof(keywords)/sizeof(keywords[0]); //total number of keywords

    for(int i = 0; i < size; i++)
    {
        if(strcmp(word, keywords[i]) == 0) //check through all keywords
        {
            return true;
        }
    }
    return false;
}

/*why did I make this so simple? Simple really, I don't how to specifically check for identifiers
*the only real rule for it is that it starts with a letter, can be anything else besides that as long as there is no space in it
*so I'm just going to check if it starts with a letter and if it does, then it's an identifier
*/
bool isIdentifier(char word[])
{
    //does it start with a letter upper or lowercase
    if(word[0] < 'A' || word[0] > 'z') //do you have a better idea for checks?
    {
        return false; //I don't
    }

    return true;
}
