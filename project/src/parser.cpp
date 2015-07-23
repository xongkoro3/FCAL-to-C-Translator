/* A recursive descent parser with operator precedence.
 
 Author: Eric Van Wyk
 Modified: Robert Edge
 
 This algorithm is based on the work of Douglas Crockford in "Top
 Down Operator Precedence", a chapter in the book "Beautiful Code".
 Mr. Crockford describes in his chapter how his work is based on an
 algorithm described Vaughan Pratt in "Top Down Operator
 Precedence", presented at the ACM Symposium on Principles of
 Programming Languages.
 
 Douglas Crockford's chapter is available at
 http://javascript.crockford.com/tdop/tdop.html
 
 Vaughan Pratt's paper is available at
 http://portal.acm.org/citation.cfm?id=512931
 
 These are both quite interesting works and worth reading if you
 find the problem of parsing to be an interesting one.
 
 Last modified: Oct 13, 2013.
 
 */

#include "parser.h"
#include "scanner.h"
#include "extToken.h"
#include "AST.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <sstream>

using namespace std ;

/*! This is the destructor for the parser. It destroys the Parser instance and deallocates memory.
 */
Parser::~Parser() {
    if (s) delete s ;
    
    ExtToken *extTokenToDelete ;
    currToken = tokens ;
    while (currToken) {
        extTokenToDelete = currToken ;
        currToken = currToken->next ;
        delete extTokenToDelete ;
    }
    
    Token *tokenToDelete ;
    Token *currScannerToken = stokens ;
    while (currScannerToken) {
        tokenToDelete = currScannerToken ;
        currScannerToken = currScannerToken->next ;
        delete tokenToDelete ;
    }
    
}

/*! This is the constructor for the parser. It initializes the variables of Parser.
 */
Parser::Parser ( ) {
    currToken = NULL; prevToken = NULL ; tokens = NULL;
    s = NULL; stokens = NULL;
}

/*! This is a method to parse the text character extracted from a file in the FCAL language. It requires one parameter: the text from the test file.
 
 \param text the text extracted from the FCAL file, in 'char'
 */
ParseResult Parser::parse (const char *text) {
    assert (text != NULL) ;
    
    ParseResult pr ;
    try {
        s = new Scanner() ;
        stokens = s->scan (text) ;
        tokens = extendTokenList ( this, stokens ) ;
        
        assert (tokens != NULL) ;
        currToken = tokens ;
        pr = parseProgram( ) ;
    }
    catch (string errMsg) {
        pr.ok = false ;
        pr.errors = errMsg ;
        pr.ast = NULL ;
    }
    return pr ;
}

/*
 * parse methods for non-terminal symbols
 * --------------------------------------
 */

/*! This is a method to parse a Program extracted from the test file.
 */
ParseResult Parser::parseProgram () {
    ParseResult pr ;
    
    /*! Matching Program based on the follow structure:
     Program ::= varName '(' ')' '{' Stmts '}'
     */
    match(variableName) ;
    string name( prevToken->lexeme ) ;
    
    VarName* v = new VarName(name) ;
    match(leftParen) ;
    match(rightParen) ;
    match(leftCurly);
    ParseResult prStmts = parseStmts() ;
    Stmts* s = NULL;
    
    /* This is a method to verify that the ast field is a Stmts pointer.
     */
    if (prStmts.ast) {
        s = dynamic_cast<Stmts *>(prStmts.ast) ;
        if(!s) throw ((string) "Wrong cast in Stmts");
    }
    match(rightCurly);
    match(endOfFile) ;
    
    pr.ast = new Program(v, s) ;
    
    return pr ;
}


/*! This is a method to parse a Matrix Declaration extracted from the test file. It handles special matrix syntax, and serves an identical purpose as parseDecl (below).
 */
