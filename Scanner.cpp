#include "Scanner.h"
#include "lexemes.h"
#include <cctype>
#include <regex>


/// <summary>
//////////////////////// PRIVATE
/// </summary>


CHARACTER_TYPE Scanner::getCharacterType(char byte)
{
    CHARACTER_TYPE type = DEFAULT;
    if (byte >= '0' && byte <= '9') type = DIGIT;
    else if ((byte >= 'a' && byte <= 'z') || (byte >= 'A' && byte <= 'Z') || (byte == '_')) type = ID_START;
    else if (byte == '.') type = DOT;
    else if (byte == '-') type = NEGATIVE;
    else if (byte == '\"') type = DOUBLE_QUOTE;
    else if (byte == ';') type = EOC;
    else if (byte == '#') type = COMMENT;
    else if (byte == '\n') type = EOL;
    return type;
}

LEXEME_TYPE Scanner::getOperator(char byte)
{
    LEXEME_TYPE oper = LX_ILLEGAL;
    switch (byte)
    {
    case '(':
        oper = LX_LPAREN;
        break;
    case ')':
        oper = LX_RPAREN;
        break;
    case ':':
        oper = LX_COLON;
        break;
    case '=':
        oper = LX_EQ;
        break;
    case '+':
        oper = LX_PLUS;
        break;
    case '-':
        oper = LX_MINUS;
        break;
    case '*':
        oper = LX_STAR;
        break;
    case '/':
        oper = LX_SLASH;
        break;
    case '!':
        oper = LX_NOT;
        break;
    case '<':
        oper = LX_LT;
        break;
    case '>':
        oper = LX_GT;
        break;
    case ';':
        oper = LX_SEMICOLON;
        break;
    case '[':
        oper = LX_LBRACKET;
        break;
    case ']':
        oper = LX_RBRACKET;
        break;
    case '.':
        oper = LX_DOT;
        break;
    case ',':
        oper = LX_COMMA;
        break;
    case '{':
        oper = LX_LCBRACKET;
        break;
    case '}':
        oper = LX_RCBRACKET;
        break;
    case EOF:
        oper = LX_EOF;
        break;
    default:
        oper = LX_ILLEGAL;
        break;
    }
    return oper;
}


string Scanner::getOperatorDescription(char byte)
{
    std::string str = "";
    switch (byte)
    {
    case '(':
        str = "LX_LPAREN";
        break;
    case ')':
        str = "LX_RPAREN";
        break;
    case ':':
        str = "LX_COLON";
        break;
    case '=':
        str = "LX_EQ";
        break;
    case '+':
        str = "LX_PLUS";
        break;
    case '-':
        str = "LX_MINUS";
        break;
    case '*':
        str = "LX_STAR";
        break;
    case '/':
        str = "LX_SLASH";
        break;
    case '!':
        str = "LX_NOT";
        break;
    case '<':
        str = "LX_LT";
        break;
    case '>':
        str = "LX_GT";
        break;
    case ';':
        str = "LX_SEMICOLON";
        break;
    case '[':
        str = "LX_LBRACKET";
        break;
    case ']':
        str = "LX_RBRACKET";
        break;
    case '.':
        str = "LX_DOT";
        break;
    case ',':
        str = "LX_COMMA";
        break;
    case '{':
        str = "LX_LCBRACKET";
        break;
    case '}':
        str = "LX_RCBRACKET";
        break;
    case EOF:
        str = "LX_EOF";

        break;
    default:
        break;
    }
    return str;
}


bool Scanner::checkKeyword(string s)
{
    for (int i = 0; i < this->keys; i++) {

        if (s.compare(this->keywords[i]) == 0) return true;
    }
    return false;
}

LEXEME_TYPE Scanner::getLexemeType(string s)
{
    for (int i = 0; i < this->keys; i++) {
        if (s.compare(this->keywords[i]) == 0) return (this->key_type[i]);
    }
}


