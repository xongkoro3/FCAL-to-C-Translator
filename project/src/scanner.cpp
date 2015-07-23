#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <regex.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "regex.h"
#include "scanner.h"

using namespace std;

regex_t *whiteSpace = makeRegex ("^[\n\t\r ]+") ;
regex_t *blockComment = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/") ;
regex_t *lineComment = makeRegex ("^//[^\n]*\n") ;

Token::Token (string _lexeme, tokenType _terminal, Token *_next) {
    lexeme = _lexeme;
    terminal = _terminal;
    next = _next ;
}

Token * Scanner::scan(const char *text) {
    int numMatchedChars;
    Token *start = NULL;
    Token *current;
    Token *last;
    
    //Remove white space and comments from the text
    numMatchedChars=consumeWhiteSpaceAndComments(whiteSpace, blockComment, lineComment, text);
    text += numMatchedChars ;
    current = start;
    last = start;
    while (text[0] != '\0') {
        
        //match the next token and make it the last one
        last = nextToken(text) ;
        if (start!=NULL) {
            current->next=last;
            current=last;
        } else {
            start=last;
            current=last;
        }
        text += current->lexeme.length();
        numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockComment, lineComment, text) ;
        text += numMatchedChars;
    }
    last = new Token("endOfFile", endOfFile, NULL);
    
    if (start == NULL) {
        return last;
    }
    
    current->next = last;
    return start;
}

Token * Scanner::nextToken(const char *text) {
    int max;
    int count;
    string lexeme = "";
    Token *result;
    
    int i;
    max=0;
    for (i = intKwd; i != lexicalError+1; i++) {
        //as long as max is smaller than the number of matched characters
        if (!(max >= matchRegex(reg_expressions[i], text))) {
            count = i;
            max = matchRegex(reg_expressions[i], text);
            lexeme.assign(text, matchRegex(reg_expressions[i], text));
        }
    }
    result = new Token(lexeme,static_cast<tokenType>(count),NULL);
    return result;
}

int Scanner::matchRegex (regex_t *re, const char *text) {
    int status ;
    const int nsub=1 ;
    regmatch_t matches[nsub] ;
    
    /* execute the regular expression match against the text.  If it
     matches, the beginning and ending of the matched text are stored
     in the first element of the matches array.
     */
    status = regexec(re, text, (size_t)nsub, matches, 0);
    
    if (status==REG_NOMATCH) {
        return 0 ;
    }
    else {
        return matches[0].rm_eo ;
    }
}

regex_t* Scanner::makeRegex (const char* pattern) {
    regex_t *re = new regex_t ;
    int rc ;
    
    /* "Compile" the regular expression.  This sets up the regex to do
     the matching specified by the regular expression given as a
     character string.
     */
    rc = regcomp(re, pattern, REG_EXTENDED) ;
    
    if (rc!= 0) {
        // printf ("Error in compiling regular expression.\n");
        size_t length = regerror (rc, re, NULL, 0) ;
        char *buffer = (char *) malloc( sizeof(char) * length ) ;
        (void) regerror (rc, re, buffer, length) ;
        // printf ("%s\n", buffer);
        
        delete re ;
        return NULL;
    }
    else
    return re ;
}

int Scanner::consumeWhiteSpaceAndComments (regex_t *whiteSpace,
                                           regex_t *blockComment,
                                           regex_t *lineComment,
                                           const char *text) {
    int numMatchedChars = 0 ;
    int totalNumMatchedChars = 0 ;
    int stillConsumingWhiteSpace ;
    
    do {
        stillConsumingWhiteSpace = 0 ; // exit loop if not reset by a match
        
        // Try to match white space
        numMatchedChars = matchRegex (whiteSpace, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }
        
        // Try to match block comments
        numMatchedChars = matchRegex (blockComment, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }
        
        // Try to match single-line comments
        numMatchedChars = matchRegex (lineComment, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }
    }
    while ( stillConsumingWhiteSpace ) ;
    
    return totalNumMatchedChars ;
}