ParseResult Parser::parseMatrixDecl () {
    ParseResult pr ;
    
    VarName *v1;
    VarName *v2;
    VarName *v3;
    
    Expr *expression1 = NULL;
    Expr *expression2 = NULL;
    Expr *expression3 = NULL;
    
    match(matrixKwd);
    match(variableName) ;
    v1 =new VarName(prevToken->lexeme);

    /*! Matching Matrix Declaration based on the follow structure:
     Decl ::= 'Matrix' varName '[' Expr ',' Expr ']' varName ',' varName  '=' Expr ';'
     */
    if(attemptMatch(leftSquare)) {
        ParseResult expr1 = parseExpr(0);
        match(comma);
        ParseResult expr2 = parseExpr(0);
        match(rightSquare);
        ParseResult varName1 = parseVariableName();
        match(comma);
        ParseResult varName2 = parseVariableName();
        match(assign);
        ParseResult expr3 = parseExpr(0);
        
        if (expr1.ast && expr2.ast && expr3.ast && varName1.ast and varName2.ast) {
            v2 = dynamic_cast<VarName *>(varName1.ast) ;
            if (!v2) throw("Wrong cast in VarName");
            
            v3 = dynamic_cast<VarName *>(varName2.ast) ;
            if (!v3) throw("Wrong cast in VarName");
            
            expression1 = dynamic_cast<Expr *>(expr1.ast) ;
            if (!expression1) throw("Wrong cast in Expr");
            
            expression2 = dynamic_cast<Expr *>(expr2.ast) ;
            if (!expression2) throw("Wrong cast in Expr");
            
            expression3 = dynamic_cast<Expr *>(expr3.ast) ;
            if (!expression3) throw("Wrong cast in Expr");
            
            pr.ast = new MatrixAdvDecl(v1, v2, v3, expression1, expression2, expression3);
        }
    }
    
    /*! Matching Matrix Declaration based on the follow structure:
     Decl ::= 'Matrix' varName '=' Expr ';'
     */
    else if(attemptMatch(assign)){
        ParseResult expression = parseExpr(0);
        
        if (expression.ast) {
            expression1 = dynamic_cast<Expr *>(expression.ast) ;
            if (!expression1) throw("Wrong cast in Expr");
        }
        pr.ast = new MatrixDecl(v1, expression1);
    }
    else{
        throw ( (string) "Bad Syntax of Matrix Decl in in parseMatrixDecl" ) ;
    }
    
    match(semiColon) ;
    
    return pr ;
}

/*! This is a method to parse a Standard Declaration extracted from the test file. The structure of a Standard Decl is below:
 Decl ::= integerKwd varName | floatKwd varName | stringKwd varName
 */
ParseResult Parser::parseStandardDecl(){
    ParseResult prType ;
    
    //ParseResult prType = parseType() ;
    string k ;
    if ( attemptMatch(intKwd) ) {
        /*! Matching Standard Declaration based on the follow structure:
         Type ::= intKwd
         */
        k = prevToken->lexeme;
    }
    
    else if ( attemptMatch(floatKwd) ) {
        /*! Matching Standard Declaration based on the follow structure:
         Type ::= floatKwd
         */
        k = prevToken->lexeme;
    }
    
    else if ( attemptMatch(stringKwd) ) {
        /*! Matching Standard Declaration based on the follow structure:
         Type ::= stringKwd
         */
        k = prevToken->lexeme;
    }
    
    else if ( attemptMatch(boolKwd) ) {
        /*! Matching Standard Declaration based on the follow structure:
         Type ::= boolKwd
         */
        k = prevToken->lexeme;
    }
    
    match(variableName) ;
    VarName* v = new VarName(prevToken->lexeme);
    match(semiColon) ;
    prType.ast = new StandardDecl(k, v);
    return prType ;
}

/*! This is a method to parse a Declaration extracted from the test file.
 */
ParseResult Parser::parseDecl () {
    ParseResult pr ;
    /*! Matching Declaration based on the follow structure:
     Decl :: Matrix variableName ....
     */
    if(nextIs(matrixKwd)){
        pr =parseMatrixDecl();
    }
    
    /*! Matching Declaration based on the follow structure:
     Decl ::= Type variableName semiColon
     */
    else{
        pr=parseStandardDecl();
    }
    return pr ;
}

/*! This is a method to parse Stmts extracted from the test file.
 */
