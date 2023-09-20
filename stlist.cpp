#include "stlist.h"
#include <iostream>

/**
 * @brief STList::STList
 * default constructor, initialize head and Counter
 */
STList::STList()
{
    Counter = 0;
    Head = NULL;
    Next = NULL;
}
/**
 * @brief STList::FindEntry: search (linear search) the list and compare the name to the ones in the list
 * @param name : Given name to find
 * @return : If name is found found return NULL otherwise reaturn a pointer to the Node
 */

bool compareCaseInsensitive(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (std::toupper(*str1++) != std::toupper(*str2++))
            return false;
    }
    return *str1 == *str2;
}


STEntry* STList::FindEntry(char* name, bool fold_case_flag)
{
    
    STEntry* ste = Head;
    while (ste != NULL)
    {
        if (fold_case_flag) {
            if(compareCaseInsensitive(name, ste->Name)) return ste;
            ste = ste->Next;
        }
        else {
            if (strcmp(name, ste->Name) == 0) return ste;
            ste = ste->Next;
        }

    }
    return NULL;
}
/**
 * @brief STList::AddEntry : Call FindEntry, if name is alread in table return false, otherwise add it to the list
 *                           Add it as the first Entry, like a stack which is fastest. Update Counter and Head
 * @param name : Name of Entry (variable)
 * @param type : Type of variable
 * @return : True if the node is added and False if the Entry Already exists in the Table
 */
bool STList::AddEntry(char* name, STE_TYPE type, bool fold_case_flag)
{
    STEntry* ste = FindEntry(name, fold_case_flag);
    bool added = false;
    if (ste)
    {
        printf("Entry Already exist, nothing Added\n");
    }
    else
    {
        std::cout << "&\n" << type << "\n";
        std::cout << "&\n" << name << "\n";
        ste = new STEntry(name, type);
        ste->Next = Head;
        Head = ste;
        added = true;
        Counter++;
        ste->print();
    }
    return added;
}
/**
 * @brief STList::PrintAll : Prints All nodes in the list, use the print in the STEntry.
 * @param fp : File Pointer where to write
 */
void STList::PrintAll(FILE* fp)
{
    STEntry* ste = Head;
    while (ste != NULL)
    {
        ste->print(fp);

        ste = ste->Next;
    }
    fprintf(fp, "\n");

}
/**
 * @brief STList::Count returns Counter which is Number of Elements
 * @return
 */
int STList::Count()
{
    return Counter;
}
/**
 * @brief STList::Clear : deletes all Elements in the List and sets the counter to zero
 */
void STList::Clear()
{
    STEntry* ste;
    while (Head != NULL)
    {
        ste = Head;
        Head = Head->Next;
        delete ste;
    }
    Counter = 0;
}

STEntry* STList::getHead()
{
    return this->Head;
}

STList::~STList()
{
    Clear();
}

