#include "hashing.h"

/*
This shouldn't really be in hashing.c, but
I'm not doing a lot of file io soooo...meh
Reads strings from a file into a char* array.
File should use new line deliminated values.
Returns a char** on success.
*/
char ** readFile(FILE *fileptr)
{
    int wordCount = 1;
    int index = 0;
    char buffer[BUFSIZE];
    char ** stringList = NULL;
    char ** tempPtr = NULL;

    while(fgets(buffer, BUFSIZE, fileptr))
    {
        tempPtr = (char **) realloc(stringList, sizeof(char*)*wordCount);
        stringList = tempPtr;        

        stringList[index] = (char *) malloc(sizeof(char) * strlen(buffer)+1);
        strcpy(stringList[index], buffer);
        wordCount++;
        index++;
    }

    tempPtr = (char **) realloc(stringList, sizeof(char*)*wordCount);
    stringList = tempPtr;
    stringList[index] = NULL;

    return stringList;
}

/*Adds ascii values of all characters
  In a string together, then performs
  a modulo operation on the sum.
  Value is the hash.
  Returns hash on success.
*/
int findHash (char * toBeHashed)
{
    int length = 0;
    int hash = 0;
    int asciiVal = 0;
    int i = 0;

    length = strlen(toBeHashed);

    for(i=0; i<length; i++)
    {
        asciiVal = toBeHashed[i];
        hash = hash + asciiVal; 
    }

    hash = hash % MODULO;
    return hash;
}

bucket * initLinkedList(int * size)
{
    int count = 0;
    bucket * root;
    bucket * newRecord;
    bucket * conductor;

    root = malloc(sizeof(bucket));
    conductor = root;
    while(count < *size)
    {
        newRecord = malloc(sizeof(bucket));
        newRecord->next = NULL;
        newRecord->value = NULL;
        newRecord->collission = NULL;
        conductor->next = newRecord;
        conductor = newRecord;
        count++;
    }

    return root;
}

int addHash(int hash, char * record, bucket * root)
{
    int status = 0;    //0 All good, 1 is a collission
    int count = 0;
    bucket * conductor;
    bucket * newRecord;
    bucket * upOne;

    conductor = root;
    
    /*Moves conductor to relevant record*/
    for(count=0; count < hash; count++)
    {
        conductor = conductor->next;
    }
    if (conductor->value == NULL)
    {
        conductor->value = malloc(strlen(record)+1);
        strcpy(conductor->value, record);
        status = 0;
    }
    else
    {
        while (conductor != NULL)
        {
            upOne = conductor;
            conductor = conductor->collission;
        }
        conductor = upOne;
        newRecord = malloc(sizeof(bucket));
        newRecord->value = malloc(strlen(record)+1);
        strcpy(newRecord->value, record);
        newRecord->collission = NULL;
        conductor->collission = newRecord;
        status = 1;
    }
    return status;
}

int queryDatabase(int hash, bucket * root, char * userInput)
{
    int status = 0;
    int counter;
    int found = 1;
    bucket * conductor;
    //bucket * upOne;

    conductor = root;

    for(counter=0; counter<hash; counter++)
    {
        conductor = conductor->next;
    }

    if(conductor->value == NULL)
    {
        printf("Record does not exist.\n");
        status = 1;
        found = 0;
    }
    else if (conductor->value != NULL)
    {
        if(strcmp(conductor->value, userInput) == 0)
        {
            printf("The record contains %s\n", conductor->value);
            status = 0;
            found = 0;
        }
        else
        {
            found = 1;
        }
    }
    if (found == 1);
    {
        while(conductor != NULL && found == 1)
        {
            //upOne = conductor;
            conductor = conductor->collission;
            if (conductor != NULL)
            {
                if(strcmp(conductor->value, userInput)==0)
                {
                    printf("The record contains %s\n", conductor->value);
                    printf("There were collissions\n");
                    found = 0;
                }
            }
        }
        if (found == 1)
        {
            printf("Record does not exist.\n");
            printf("There were collissions.\n");
        }
    }

    return status;
}