ParseResult Parser::parseStmts () {
    ParseResult pr ;
    //ParseResult dpr = parseStmt
    
    if ( ! nextIs(rightCurly) && !nextIs(inKwd) ) {
        
        /*! Matching Stmts based on the follow structure:
         Stmts ::= Stmt Stmts
         */
        ParseResult prStmt = parseStmt() ;
        ParseResult prStmts = parseStmts() ;
        
        Stmt* statement = NULL;
        Stmts* statements = NULL;
        
        if (prStmt.ast && prStmts.ast) {
            statement = dynamic_cast<Stmt *>(prStmt.ast) ;
            if (!statement) throw("Wrong cast in Stmt");
            
            statements = dynamic_cast<Stmts *>(prStmts.ast) ;
            if (!statements) throw("Wrong cast in Stmts");
        }
        pr.ast = new StmtStmts(statement, statements);
    }
    else {
        
        /*! Matching Stmts based on the follow structure:
         Stmts ::=
         (Nothing to match)
         */
        pr.ast = new EmptyStmts() ;
    }
    return pr ;
}

/*! This is a method to parse Stmt extracted from the test file.
 */
ParseResult Parser::parseStmt () {
    ParseResult pr ;
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= Decl
     */
    if(nextIs(intKwd)||nextIs(floatKwd)||nextIs(matrixKwd)||nextIs(stringKwd)||nextIs(boolKwd)){
        pr = parseDecl();
    }
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= '{' Stmts '}'
     */
    else if (attemptMatch(leftCurly)){
        Stmts *stmts = NULL;
        ParseResult pr1 = parseStmts() ;
        match(rightCurly);
        
        if (pr1.ast) {
            stmts = dynamic_cast<Stmts *>(pr1.ast);
            if (!stmts) throw("Wrong cast in Stmts");
        }
        
        pr.ast = new StmtBlock(stmts);
    }
    
    /*! Matching Stmt based on the follow structures:
     Stmt ::= 'if' '(' Expr ')' Stmt
     Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
     */
    else if (attemptMatch(ifKwd)){
        Expr *ex;
        Stmt *stmt1 = NULL;
        Stmt *stmt2 = NULL;
        
        match(leftParen);
        ParseResult expr = parseExpr(0);
        match(rightParen);
        ParseResult stmtparse = parseStmt();
        
        if (expr.ast && stmtparse.ast) {
            ex = dynamic_cast<Expr *>(expr.ast);
            if (!ex) throw("Wrong cast in Expr");
            
            stmt1 = dynamic_cast<Stmt *>(stmtparse.ast);
            if (!stmt1) throw("Wrong cast in Stmt");
        }
        
        if (attemptMatch(elseKwd)){
            ParseResult stmtparse = parseStmt();
            
            if (stmtparse.ast) {
                stmt2 = dynamic_cast<Stmt *>(stmtparse.ast);
                if (!stmt2) throw("Wrong cast in Stmt");
            }
            
            pr.ast = new IfElseStmt(ex, stmt1, stmt2);
        } else {
            pr.ast = new IfStmt(ex, stmt1);
        }
        
    }
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= varName '=' Expr ';'  | varName '[' Expr ',' Expr ']' '=' Expr ';'
     */
    else if ( attemptMatch (variableName) ) {
        Expr *ex1 = NULL;
        Expr *ex2;
        Expr *ex3;
        VarName *v = new VarName(prevToken->lexeme);
        
        if (attemptMatch ( leftSquare ) ) {
            ParseResult expr1 = parseExpr(0);
            match ( comma ) ;
            ParseResult expr2 = parseExpr (0) ;
            match ( rightSquare ) ;
            
            if (expr1.ast && expr2.ast) {
                ex1 = dynamic_cast<Expr *>(expr1.ast);
                if (!ex1) throw("Wrong cast in Expr");
                
                ex2 = dynamic_cast<Expr *>(expr2.ast);
                if (!ex2) throw("Wrong cast in Expr");
            }
        }
        match(assign);
        ParseResult expr3 = parseExpr(0);
        match(semiColon);
        
        if (expr3.ast) {
            ex3 = dynamic_cast<Expr *>(expr3.ast);
            if (!ex3) throw("Wrong cast in Expr");
        }
        
        if (ex1 == NULL) {
            pr.ast = new StandardAssignStmt(v, ex3);
        } else {
            pr.ast = new MatrixAssignStmt(v, ex1, ex2, ex3);
        }
    }
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= 'print' '(' Expr ')' ';'
     */
    else if ( attemptMatch (printKwd) ) {
        Expr *ex = NULL;
        match (leftParen) ;
        ParseResult expr = parseExpr(0);
        match (rightParen) ;
        match (semiColon) ;
        
        if (expr.ast) {
            ex = dynamic_cast<Expr *>(expr.ast);
            if (!ex) throw("Wrong cast in Expr");
        }
        pr.ast = new PrintStmt(ex);
    }
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= 'for' '(' varName '=' Expr ':' Expr ')' Stmt
     */
    else if ( attemptMatch (forKwd) ) {
        Expr *ex1 = NULL;
        Expr *ex2 = NULL;
        Stmt *stmt = NULL;
        
        match (leftParen) ;
        match (variableName) ;
        VarName *v = new VarName(prevToken->lexeme);
        match (assign) ;
        ParseResult expr1 = parseExpr (0) ;
        match (colon) ;
        ParseResult expr2 = parseExpr (0) ;
        match (rightParen) ;
        ParseResult stmtparse = parseStmt () ;
        
        if (expr1.ast && expr2.ast && stmtparse.ast) {
            ex1 = dynamic_cast<Expr *>(expr1.ast);
            if (!ex1) throw("Wrong cast in Expr");
            
            ex2 = dynamic_cast<Expr *>(expr2.ast);
            if (!ex2) throw("Wrong cast in Expr");
            
            stmt = dynamic_cast<Stmt *>(stmtparse.ast);
            if (!stmt) throw("Wrong cast in Stmt");
        }
        pr.ast = new ForStmt(v, ex1, ex2, stmt);
    }
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= 'while' '(' Expr ')' Stmt
     */
    else if (attemptMatch(whileKwd)) {
        Expr *ex = NULL;
        Stmt *stmt = NULL;
        
        match(leftParen);
        ParseResult expr = parseExpr(0);
        match(rightParen);
        ParseResult stmtparse = parseStmt();
        
        if (expr.ast && stmtparse.ast) {
            ex = dynamic_cast<Expr *>(expr.ast);
            if (!ex) throw("Wrong cast in Expr");
            
            stmt = dynamic_cast<Stmt *>(stmtparse.ast);
            if (!stmt) throw("Wrong cast in Stmt");
        }
        pr.ast = new WhileStmt(ex, stmt);
    }
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= ';
     */
    else if ( attemptMatch (semiColon) ) {
        // parsed a skip
    }
    else{
        throw ( makeErrorMsg ( currToken->terminal ) + " while parsing a statement" ) ;
    }
    
    /*! Matching Stmt based on the follow structure:
     Stmt ::= variableName assign Expr semiColon
     */
    return pr ;
}


