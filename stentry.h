#pragma once
#ifndef STENTRY_H
#define STENTRY_H
#include <stdio.h>
#include <string.h>
#define TYPE_SIZE 11

typedef enum
{
    STE_NONE, //0
    STE_VAR,
    STE_CONST,
    STE_INT,
    STE_BOOL,
    STE_STRING,
    STE_FLOAT,
    STE_DOUBLE,
    STE_CHAR,
    STE_FUNC,
    STE_PROC
}STE_TYPE;


const static char* STE_TYPE_STR[TYPE_SIZE] = { "None", "var", "constant",  "integer", "boolean", "string","float", "double", "char" , "function" , "procedure" };// It is not a good idea to put this here
static char  str[128];

class STEntry
{
public:

    char Name[64];
    STE_TYPE Type;  //it is an int
    STEntry* Next;
    STEntry() {
        Next = NULL;
        Type = STE_NONE;
        Name[0] = 0; //empty String
    }
    STEntry(char* name, STE_TYPE type)
    {
        printf("THIS IS IS IS %d => %s\n", type, name);
        Next = NULL;
        Type = type;
        strcpy(Name, name);
    }
    char* toString()
    {
        if ((Type < STE_NONE) || Type > STE_PROC)  Type = STE_NONE;
        sprintf(str, "(%s,%s)", Name, STE_TYPE_STR[Type]);
        return str;
    }
    void print(FILE* fp)
    {
        fprintf(fp, "%s ", toString());
    }
    void print()
    {
        printf("%s", toString());
    }


};

#endif // STENTRY_H
