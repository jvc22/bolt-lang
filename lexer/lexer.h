#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

using namespace std;

enum class TokenType {
    Undefined,
    Identifier,
    Number,
    String,
    Boolean,
    Keyword,
    Operator,
    Delimiter,
    EndOfFile
};

struct Token {
    TokenType type;
    string value;
    int line;

    Token(TokenType t, const string& v, int l) : type(t), value(v), line(l) {}
};

class Lexer {
    private:
        string source;
        size_t position = 0;
        int currentLine = 1;

    public:
        Lexer(const string& src);
        Token nextToken();
        vector<Token> tokenize();
};

#endif