/*! This is a method to parse Expression extracted from the test file.
 */
ParseResult Parser::parseExpr (int rbp) {
    /* Examine current token, without consuming it, to call its
     associated parse methods.  The ExtToken objects have 'nud' and
     'led' methods that are dispatchers that call the appropriate
     parse methods.*/
    ParseResult left = currToken->nud() ;
    
    while (rbp < currToken->lbp() ) {
        left = currToken->led(left) ;
    }
    
    return left ;
}


/*
 * parse methods for Expr productions
 * ----------------------------------
 */

/*! This is a method to parse TrueKwd extracted from the test file. This Expr has the following structure:
 Expr ::= trueKwd
 */
ParseResult Parser::parseTrueKwd ( ) {
    ParseResult pr ;
    match ( trueKwd ) ;
    pr.ast = new AnyConst(prevToken->lexeme);
    return pr ;
}

/*! This is a method to parse FalseKwd extracted from the test file. This Expr has the following structure:
 Expr ::= falseKwd
 */
ParseResult Parser::parseFalseKwd ( ) {
    ParseResult pr ;
    match ( falseKwd ) ;
    pr.ast = new AnyConst(prevToken->lexeme);
    return pr ;
}

/*! This is a method to parse IntConst extracted from the test file. This Expr has the following structure:
 Expr ::= intConst
 */
ParseResult Parser::parseIntConst ( ) {
    ParseResult pr ;
    match ( intConst ) ;
    pr.ast = new AnyConst(prevToken->lexeme) ;
    return pr ;
}

/*! This is a method to parse FloatConst extracted from the test file. This Expr has the following structure:
 Expr ::= floatConst
 */
ParseResult Parser::parseFloatConst ( ) {
    ParseResult pr ;
    match ( floatConst ) ;
    pr.ast = new AnyConst(prevToken->lexeme);
    return pr ;
}

