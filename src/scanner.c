#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct {
  const char* start;
  const char* current;
  int line;
} Scanner;

Scanner scanner;

static bool isAtEnd() {
  return *scanner.current == '\0';
}

static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;

  return token;
}

static Token errorToken(const char* message) {
  Token token;
  token.type = ILLEGAL;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;

  return token;
}

static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

static bool match(char expected) {
  if (isAtEnd()) return false;
  if (*scanner.current != expected) return false;

  scanner.current++;
  return true;
}

static char peek() {
  return *scanner.current;
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\t':
        advance();
        break;

      case '\n':
        scanner.line++;
        advance();
        break;

      default:
        return;
    }
  }
}

static Token string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') scanner.line++;
    advance();
  }

  if (isAtEnd()) return errorToken("Unterminated string.");

  // The closing quote.
  advance();
  return makeToken(STRING);
}

static bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

static Token number() {
  while (isDigit(peek())) advance();

  return makeToken(INT);
}

static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
          c == '_';
}

static TokenType checkKeyword(int start, int length,
    const char* rest, TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }

  return IDENT;
}

static TokenType identifierType() {
  switch (scanner.start[0]) {
    case 'e': return checkKeyword(1, 3, "lse", ELSE);
    case 'i': return checkKeyword(1, 1, "f", IF);
    case 'r': return checkKeyword(1, 5, "eturn", RETURN);
    case 'l': return checkKeyword(1, 2, "et", LET);
    case 't': return checkKeyword(1, 3, "ure", TRUE);
    case 'f':
      if (scanner.current - scanner.start > 1) {
        switch (scanner.start[1]) {
          case 'a': return checkKeyword(2, 3, "lse", FALSE);
          case 'n': return FUNCTION;
        }
      }
      break;
  }
  return IDENT;
}

static Token identifier() {
  while (isAlpha(peek()) || isDigit(peek())) advance();

  return makeToken(identifierType());
}

Token scanToken() {
  skipWhitespace();

  scanner.start = scanner.current;

  if (isAtEnd()) return makeToken(TEOF);

  char c = advance();

  if (isAlpha(c)) return identifier();
  if (isDigit(c)) return number();

  switch (c) {
    case '(': return makeToken(LPAREN);
    case ')': return makeToken(RPAREN);
    case '{': return makeToken(LBRACE);
    case '}': return makeToken(RBRACE);
    case ';': return makeToken(SEMICOLON);
    case ',': return makeToken(COMMA);
    case '-': return makeToken(MINUS);
    case '+': return makeToken(PLUS);
    case '/': return makeToken(SLASH);
    case '*': return makeToken(ASTERISK);
    case '<': return makeToken(LT);
    case '>': return makeToken(GT);
    case '!':
      return makeToken(
          match('=') ? NOT_EQ : BANG);
    case '=':
      return makeToken(
          match('=') ? EQ : ASSIGN);
    case '"': return string();
  }

  return errorToken("Unexpected character.");
}

void initScanner(const char* source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}
