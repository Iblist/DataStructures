//Practice safe includes, use an include guard
#ifndef HASHING_H
#define HASHING_H

#define BUFSIZE 255
#define MODULO 37

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bucket
{
    char * value;
    struct bucket * next;
    struct bucket * collission;
}bucket;

char ** readFile(FILE* fileptr);
int findHash (char * toBeHashed);
int addHash(int hash, char * record, bucket * root);
int queryDatabase(int hash, bucket * root, char * userInput);
bucket * initLinkedList(int * size);

#endif //HASHING_H