/*! This is a method to parse StringConst extracted from the test file. This Expr has the following structure:
 Expr ::= stringConst
 */
ParseResult Parser::parseStringConst ( ) {
    ParseResult pr ;
    match ( stringConst ) ;
    pr.ast = new AnyConst(prevToken->lexeme);
    return pr ;
}

/*! This is a method to parse VariableName extracted from the test file. This Expr has the following structure:
 Expr ::= variableName
 */
ParseResult Parser::parseVariableName ( ) {
    ParseResult pr ;
    Expr *ex1 = NULL;
    Expr *ex2 = NULL;
    
    match ( variableName ) ;
    VarName* v = new VarName(prevToken->lexeme);
    
    if(attemptMatch(leftSquare)){
        ParseResult expr1 = parseExpr(0);
        match(comma);
        ParseResult expr2 = parseExpr(0);
        match(rightSquare);
        
        if (expr1.ast && expr2.ast) {
            ex1 = dynamic_cast<Expr *>(expr1.ast);
            if (!ex1) throw("Wrong cast in Expr");
            
            ex2 = dynamic_cast<Expr *>(expr2.ast);
            if (!ex2) throw("Wrong cast in Expr");
        }
        
        pr.ast = new MatrixRefExpr(v, ex1, ex2);
    }
    
    /*! Matching Expr (NextedOrFunction Call) based on the follow structure:
     Expr ::= varableName '(' Expr ')'
     */
    else if(attemptMatch(leftParen)){
        ParseResult expr = parseExpr(0);
        match(rightParen);
        
        if (expr.ast) {
            ex1 = dynamic_cast<Expr *>(expr.ast);
            if (!ex1) throw("Wrong cast in Expr");
        }
        
        pr.ast = new FunctionCall(v, ex1);
    }
    
    /*! Matching Expr based on the follow structure:
     Expr := variableName
     */
    else{
        // variable
        pr.ast = v;
    }
    
    return pr ;
}

/*! This is a method to parse NestedExpr extracted from the test file. This Expr has the following structure:
 Expr ::= leftParen Expr rightParen
 */
ParseResult Parser::parseNestedExpr ( ) {
    ParseResult pr ;
    Expr *ex = NULL;
    match ( leftParen ) ;
    ParseResult expr = parseExpr(0) ;
    match(rightParen) ;
    
    if (expr.ast) {
        ex = dynamic_cast<Expr *>(expr.ast);
        if (!ex) throw("Wrong cast in Expr");
    }
    
    pr.ast = new ParensExpr(ex);
    return pr ;
}

/*! This is a method to parse IfExpr extracted from the test file. This Expr has the following structure:
 Expr ::= 'if' Expr 'then' Expr 'else' Expr
 */
ParseResult Parser::parseIfExpr(){
    ParseResult pr ;
    Expr *ex1 = NULL;
    Expr *ex2 = NULL;
    Expr *ex3 = NULL;
    
    match(ifKwd);
    ParseResult expr1 = parseExpr(0);
    match(thenKwd);
    ParseResult expr2 = parseExpr(0);
    match(elseKwd);
    ParseResult expr3 = parseExpr(0);
    
    if (expr1.ast && expr2.ast && expr3.ast) {
        ex1 = dynamic_cast<Expr *>(expr1.ast);
        if (!ex1) throw("Wrong cast in Expr");
        
        ex2 = dynamic_cast<Expr *>(expr2.ast);
        if (!ex2) throw("Wrong cast in Expr");
        
        ex3 = dynamic_cast<Expr *>(expr3.ast);
        if (!ex3) throw("Wrong cast in Expr");
    }
    
    pr.ast = new IfExpr(ex1, ex2, ex3);
    return pr;
}

/*! This is a method to parse LetExpr extracted from the test file. This Expr has the following structure:
 Expr ::= 'let' Stmts 'in' Expr 'end'
 */
ParseResult Parser::parseLetExpr(){
    ParseResult pr ;
    Stmts *stmts = NULL;
    Expr *ex = NULL;
    
    match(letKwd);
    ParseResult stmtsparse = parseStmts();
    match(inKwd);
    ParseResult expr = parseExpr(0);
    match(endKwd);
    if (stmtsparse.ast && expr.ast) {
        stmts = dynamic_cast<Stmts *>(stmtsparse.ast);
        if (!stmts) throw("Wrong cast in Expr");
        
        ex = dynamic_cast<Expr *>(expr.ast);
        if (!ex) throw("Wrong cast in Expr");
    }
    
    pr.ast = new LetExpr(stmts, ex);
    return pr;
}

