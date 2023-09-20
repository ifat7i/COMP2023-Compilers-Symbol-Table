#include "stable.h"
#include <iostream>

void STable::init(int size)
{
    Size = size;
    Table = new STList[size];
    Head = new STList();

}


STable::STable()
{
    init(DEFAULT_SIZE);
}



STable::STable(unsigned long size)
{
    init(size);
}


void STable::Reset(unsigned long size)
{
    Clear();
    init(size);
}





void STable::changeHash()
{
    indexPreHash = indexHash;
    while (true) {
        indexHash = rand() % Size;
        if (Table[indexHash].getHead() == NULL) break;
    }
}
/**
 * @brief STable::AddEntry : Adds the Entry, call Hash to find index, then call Add to the List in Table[index] to add it
 * @param name : Name of Entry to be added
 * @param type : type of Entry. See the Main function for example how to find it
 * @return  true if added and false otherwise, the List Table[index] Already returns this for you
 */
STEntry* STable::AddEntryToHashTable(char* name, STE_TYPE type)
{
    bool Added = Table[indexHash].AddEntry(name, type, this->fold_case_flag);
    
    
    //return Added;

    //if we want to return a point to the entry
    STEntry* entry =  Table[indexHash].FindEntry(name, this->fold_case_flag);
    return entry;
}





bool STable::AddEntryToLinkedList(char* name, STE_TYPE type)
{
    bool Added = Head->AddEntry(name, type, this->fold_case_flag);
    return Added;
}


void STable::Add_New_STListToLinkedList()
{
    newScopeInGlobal++;
    STList* stlist = new STList();
    stlist->Next = Head;
    Head = stlist;
    changeHash();
}

void STable::Remove_STListFromLinkedList()
{
    newScopeInGlobal--;
    Head = Head->Next;
    indexHash = indexPreHash;
    if (newScopeInGlobal == 0) {
        indexHash = 0;
    }
}

/**
 * @brief STable::FindAndPrintEntry Finds and prints the Entry if it is found
 *                if Not found print the Message Not found, see the example result
 * @param name  : name to search for
 * @param fp  : File pointer to print : See Example in reults
 */
void  STable::FindAndPrintEntry(char* name, FILE* fp)// may be find and print entry
{
    STEntry* ste = NULL;
    STList* tmp = Head;
    while (tmp != NULL) {
        ste = tmp->FindEntry(name, this->fold_case_flag);
        if (ste) return;
        tmp = tmp->Next;
    }
    fprintf(fp, "Error: '%s' was not declared in this scope nor the outer scopes\n", name);
    
}
/**
 * @brief STable::PrintAll : Prints all Elements. Print the Count of each list and the Entries.
 *                            See the Sample Result (fout.txt) to format your output
 *                            Loop through the Slots (Lists) and Call Table[i].printAll
 * @param fp
 */

void STable::PrintAll(FILE* fp)
{
    unsigned long i;
    for (i = 0; i < Size; i++)
    {
        fprintf(fp, "T[%d]: %d ste:\t", i, Table[i].Count());
        Table[i].PrintAll(fp);
    }
    fprintf(fp, "\n==============\n");
    STList* tmp = Head;
    while (tmp != NULL) {
        tmp->PrintAll(fp);
        tmp = tmp->Next;
        fprintf(fp, "**********\n");
    }
    
}




/**
 * @brief STable::Clear : Delete All Elements, use a loop and call the Table[i].clear. Then Delete the Array Table
 */
void STable::Clear()
{
    unsigned long i;
    for (i = 0; i < Size; i++)
    {
        Table[i].Clear();
    }
    delete[]Table;

}
STable::~STable()
{
    Clear();
}


