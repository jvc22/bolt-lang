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

    if (source[position] == '"') {
        position++;
        string str;

        while (position < source.length() && source[position] != '"') {
            if (source[position] == '\\') {
                position++;

                if (position < source.length()) {
                    str += source[position++];
                }
            } else {
                str += source[position++];
            }
        }

        if (position < source.length() && source[position] == '"') {
            position++;
        }

        return Token(TokenType::String, str, currentLine);
    }

    if (source.substr(position, 4) == "true") {
        position += 4;

        return Token(TokenType::Boolean, "true", currentLine);
    }

    if (source.substr(position, 5) == "false") {
        position += 5;

        return Token(TokenType::Boolean, "false", currentLine);
    }


    if (source[position] == '+' || source[position] == '-' || source[position] == '*' || source[position] == '/') {
        char op = source[position];

        return Token(TokenType::Operator, string(1, op), currentLine);
    }

    if (source[position] == '=') {
        if (position + 1 < source.length() && source[position + 1] == '=') {
            position += 2;

            return Token(TokenType::Operator, "==", currentLine);
        } else {
            position++;

            return Token(TokenType::Operator, "=", currentLine);
        }
    }

    if (source[position] == ',') {
        return Token(TokenType::Delimiter, string(1, source[position++]), currentLine);
    }

    if (source[position] == ';') {
        return Token(TokenType::Delimiter, string(1, source[position++]), currentLine);
    }

    if (source[position] == '{' || source[position] == '}') {
        char brace = source[position++];

        return Token(TokenType::Delimiter, string(1, brace), currentLine);
    }

    if (source[position] == '(' || source[position] == ')') {
        char paren = source[position++];

        return Token(TokenType::Delimiter, string(1, paren), currentLine);
    }

    if (source[position] == '[' || source[position] == ']') {
        char bracket = source[position++];

        return Token(TokenType::Delimiter, string(1, bracket), currentLine);
    }

    return Token(TokenType::Undefined, string(1, source[position++]), currentLine);
}