/*! This is a method to parse NotExpr extracted from the test file. This Expr has the following structure:
 Expr ::= '!' Expr
 */
ParseResult Parser::parseNotExpr () {
    ParseResult pr ;
    Expr *ex = NULL;
    
    match ( notOp ) ;
    ParseResult expr = parseExpr( 0 );
    if (expr.ast) {
        ex = dynamic_cast<Expr *>(expr.ast);
        if (!ex) throw("Wrong cast in Expr");
    }
    
    pr.ast = new NotExpr(ex);
    return pr ;
    
}

/*! This is a method to parse Addition extracted from the test file. This Expr has the following structure:
 Expr ::= Expr plusSign Expr
 */
ParseResult Parser::parseAddition ( ParseResult prLeft ) {
    /* Check that parser has already matched left expression
     */
    Expr* left = dynamic_cast<Expr *>(prLeft.ast);
    if (!left) throw("Wrong cast in Expr");
    
    ParseResult pr ;
    match ( plusSign ) ;
    string lex = prevToken->lexeme;
    ParseResult ex = parseExpr( prevToken->lbp() );
    
    Expr* right = dynamic_cast<Expr *>(ex.ast);
    if (!right) throw("Wrong cast in Expr");
    
    pr.ast = new BinOpExpr(left, lex, right);
    return pr ;
}

/*! This is a method to parse Multiplication extracted from the test file. This Expr has the following structure:
 Expr ::= Expr star Expr
 */
ParseResult Parser::parseMultiplication ( ParseResult prLeft ) {
    
    /* Parser has already matched left expression
     */
    Expr* left = dynamic_cast<Expr *>(prLeft.ast);
    if (!left) throw("Wrong cast in Expr");
    
    ParseResult pr ;
    match ( star ) ;
    string lex = prevToken->lexeme;
    ParseResult ex = parseExpr( prevToken->lbp() );
    
    Expr* right = dynamic_cast<Expr *>(ex.ast);
    if (!right) throw("Wrong cast in Expr");
    
    pr.ast = new BinOpExpr(left, lex, right);
    return pr ;
}

/*! This is a method to parse Subtraction extracted from the test file. This Expr has the following structure:
 Expr ::= Expr dash Expr
 */
ParseResult Parser::parseSubtraction ( ParseResult prLeft ) {
    /* Parser has already matched left expression
     */
    Expr* left = dynamic_cast<Expr *>(prLeft.ast);
    if (!left) throw("Wrong cast in Expr");
    
    ParseResult pr ;
    match ( dash ) ;
    string lex = prevToken->lexeme;
    ParseResult ex = parseExpr( prevToken->lbp() );
    
    Expr* right = dynamic_cast<Expr *>(ex.ast);
    if (!right) throw("Wrong cast in Expr");
    
    pr.ast = new BinOpExpr(left, lex, right);
    return pr ;
}

/*! This is a method to parse Division extracted from the test file. This Expr has the following structure:
 Expr ::= Expr forwardSlash Expr
 */
ParseResult Parser::parseDivision ( ParseResult prLeft ) {
    /* Parser has already matched left expression
     */
    Expr* left = dynamic_cast<Expr *>(prLeft.ast);
    if (!left) throw("Wrong cast in Expr");
    
    ParseResult pr ;
    match ( forwardSlash ) ;
    string lex = prevToken->lexeme;
    ParseResult ex = parseExpr( prevToken->lbp() );
    
    Expr* right = dynamic_cast<Expr *>(ex.ast);
    if (!right) throw("Wrong cast in Expr");
    
    pr.ast = new BinOpExpr(left, lex, right);
    return pr ;
}


// Expr ::= Expr equalEquals Expr
// Expr ::= Expr lessThanEquals Expr
// Expr ::= Expr greaterThanEquals Expr
// Expr ::= Expr notEquals Expr
// Expr ::= Expr leftAngle Expr
// Expr ::= Expr rightAngle Expr
/* Notice that for relational operators we use just one parse
 function. This shows another possible means for implementing
 expressions, as opposed to the method used for arithmetic
 expressions in which each operation has its own parse method. It
 will depend on what we do in iteration 3 in building an abstract
 syntax tree to decide which method is better.
 */


