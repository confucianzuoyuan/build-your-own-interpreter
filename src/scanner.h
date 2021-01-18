#ifndef monkey_scanner_h
#define monkey_scanner_h

typedef enum {
    EQ,       // ==
    ASSIGN,   // =
    PLUS,     // +
    MINUS,    // -
    NOT_EQ,   // !=
    BANG,     // !
    SLASH,    // /
    ASTERISK, // *
    LT,       // <
    GT,       // >
    SEMICOLON,// ;
    LPAREN,   // (
    RPAREN,   // )
    COMMA,    // ,
    LBRACE,   // {
    RBRACE,   // }
    LBRAKET,  // [
    RBRAKET,  // ]
    COLON,    // :
    STRING,
    INT,
    ILLEGAL,
    IDENT,    // add, foo, i, j, ...
    TEOF,

    // 关键字
    FUNCTION, // fn
    LET,      // let
    TRUE,     // true
    FALSE,    // false
    IF,       // if
    ELSE,     // else
    RETURN    // return
} TokenType;

typedef struct {
  TokenType type;
  const char* start;
  int length;
  int line;
} Token;

void initScanner(const char* source);
Token scanToken();

#endif
