/*
*@file main.c
*@brief This is the main file for the lexer
*@details This file will take in a file and parse it into a new file with the .lexer extension
*@date 2021-10-13
*@name Nolan Meyer
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"


int main()
{
    int back;
    char c;
    char file_name[100];
    printf("please write the input file: ");
    scanf("%s", file_name);
    // Open one file for reading
    fptr1 = fopen(file_name, "r");         //IMPORTANT CHANGE LATER
    if (fptr1 == NULL)
    {
        printf("Cannot open file\n");
        exit(0);
    }
    // add ".lexer" to end of the file_name
    strcat(file_name, ".lexer");
    printf("%s", file_name);
    // Open another file for writing
    fptr2 = fopen(file_name, "w");
    
    //get data
    char data[100] = {'\0'};
    fscanf(fptr1, "%s", data);
    
    do 
    {
        c = fgetc(fptr1);
        int len = strlen(data); //length being set wrong, getting length 5 for word=a
        char* word = (char*)malloc(len + 1);

        for(int i = 0; i < len; i++)
        {
            word[i] = data[i];
        }

        if(strlen(word) != 0) // Ignore empty lines
        {    
            if (isNumber(word)) //Numbers
            {
                fprintf(fptr2, "%s (numeric literal)\n", word);
            }
            else if(data[0] == '"') //Strings
            {
                back = (strlen(data));
                //move back to the beggining of the word
                fseek(fptr1, -back, SEEK_CUR);
                //print the first "
                c = '"'; //force the first " to print
                fprintf(fptr2, "%c", c);
                c = fgetc(fptr1);
                fprintf(fptr2, "%c", c);
                //if it is, then print the data until the next "
                while(c != '"')
                {
                    c = fgetc(fptr1);
                    fprintf(fptr2, "%c", c);            
                }
                //print the last "
                fprintf(fptr2, " (string)\n");
                fscanf(fptr1, "%s", data); // get the next word
            }
            else if(data[0] == '/' || data[1] == '*') //Comments
            {
                // comment check
                fprintf(fptr2, "%s", data);
                fprintf(fptr2, "%c", c);
                //if it is a comment, then print the word until the next */
                for(bool end = false; end == false;)
                {
                    c = fgetc(fptr1);
                    fprintf(fptr2, "%c", c);
                    if(c == '*')
                    {
                        c = fgetc(fptr1);
                        if(c == '/')
                        {
                            end = true;
                        }
                    }
                }
                fprintf(fptr2, "%c", c);
                fprintf(fptr2, " (comment)\n");
            }
            else //everything else
            {
                int operatorIndex = getOperatorIndex(word);

                if (operatorIndex == 0)
                {
                    parseWord(word);
                }
                else
                {
                    int size = strlen(word);
                    while ((size > 0))
                    {       
                        if (operatorIndex == 0)
                        {
                            parseWord(word);
                            size = 0;
                        }             
                        else
                        {
                            if(operatorIndex > 1)
                            {
                                operatorIndex = operatorIndex - 1;
                            }

                            char* tempWord = (char*)malloc(operatorIndex + 1);
                            
                            // single operator 
                            if((operatorIndex == 2) && (size == 1))
                            {
                                tempWord[0] = word[0];
                                operatorIndex   = 1;
                            } // double operator
                            else if((operatorIndex == 1) && (size == 3) && (containsDoubleOperator(word)))
                            {
                                tempWord[0] = word[0];
                                tempWord[1] = word[1];
                                operatorIndex = 2;
                            } // double operator
                            else if((operatorIndex == 1) && (size == 2) && (containsDoubleOperator(word)))
                            {
                                tempWord[0] = word[0];
                                tempWord[1] = word[1];
                                operatorIndex = 2;
                            }
                            else // everything else
                            {
                                for(int i = 0; i < operatorIndex; i++)
                                {
                                    tempWord[i] = word[i];
                                }
                            }

                            parseWord(tempWord);

                            //remove the word from the string and run the loop again
                            size_t temp = strlen(word);
                            char tempWord2[temp - operatorIndex]; 
                            int j = 0;
                            for(int i = operatorIndex; i < temp; i++)
                            {
                                tempWord2[j] = word[i];
                                j++;
                            }
                            
                            for(int i = 0; i < sizeof(word); i++)
                            {
                                word[i]='\0';
                            }

                            memcpy(word, tempWord2, temp - operatorIndex);
                            operatorIndex = getOperatorIndex(word);
                            size = strlen(word);
                        } 
                    }
                } 
            }
        }

        for(int i = 0; i < sizeof(data); i++)
        {
            data[i]='\0';
        }

        printf("%s\n", data);
        fscanf(fptr1, "%s", data);
           
    }while ((c != EOF));
  
    fclose(fptr1);
    fclose(fptr2);

    return 0;
}

//gcc -o main main.c

bool containsDoubleOperator(char word[])
{
    int size = strlen(word);
    int operatorSize = sizeof(double_operators)/sizeof(double_operators[0]);
    
    for(int i = 0; i < operatorSize; i++)
    {
        if(strstr(word, double_operators[i]))
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
    int size = strlen(word);
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
    int size = strlen(word);
    int operatorSize = sizeof(double_operators)/sizeof(double_operators[0]);
    
    for(int i = 0; i < operatorSize; i++)
    {
        if(strstr(word, double_operators[i]))
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
    size_t sizeDoubleOperators = sizeof(double_operators)/sizeof(double_operators[0]);

    for(int j = 0; j < size; j++)
    {
        for(int i = 0; i < sizeOperators; i++)
        {
            char temp[2];
            temp[0] = word[j];
            temp[1] = word[j + 1];
            for(int k = 0; k < sizeDoubleOperators; k++)
            {
                if(strcmp(temp, double_operators[k]) == 0)
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