#include "lexer.h"
#include <cctype>

using namespace std;

Lexer::Lexer(const string& src) : source(src) {}

Token Lexer::nextToken() {
    while (position < source.length() && isspace(source[position])) {
        if (source[position] == '\n') {
            currentLine++;
        }

        position++;
    }

    if (position >= source.length()) {
        return Token(TokenType::EndOfFile, "", currentLine);
    }

    if (isalpha(source[position])) {
        string identifier;

        while (position < source.length() && (isalnum(source[position]) || source[position] == '_')) {
            identifier += source[position++];
        }

        return Token(TokenType::Identifier, identifier, currentLine);
    }

    if (isdigit(source[position])) {
        string number;

        while (position < source.length() && isdigit(source[position])) {
            number += source[position++];
        }

        return Token(TokenType::Number, number, currentLine);
    }

    return Token(TokenType::Undefined, string(1, source[position++]), currentLine);
}