#ifndef SCANNER_H
#define SCANNER_H

#include <regex.h>
#include <string>
#include "regex.h"

class Token ;

enum tokenEnumType {
    
    intKwd, floatKwd, boolKwd,
    trueKwd, falseKwd, stringKwd,  matrixKwd,
    letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd,
    forKwd, whileKwd, printKwd,
    
    // Constants
    intConst, floatConst, stringConst,
    
    // Names
    variableName ,
    
    // Punctuation
    leftParen, rightParen,
    leftCurly, rightCurly,
    leftSquare, rightSquare,
    
    comma, semiColon, colon,
    
    //Operators
    assign,
    plusSign, star, dash, forwardSlash,
    lessThan, lessThanEqual, greaterThan, greaterThanEqual,
    equalsEquals, notEquals,
    andOp, orOp, notOp,
    
    // Special terminal types
    endOfFile ,
    lexicalError
} ;
typedef enum tokenEnumType tokenType ;


class Token {
    public:
    Token (std::string, tokenType, Token *);
    std::string lexeme ;
    tokenType terminal ;
    Token * next ;
} ;

class Scanner {
    public:
    //Given
    int matchRegex (regex_t *, const char *) ;
    regex_t *makeRegex (const char* pattern) ;
    int consumeWhiteSpaceAndComments (regex_t *whiteSpace, regex_t *blockComment, regex_t *lineComment, const char *text) ;

    //New
    Token * nextToken(const char *text) ;
    Token * scan(const char *text) ;
    
    regex_t* reg_expressions[lexicalError+1] ;
    Scanner() {
        reg_expressions[intKwd] = makeRegex("^Int") ;
        reg_expressions[floatKwd] = makeRegex("^Float") ;
        reg_expressions[boolKwd] = makeRegex("^Bool") ;
        reg_expressions[trueKwd] = makeRegex("^True") ;
        reg_expressions[falseKwd] = makeRegex("^False") ;
        reg_expressions[stringKwd] = makeRegex("^Str") ;
        reg_expressions[matrixKwd] = makeRegex("^Matrix") ;
        reg_expressions[letKwd] = makeRegex("^let") ;
        reg_expressions[inKwd] = makeRegex("^in") ;
        reg_expressions[endKwd] = makeRegex("^end");
        reg_expressions[ifKwd] = makeRegex("^if") ;
        reg_expressions[thenKwd] = makeRegex("^then") ;
        reg_expressions[elseKwd] = makeRegex("^else") ;
        reg_expressions[forKwd] = makeRegex("^for") ;
        reg_expressions[whileKwd] = makeRegex("^while") ;
        reg_expressions[printKwd] = makeRegex("^print") ;
        
        //Constants
        reg_expressions[intConst] = makeRegex("^[0-9]+") ;
        reg_expressions[floatConst] = makeRegex("^[0-9]*\\.?[0-9]*") ;
        reg_expressions[stringConst] = makeRegex("^\"(\\.|[^\"])*\"");
        
        //Names
        reg_expressions[variableName] = makeRegex("^[a-zA-Z_][a-zA-Z_0-9]*") ;
        
        //Punctuation
        reg_expressions[leftParen] = makeRegex("^\\(") ;
        reg_expressions[rightParen] = makeRegex("^)") ;
        reg_expressions[leftCurly] = makeRegex("^\\{") ;
        reg_expressions[rightCurly] = makeRegex("^}") ;
        reg_expressions[leftSquare] = makeRegex("^\\[") ;
        reg_expressions[rightSquare] = makeRegex("^]") ;
        reg_expressions[comma] = makeRegex("^,") ;
        reg_expressions[semiColon] = makeRegex("^;") ;
        reg_expressions[colon] = makeRegex("^:") ;
        
        //Operators
        reg_expressions[assign] = makeRegex("^=") ;
        reg_expressions[plusSign] = makeRegex("^\\+") ;
        reg_expressions[star] = makeRegex("^\\*") ;
        reg_expressions[dash] = makeRegex("^-") ;
        reg_expressions[forwardSlash] = makeRegex("^/") ;
        reg_expressions[lessThan] = makeRegex("^<") ;
        reg_expressions[lessThanEqual] = makeRegex("^<=") ;
        reg_expressions[greaterThan] = makeRegex("^>") ;
        reg_expressions[greaterThanEqual] = makeRegex("^>=") ;
        reg_expressions[equalsEquals] = makeRegex("^==") ;
        reg_expressions[notEquals] = makeRegex("^!=") ;
        reg_expressions[andOp] = makeRegex("^&&") ;
        reg_expressions[orOp] = makeRegex("^\\|\\|") ;
        reg_expressions[notOp] = makeRegex("^!") ;
        
        //Special terminal types
        reg_expressions[endOfFile] = makeRegex("^EOF") ;
        reg_expressions[lexicalError] = makeRegex("[^ ]") ;
    }
} ;

#endif /* SCANNER_H */