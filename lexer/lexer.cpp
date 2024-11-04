#include "lexer.h"
#include <cctype>
#include <set>

using namespace std;

set<string> operators = {
    "+", "-", "*", "/", "="
};

set<string> keywords = {
    "if", "else", "while", "for", "return", "let", "function", "print"
};

set<string> delimiters = {
    ",", ";", "(", ")", "[", "]", "{", "}"
};

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

    // Alphanumeric (identifier & keyword) verification
    if (isalpha(source[position])) {
        string identifier;

        while (position < source.length() && (isalnum(source[position]) || source[position] == '_')) {
            identifier += source[position++];
        }

        if (keywords.find(identifier) != keywords.end()) {
            return Token(TokenType::Keyword, identifier, currentLine);
        }

        return Token(TokenType::Identifier, identifier, currentLine);
    }

    // Number verification
    if (isdigit(source[position])) {
        string number;

        while (position < source.length() && isdigit(source[position])) {
            number += source[position++];
        }

        return Token(TokenType::Number, number, currentLine);
    }

    // String verification
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

    // Operators verification
    if (operators.find(string(1, source[position])) != operators.end()) {
        string op = string(1, source[position]);

        if (op == "=") {
            if (position + 1 < source.length() && source[position + 1] == '=') {
                position += 2;

                return Token(TokenType::Operator, "==", currentLine);
            } else {
                position++;

                return Token(TokenType::Operator, "=", currentLine);
            }
        }

        return Token(TokenType::Operator, op, currentLine);
    }

    // Delimiters verification
    if (delimiters.find(string(1, source[position])) != delimiters.end()) {
        string de = string(1, source[position++]);

        return Token(TokenType::Delimiter, de, currentLine);
    }

    return Token(TokenType::Undefined, string(1, source[position++]), currentLine);
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    Token token = nextToken();

    while (token.type != TokenType::EndOfFile) {
        tokens.push_back(token);
        token = nextToken();
    }

    return tokens;
}