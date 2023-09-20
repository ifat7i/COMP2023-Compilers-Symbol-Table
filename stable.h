#pragma once
#ifndef STABLE_H
#define STABLE_H
#include "stlist.h"
#define DEFAULT_SIZE 19
class STable
{
private:
    unsigned long indexHash = 0;
    unsigned long indexPreHash = 0;
    int newScopeInGlobal = 0;
    unsigned long Size;
    STList* Table;   // Dynamic Array of size = Size
       
    void init(int size);
    void changeHash();
    bool fold_case_flag;
public:
    STable();
    ~STable();
    STable(unsigned long size);
    void Reset(unsigned long size);
    STEntry* AddEntryToHashTable(char* name, STE_TYPE type);
    bool AddEntryToLinkedList(char* name, STE_TYPE type);
    void Add_New_STListToLinkedList();
    void Remove_STListFromLinkedList();
    void FindAndPrintEntry(char* name, FILE* fp);//finds and prints the Entry if it exist
    void PrintAll(FILE* fp);
    void Clear();
    void set_fold_case_flag(bool x) {
        this->fold_case_flag = x;
    }
    STList* Head; //  Linked List depends on every scope we enter
};

#endif // STABLE_H
