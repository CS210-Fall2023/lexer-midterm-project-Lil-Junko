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
    fptr1 = fopen(file_name, "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file\n");
        exit(0);
    }
    // add ".lexer" to end of the file_name
    strcat(file_name, ".lexer");
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

        fscanf(fptr1, "%s", data);
           
    }while ((c != EOF));
  
    fclose(fptr1);
    fclose(fptr2);

    return 0;
}