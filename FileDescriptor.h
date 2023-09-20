#pragma once
#include <iostream>
#include <fstream>
#define SET 1
#define UNSET 0
#define BUFFER SIZE 256
using namespace std;

class FileDescriptor {

private:
	FILE* fp;
	int lineNumber = 1; /* line number in the file */
	int charNumber; /* character number in the line */
	int flag; /* to prevents two ungets in a row */
	int bufSize = 256; /* stores the buffer size */
	string buffer; /* buffer to store a line */
	char* file; /* file name, allocate memory for this */
	int flag2;
	const char* fileName;

public:
	/* Externally-visible functions: */
	const char* getFileName();
	bool isOpen(); // returns true if a file is open without errors, //otherwise returns false
	char* getCurrLine(); // returns a pointer to buffer, null if EOF
	int setLineNum(int lineNum);
	int getLineNum();
	int getCharNum();
	FileDescriptor(const char* FileName); // opens the stdin FileName is Null
	~FileDescriptor();
	FileDescriptor(); //opens the stdin
	void close(); // closes the file descriptor
	char getChar(); // Gets the current character in the file
	//bool open_file_descriptor (char *filename);
	void reportError(char* msg); // reports the error specifying the current line and //character
	void ungetChar(char c); // puts back the current character, modifies char number
	void flush_buffer();
};