/*! This is a method to parse Relational Expressions extracted from the test file.
 */
ParseResult Parser::parseRelationalExpr ( ParseResult prLeft ) {
    /* Parser has already matched left expression
     */
    ParseResult pr ;
    
    nextToken( ) ;
    /* This method just advances token, since examining it in parseExpr caused this method being called.
     */
    string op = prevToken->lexeme ;
    
    /* This is a method to verify that the ast field is a Stmts pointer.
     */
    ParseResult right = parseExpr( prevToken->lbp() );
    BinOpExpr *i = new BinOpExpr(dynamic_cast<Expr*>(prLeft.ast), op, dynamic_cast<Expr*>(right.ast));
    if (!i) throw("Wrong cast in BinaryOper");
    
    pr.ast = i;
    
    return pr ;
}


/*! This is a helper method used by the parser, to match the token type to the terminal found in the test file. It requires one parameter: the token type we want to match to.
 \param tt the tokenType stored that we want to match to, in 'tokenType'
 */
void Parser::match (tokenType tt) {
    if (! attemptMatch(tt)) {
        throw ( makeErrorMsgExpected ( tt ) ) ;
    }
}


/*! This is a helper boolean method used by the parser, to attempt to match the token type to the terminal found in the test file, used in cases where we're not sure which terminal we will encounter next. Returns yes if the tokenType we guess is the correct one, no otherwise.  It requires one parameter: the token type we want to match to.
 \param tt the tokenType stored that we want to match to, in 'tokenType'
 */
bool Parser::attemptMatch (tokenType tt) {
    if (currToken->terminal == tt) {
        nextToken() ;
        return true ;
    }
    return false ;
}

/*! This is a helper boolean method used by the parser, to determine the next tokenType we will encounter. It requires one parameter: the token type we think will come next.
 \param tt the tokenType we think we will encounter next, in 'tokenType'
 */
bool Parser::nextIs (tokenType tt) {
    return currToken->terminal == tt ;
}

/*! This is a helper method used by the parser, to get the next token from the test file.
 */
void Parser::nextToken () {
    if ( currToken == NULL )
    throw ( string("Internal Error: should not call nextToken in unitialized state"));
    else
    if (currToken->terminal == endOfFile && currToken->next == NULL) {
        prevToken = currToken ;
    } else if (currToken->terminal != endOfFile && currToken->next == NULL) {
        throw ( makeErrorMsg ( "Error: tokens end with endOfFile" ) ) ;
    } else {
        prevToken = currToken ;
        currToken = currToken->next ;
    }
}

/*! This is a helper method used by the parser, to get the description of the terminal . It requires one parameter: the terminal we want description of.
 \param terminal the terminal we are receiving a description for, in 'tokenType'
 */
string Parser::terminalDescription ( tokenType terminal ) {
    Token *dummyToken = new Token ("",terminal, NULL) ;
    ExtToken *dummyExtToken = extendToken (this, dummyToken) ;
    string s = dummyExtToken->description() ;
    delete dummyToken ;
    delete dummyExtToken ;
    return s ;
}
/*! This is a helper method used by the parser, to output the error message that we receive in the "Expected...but found..." format, if the test fails. It requires one parameter: the terminal parsed in from the inputted test file.
 \param terminal the terminal parsed in from the test file, in 'tokenType'
 */
string Parser::makeErrorMsgExpected ( tokenType terminal ) {
    string s = (string) "Expected " + terminalDescription (terminal) +
    " but found " + currToken->description() ;
    return s ;
}

/*! This is a helper method used by the parser, to output the error message that contains the Unexpected Symbol that we receive, if the test fails. It requires one parameter: the terminal parsed in from the inputted test file.
 \param terminal the terminal parsed in from the test file, in 'tokenType'
 */
string Parser::makeErrorMsg ( tokenType terminal ) {
    string s = "Unexpected symbol " + terminalDescription (terminal) ;
    return s ;
}

/*! This is a helper method used by the parser, to output the error message. It requires one parameter: an input message.
 \param msg the error message
 */
string Parser::makeErrorMsg ( const char *msg ) {
    return msg ;
}