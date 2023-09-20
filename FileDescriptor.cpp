#include "FileDescriptor.h"



const char* FileDescriptor::getFileName()
{
    return this->fileName;
}

bool FileDescriptor::isOpen()
{
    if (this->fp == NULL) return false;
    return true;
}

char* FileDescriptor::getCurrLine()
{

    return nullptr;
}

int FileDescriptor::setLineNum(int lineNum)
{
    this->lineNumber = lineNum;
    return 0;
}

int FileDescriptor::getLineNum()
{
    return this->lineNumber;
}

int FileDescriptor::getCharNum()
{
    return 0;
}

FileDescriptor::FileDescriptor(const char* fileName)
{
    this->fileName = fileName;
    this->fp = fopen(fileName, "r");
}

FileDescriptor::~FileDescriptor()
{
}

FileDescriptor::FileDescriptor()
{
}

void FileDescriptor::close()
{
    fclose(this->fp);
}

char FileDescriptor::getChar()
{
    char byte = 0;
    byte = fgetc(this->fp);
    buffer.push_back(byte);
    return byte;
}

void FileDescriptor::reportError(char* msg)
{
    cout << "----------------------------------------\n";
    cout << buffer;
    cout << "^^^^^" << "\n";
    cout << "ERROR: ";

    int i = 0;
    while (msg[i] != '\0') {
        char a = (msg[i]);
        cout << a;
        i++;
    }
    cout << " on line " << this->lineNumber << " of ";
    i = 0;
    while (this->fileName[i] != '\0') {
        char a = (this->fileName[i]);
        cout << a;
        i++;
    }
    cout << "\n";
}

void FileDescriptor::ungetChar(char c)
{
    ungetc(c, this->fp);

}

void FileDescriptor::flush_buffer()
{
    this->buffer = "";
}
