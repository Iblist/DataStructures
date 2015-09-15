/*Preamble;
  This program should, in theory, take a file name as an argument,
  grab everything from the file and shove it through a hashing
  function.  Once everything is sorted into buckets, the user
  will be able to query the database for entries.  The program
  will hash the value given, and check the database for a matching
  hash.  The database will then check if the value is correct before
  returning it to the user.  If the value is incorrect, fuck.
*/

#include "main.h"

int main(int argc, char * argv[])
{
    int counter1 = 0;
    int hashValue;
    int sizeOfList = 102;
    int * sizePtr = &sizeOfList;
    bucket * root;
    //bucket * conductor;
    char ** wordList;
    char * toBeHashed;
    char userInput[BUFSIZE];

    FILE* inputFile;
    
    if (argc != 2)
    {
        printf("Please input a file name and nothing else.\n");
        exit(0);
    }

    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("The file '%s' does not exist.  Quiting.\n", argv[1]);
        exit(0);
    }

    wordList = readFile(inputFile);
    fclose(inputFile);

    root = initLinkedList(sizePtr);    

    if(root == NULL)
    {
        printf("Error creating linked list, quiting...\n");
        exit(0);
    }

    while (wordList[counter1] != NULL)
    {
        hashValue = findHash(wordList[counter1]);
        addHash(hashValue, wordList[counter1], root);
        counter1++;
    }
    free(wordList);

    printf("List successfully hashed! Ready for queries: ");
    while (1==1)
    {
        fgets(userInput, BUFSIZE, stdin);
        toBeHashed = malloc(strlen(userInput)+1);
        strcpy(toBeHashed, userInput);
        hashValue = findHash(toBeHashed);

        queryDatabase(hashValue, root, toBeHashed);
        printf("Ready for queries: ");
    }

    return 0;
}
