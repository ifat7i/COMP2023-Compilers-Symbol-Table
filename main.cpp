#include<iostream>
#include"FileDescriptor.h"
#include "Scanner.h"
#include <cctype>
#include "stentry.h"
#include "stable.h"
#include "lexemes.h"
#include <stdlib.h>
using namespace std;

bool isDataType(LEXEME_TYPE type)
{
    bool flag = false;
    switch (type)
    {
    case KW_VAR:
        flag = true;
        break;
    case KW_CONSTANT:
        flag = true;
        break;
    case KW_INTEGER:
        flag = true;
        break;
    case KW_BOOLEAN:
        flag = true;
        break;
    case KW_STRING:
        flag = true;
        break;
    case KW_FLOAT:
        flag = true;
        break;
    case KW_DOUBLE:
        flag = true;
        break;
    case KW_CHAR:
        flag = true;
        break;
    case KW_FUNCTION:
        flag = true;
        break;
    case KW_PROCEDURE:
        flag = true;
        break;
    default:
        flag = false;
        break;
    }
    return flag;
}


STE_TYPE getType(LEXEME_TYPE lexT)
{
    STE_TYPE type = STE_NONE;
    switch (lexT)
    {
    case KW_VAR:
        type = STE_VAR;
        break;
    case KW_CONSTANT:
        type = STE_CONST;
        break;
    case KW_INTEGER:
        type = STE_INT;
        break;
    case KW_BOOLEAN:
        type = STE_BOOL;
        break;
    case KW_STRING:
        type = STE_STRING;
        break;
    case KW_FLOAT:
        type = STE_FLOAT;
        break;
    case KW_DOUBLE:
        type = STE_DOUBLE;
        break;
    case KW_CHAR:
        type = STE_CHAR;
        break;
    case KW_FUNCTION:
        type = STE_FUNC;
        break;
    case KW_PROCEDURE:
        type = STE_PROC;
        break;
    default:
        type = STE_NONE;
        break;
    }
    return type;
}

char* getName(LEXEME_TYPE lexT)
{
    std::string str = "";
    switch (lexT)
    {
    case KW_VAR:
        str = "var";
        break;
    case KW_CONSTANT:
        str = "constant";
        break;
    case KW_INTEGER:
        str = "integer";
        break;
    case KW_BOOLEAN:
        str = "bool";
        break;
    case KW_STRING:
        str = "char*";
        break;
    case KW_FLOAT:
        str = "float";
        break;
    case KW_DOUBLE:
        str = "double";
        break;
    case KW_CHAR:
        str = "char";
        break;
    default:
        str = "None";
        break;
    }
    char* charArray = new char[str.length() + 1];
    strcpy(charArray, str.c_str());
    return charArray;
}


int main() {
    string str = "";
    cout << "ENTER FILE NAME: ";
    cin >> str;
    char* fileName = new char[str.length() + 1];
    strcpy(fileName, str.c_str());
    FileDescriptor* Fd = new FileDescriptor(fileName);


    TOKEN* returnedToken;
    Scanner* scanner = new Scanner(Fd);

    FILE* fp = nullptr;
    STable  ST;
    ST.set_fold_case_flag(false);
    STE_TYPE type = STE_NONE;
    char* name;
    FILE* fout = fopen("out.txt", "w");   //set fout = stdout for screen output
    fprintf(fout, "\n**(Test 1)**: Reading from the file t.txt and creating a symbol table with size = 19(default)\n\n");
    int n;
    bool Added;
    while (1) {
        returnedToken = scanner->Scan();

        if (returnedToken->type == LX_ERROR) {
            continue;
        }

        if (returnedToken->type == LX_WHITE_SPACE) continue;

        if (returnedToken->type == LX_EOF) break;




        //IF WE WANT TO SHOW ERROR IF THE DATATYPE IS NOT FOLLOWED BY ID
        
        if (isDataType(returnedToken->type)) {
            std::cout << " ###" << returnedToken->str_ptr;
            type = getType(returnedToken->type);
            std::cout << " ###ty" << type;

            while ((returnedToken = scanner->Scan())->type == LX_WHITE_SPACE);
            std::cout << " ###" << returnedToken->type;
            if (returnedToken->type == LX_IDENTIFIER) {
                Added = ST.AddEntryToLinkedList(returnedToken->str_ptr, type);
                if (!Added) {
                    fprintf(fout, "Error: redeclaration of '%s' | Line: %d\n", returnedToken->str_ptr, Fd->getLineNum());
                }
                else {
                    ST.AddEntryToHashTable(returnedToken->str_ptr, type);
                }
            }
            else {
                Fd->reportError(scanner->getErrorMsg(BAD_VARIABLE_DECLARING));

            }
            continue;
        }

        
        if (returnedToken->type == LX_IDENTIFIER) {
            ST.FindAndPrintEntry(returnedToken->str_ptr, fout);
            std::cout << "\n ID: " << returnedToken->str_ptr;
        }

        if (returnedToken->type == LX_LCBRACKET) {
            ST.Add_New_STListToLinkedList();
        }

        if (returnedToken->type == LX_RCBRACKET) {
            ST.Remove_STListFromLinkedList();
        }

    }


    fprintf(fout, "\n==============\n");
    ST.PrintAll(fout);
    fprintf(fout, "\n==============\n");
    return 0;
}