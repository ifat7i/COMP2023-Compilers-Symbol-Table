#pragma once
#include "FileDescriptor.h"
#include "lexemes.h"



struct	TOKEN {
	LEXEME_TYPE type;
	int value;
	float float_value;
	char* str_ptr;
};



class Scanner {
private:
	FileDescriptor* Fd;
	static const  int keys = 34;
	std::string keywords[keys] = {
	"and", "begin", "boolean", "by", "constant",
	"double","char",
	"do", "else", "end", "false", "fi", "float", "for", "from",
	"function", "if", "integer", "not", "od", "or", "procedure",
	"program", "read", "return", "string", "then", "to", "true",
	"var", "while", "write"
	};
	LEXEME_TYPE key_type[keys] = { KW_AND, KW_BEGIN, KW_BOOLEAN, KW_BY, KW_CONSTANT,
	KW_DOUBLE,
	KW_CHAR,
	KW_DO, KW_ELSE, KW_END, KW_FALSE, KW_FI,KW_FLOAT,
	KW_FOR, KW_FROM, KW_FUNCTION, KW_IF, KW_INTEGER, KW_NOT,
	KW_OD, KW_OR, KW_PROCEDURE, KW_PROGRAM,KW_READ, KW_RETURN,
	KW_STRING, KW_THEN, KW_TO, KW_TRUE, KW_VAR, KW_WHILE, KW_WRITE
	};


	CHARACTER_TYPE getCharacterType(char byte);
	LEXEME_TYPE getOperator(char byte);
	string getOperatorDescription(char byte);
	bool checkKeyword(string s);
	LEXEME_TYPE getLexemeType(string s);





public:
	Scanner();
	Scanner(FileDescriptor* Fd);
	TOKEN* Scan();
	char* getErrorMsg(ERROR_TYPE type);
};