char* Scanner::getErrorMsg(ERROR_TYPE type)
{
    std::string str = "";
    switch (type)
    {
    case UNRECONIZED_WORD:
        str = "Unreconized word/token";
        break;
    case ILLEGAL_ID:
        str = "Illegal Identifier";
        break;
    case BAD_FP_NUMBER:
        str = "Bad Floating Point Number";
        break;
    case BAD_STRING:
        str = "String not declared correctly, missing double quote";
        break;
    case BAD_VARIABLE_DECLARING:
        str = "Wrong way of declaring a variable";
        break;
    default:
        break;
    }
    char* err_msg = new char[str.length() + 1];
    strcpy(err_msg, str.c_str());
    return err_msg;
}

/// <summary>
//////////////////////// PUBLIC
/// </summary>

Scanner::Scanner() {
}

Scanner::Scanner(FileDescriptor* Fd) {
    this->Fd = Fd;
}

TOKEN* Scanner::Scan() {

    TOKEN* token = new TOKEN();
    char byte = 0;
    byte = this->Fd->getChar();
    if (byte == '\n') {
        this->Fd->setLineNum(this->Fd->getLineNum() + 1);
        this->Fd->flush_buffer();
    }


    std::string str = "";


    //COMMENT
    if ((getCharacterType(byte) == COMMENT)) {
        if (getCharacterType(byte = this->Fd->getChar()) == COMMENT) {
            while (1) {
                byte = this->Fd->getChar();
                if (getCharacterType(byte) == COMMENT) {
                    byte = this->Fd->getChar();
                    if (getCharacterType(byte) == COMMENT) {
                        break;
                    }
                }
                else if (getCharacterType(byte) == EOL) break;
            }
            token->type = LX_WHITE_SPACE;
            return token;
        }
        else {
            this->Fd->reportError(getErrorMsg(UNRECONIZED_WORD));
            token->type = LX_ERROR;
            return token;
        }
    }

    //WHITE_SPACES
    if (isspace(byte)) {
        token->type = LX_WHITE_SPACE;
        return token;
    }

    //Identifiers & Reserved Words
    if (getCharacterType(byte) == ID_START) {
        str.push_back(byte);
        while ((getCharacterType(byte = this->Fd->getChar()) == DIGIT) || getCharacterType(byte) == ID_START) {
            str.push_back(byte);
        }
        if (!isspace(byte) && getOperator(byte) == LX_ILLEGAL) {
            this->Fd->reportError(getErrorMsg(ILLEGAL_ID));
            token->type = LX_ERROR;
            return token;
        }
        this->Fd->ungetChar(byte);
        char* id_array = new char[str.length() + 1];
        strcpy(id_array, str.c_str());

        if (this->checkKeyword(str)) {
            token->type = getLexemeType(str);
            token->str_ptr = id_array;
        }
        else {
            token->str_ptr = id_array;
            token->type = LX_IDENTIFIER;
        }
        return token;
    }


    //Integer Literals & FloatingPoint Numbers
    if (getCharacterType(byte) == NEGATIVE) {
        str.push_back('-');
        if (getCharacterType(byte = this->Fd->getChar()) == DIGIT) {
            str.push_back(byte);
            while (getCharacterType(byte = this->Fd->getChar()) == DIGIT) str.push_back(byte);
            if (getCharacterType(byte) == DOT) {
                str.push_back(byte);
                if (getCharacterType(byte = this->Fd->getChar()) == DIGIT) {
                    str.push_back(byte);
                    while (getCharacterType(byte = this->Fd->getChar()) == DIGIT) str.push_back(byte);
                    if (!isspace(byte) && getOperator(byte) == LX_ILLEGAL) {
                        this->Fd->reportError(getErrorMsg(BAD_FP_NUMBER));
                        token->type = LX_ERROR;
                        return token;
                    }
                }
                else {
                    this->Fd->reportError(getErrorMsg(BAD_FP_NUMBER));
                    token->type = LX_ERROR;
                    return token;
                }
                this->Fd->ungetChar(byte);
                token->float_value = std::stof(str);
                token->type = LX_FLOAT;
                return token;
            }
            else if (!isspace(byte) && getOperator(byte) == LX_ILLEGAL) {
                this->Fd->reportError(getErrorMsg(ILLEGAL_ID));
                token->type = LX_ERROR;
                return token;
            }
            this->Fd->ungetChar(byte);
            token->value = std::stoi(str);
            token->type = LX_INTEGER;
            return token;
        }
        else {
            this->Fd->ungetChar(byte);
            byte = '-';
        }
    }


    if (getCharacterType(byte) == DIGIT) {
        str.push_back(byte);
        while (getCharacterType(byte = this->Fd->getChar()) == DIGIT) str.push_back(byte);
        if (getCharacterType(byte) == DOT) {
            str.push_back(byte);
            if (getCharacterType(byte = this->Fd->getChar()) == DIGIT) {
                str.push_back(byte);
                while (getCharacterType(byte = this->Fd->getChar()) == DIGIT) str.push_back(byte);
                if (!isspace(byte) && getOperator(byte) == LX_ILLEGAL) {
                    this->Fd->reportError(getErrorMsg(BAD_FP_NUMBER));
                    token->type = LX_ERROR;
                    return token;
                }
            }
            else {
                this->Fd->reportError(getErrorMsg(BAD_FP_NUMBER));
                token->type = LX_ERROR;
                return token;
            }
            //FLOAT
            this->Fd->ungetChar(byte);
            token->float_value = std::stof(str);
            token->type = LX_FLOAT;
            return token;
        }
        else if (!isspace(byte) && getOperator(byte) == LX_ILLEGAL) {
            this->Fd->reportError(getErrorMsg(ILLEGAL_ID));
            token->type = LX_ERROR;
            return token;
        }
        //INTEGER 
        this->Fd->ungetChar(byte);
        token->value = std::stoi(str);
        token->type = LX_INTEGER;
        return token;
    }

    //Strings
    if (getCharacterType(byte) == DOUBLE_QUOTE) {
        while ((getCharacterType(byte = this->Fd->getChar()) != DOUBLE_QUOTE) && (getCharacterType(byte) != EOL) && (byte != EOF))  str.push_back(byte);
        if (byte == EOF || getCharacterType(byte) == EOL) {
            this->Fd->reportError(getErrorMsg(BAD_STRING));
            token->type = LX_ERROR;
            return token;
        }
        char* id_array = new char[str.length() + 1];
        strcpy(id_array, str.c_str());
        token->str_ptr = id_array;
        token->type = LX_STRING;
        return token;
    }

    //Operators
    if (getOperator(byte) != LX_ILLEGAL) {
        char nextChar = this->Fd->getChar();
        if (getOperator(byte) == LX_COLON && getOperator(nextChar) == LX_EQ) {
            token->type = LX_COLON_EQ;
            str = "LX_COLON_EQ";
        }
        else if (getOperator(byte) == LX_NOT && getOperator(nextChar) == LX_EQ) {
            token->type = LX_NEQ;
            str = "LX_NEQ";
        }
        else if (getOperator(byte) == LX_LT && getOperator(nextChar) == LX_EQ) {
            token->type = LX_LE;
            str = "LX_LE";
        }
        else if (getOperator(byte) == LX_GT && getOperator(nextChar) == LX_EQ) {
            token->type = LX_GE;
            str = "LX_GE";
        }
        else {
            this->Fd->ungetChar(nextChar);
            token->type = getOperator(byte);
            str = getOperatorDescription(byte);
        }
        char* operatorDesc = new char[str.length() + 1];
        strcpy(operatorDesc, str.c_str());
        token->str_ptr = operatorDesc;
        return token;
    }

    else {
        this->Fd->reportError(getErrorMsg(UNRECONIZED_WORD));
        token->type = LX_ERROR;
        return token;
    }





}
