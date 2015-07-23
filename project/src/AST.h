#ifndef Node_H
#define Node_H

#include <string>
#include <iostream>

#include "scanner.h"


class Node ;

//Inherited from Node
class Program ;
class Stmt ;
class Stmts ;
class Expr ;

//Inherited from Stmts
class EmptyStmts ;
class StmtStmts ;

//Inherited from Stmt
class StandardDecl ;
class MatrixAdvDecl ;
class MatrixDecl ;
class StmtBlock ;
class IfStmt ;
class IfElseStmt ;
class StandardAssignStmt ;
class MatrixAssignStmt ;
class PrintStmt ;
class ForStmt ;
class WhileStmt ;

//Inherited from Expr
class VarName ;
class AnyConst ;
class BinOpExpr ;
class MatrixRefExpr ;
class FunctionCall ;
class ParensExpr ;
class LetExpr ;
class IfExpr ;
class NotExpr ;

/*! This is the super class. It's the base class for all nodes. Program, Stmt, Stmts, Decl, Decls, and Expr are all derived from this class.
 */
class Node {
    public:
    /*! This is a virtual method that returns unparse texts - commented out for now.
     
     virtual std::string unparse ( ) { return " This should be pure virtual ";} ;
     virtual std::string cppCode ( ) { return " This should be pure virtual" ; } ;
     */
    
    /*! This is the virtual destructor. This function deletes the node and deallocates space.
     */
    
    virtual std::string unparse ( ) = 0 ;
    virtual std::string cppCode ( ) { return " This should be pure virtual ";} ;
    virtual ~Node() { } ;
} ;

/*! This is an abstract non-terminal class for Program. It is inherited from the Node class.
 */
class Program : public Node {
    public:
    
    /* This constructor requires two parameters: the current variable name and a list of statements.
     \param *v the reference to the variable name in the Program, in 'VarName'
     \param *s the reference to the list of Statements in the Program, in 'Stmts'
     */
    Program(VarName *v, Stmts *s) {
        varName = v;
        stmts = s;
    };
    std::string unparse(),cppCode();
    
    private:
    VarName *varName;
    Stmts *stmts;
};

/*! This is an abstract non-terminal class for Stmt. It is inherited from the Node class.
 */
class Stmt : public Node {
};

/*! This is an abstract non-terminal class for Stmts. It is inherited from the Node class.
 */
class Stmts : public Node {
};


/*! This is an abstract class for EmptyStmts, which is a list of empty statements. It is inherited from the Stmts class.
 */
class EmptyStmts : public Stmts {
    public:
    EmptyStmts(){
    };
    
    std::string unparse(),cppCode();
};


/*! This is an abstract class for StmtStmts. It is inherited from the Stmts class.
 */
class StmtStmts : public Stmts {
    public:
    StmtStmts(Stmt *_stmt, Stmts *_stmts) {
        stmt = _stmt;
        stmts = _stmts;
    };
    std::string unparse(),cppCode();
    
    private:
    Stmt *stmt;
    Stmts *stmts;
};



/*! This is an abstract class for StandardDecl. It is inherited from the Stmt class.
 */

class StandardDecl : public Stmt {
    public:
    StandardDecl(std::string k, VarName *v) {
        type = k;
        varName = v;
    };
    std::string unparse(),cppCode();
    
    private:
    std::string type;
    VarName *varName;
};


/*!
 This is an abstract class for MatrixAdvDecl. It is inherited from the Stmt class.
 */
class MatrixAdvDecl : public Stmt {
    public:
    MatrixAdvDecl(VarName* v1, VarName* v2, VarName* v3, Expr* e1, Expr* e2, Expr* e3) {
        varName1 = v1;
        varName2 = v2;
        varName3 = v3;
        expr1 = e1;
        expr2 = e2;
        expr3 = e3;
    };
    
    std::string unparse(),cppCode();
    
    private:
    VarName *varName1;
    VarName *varName2;
    VarName *varName3;
    
    Expr* expr1;
    Expr* expr2;
    Expr* expr3;
};

/*! 
 This is an abstract class for MatrixDecl. It is inherited from the Stmt class.
 */
class MatrixDecl : public Stmt {
    public:
    MatrixDecl(VarName* v, Expr* e) {
        varName = v;
        expr = e;
    };
    std::string unparse(),cppCode();
    
    private:
    VarName *varName;
    Expr* expr;
};


/*! This is an abstract class for StmtBlock. It is inherited from the Stmt class.
 */
class StmtBlock: public Stmt{
    public:
    StmtBlock(Stmts* s) {
        stmts = s;
    };
    std::string unparse(),cppCode();
    
    private:
    Stmts* stmts;
} ;

/*!
 This is an abstract class for IfStmt. It is inherited from the Stmt class.
 */
class IfStmt : public Stmt {
    public:
    IfStmt(Expr* e, Stmt* s){
        expr = e;
        stmt = s;
    };
    std::string unparse(),cppCode();
    
    private:
    Expr* expr;
    Stmt* stmt;
};

/*!
 This is an abstract class for IfElseStmt. It is inherited from the Stmt class.
 */
class IfElseStmt : public Stmt {
    public:
    IfElseStmt(Expr* e, Stmt* s1, Stmt* s2) {
        expr = e;
        stmt1 = s1;
        stmt2 = s2;
    };
    std::string unparse(),cppCode();
    
    private:
    Expr* expr;
    Stmt* stmt1;
    Stmt* stmt2;
};

/*!
 This is an abstract class for StandardAssignStmt. It is inherited from the Stmt class.
 */
class StandardAssignStmt : public Stmt {
    public:
    StandardAssignStmt(VarName* v, Expr* e){
        varName = v;
        expr = e;
    };
    std::string unparse(),cppCode();
    
    private:
    VarName* varName;
    Expr* expr;
};

/*!
 This is an abstract class for MatrixAssignStmt. It is inherited from the Stmt class.
 */
class MatrixAssignStmt : public Stmt {
    public:
    MatrixAssignStmt(VarName* v, Expr* e1, Expr* e2, Expr* e3) {
        varName = v;
        expr1 = e1;
        expr2 = e2;
        expr3 = e3;
    };
    std::string unparse(),cppCode();
    
    private:
    VarName* varName;
    Expr* expr1;
    Expr* expr2;
    Expr* expr3;
};

/*!
 This is an abstract class for PrintStmt. It is inherited from the Stmt class.
 */
class PrintStmt : public Stmt{
     public:
     PrintStmt(Expr* e) {
         expr = e;
     };
     std::string unparse(),cppCode();
     
     private:
     Expr* expr;
 };

/*!
 This is an abstract class for ForStmt. It is inherited from the Stmt class.
 */
class ForStmt : public Stmt{
     public:
     ForStmt(VarName* v, Expr* e1, Expr* e2, Stmt* s) {
         varName = v;
         expr1 = e1;
         expr2 = e2;
         stmt = s;
     };
     std::string unparse(),cppCode();
     
     private:
     VarName* varName;
     Expr* expr1;
     Expr* expr2;
     Stmt* stmt;
 };

/*!
 This is an abstract class for WhileStmt. It is inherited from the Stmt class.
 */
class WhileStmt : public Stmt {
    public:
    WhileStmt(Expr* e, Stmt* s) {
        expr = e;
        stmt = s;
    };
    std::string unparse(),cppCode();
    
    private:
    Expr* expr;
    Stmt* stmt;
};

/*!
 This is an abstract class for Expr. It is inherited from the Node class.
 */
class Expr : public Node {
};


/*!
 This is an abstract class for varName. It is inherited from the Expr class.
 */
class VarName : public Expr {
    public:
    VarName(std::string s) {
        lexeme = s;
    };
    std::string unparse(),cppCode();
    
    private:
    std::string lexeme;
};

/*!
 This is an abstract class for AnyConst. It is inherited from the Expr class.
 */
class AnyConst : public Expr {
    public:
    AnyConst(std::string s){
        constStr = s;
    };
    std::string unparse(),cppCode();
    
    private:
    std::string constStr;
};

/*!
 This is an abstract class for BinOpExpr. It is inherited from the Expr class.
 */
class BinOpExpr : public Expr {
    public:
    BinOpExpr(Expr* l, std::string op, Expr* r): op(op) {
        left = l;
        right = r;
    } ;
    std::string unparse(),cppCode();
    
    private:
    Expr *left;
    std::string op;
    Expr *right;
};

/*!
 This is an abstract class for MatrixRefExpr. It is inherited from the Expr class.
 */
class MatrixRefExpr : public Expr {
    public:
    MatrixRefExpr(VarName* v, Expr* e1, Expr* e2) {
        varName = v;
        expr1 = e1;
        expr2 = e2;
    };
    std::string unparse(),cppCode();
    
    private:
    VarName* varName;
    Expr* expr1;
    Expr* expr2;
};

/*!
 This is an abstract class for FunctionCall. It is inherited from the Expr class.
 */
class FunctionCall : public Expr {
    public:
    FunctionCall(VarName* v, Expr* e) {
        varName = v;
        expr = e;
    };
    std::string unparse(), cppCode();
    
    private:
    VarName* varName;
    Expr* expr;
};

/*!
 This is an abstract class for ParensExpr. It is inherited from the Expr class.
 */
class ParensExpr : public Expr {
    public:
    ParensExpr(Expr* e) {
        expr = e;
    };
    std::string unparse(),cppCode();
    
    private:
    Expr* expr;
};

/*!
 This is an abstract class for LetExpr. It is inherited from the Expr class.
 */
class LetExpr : public Expr{
    public:
    LetExpr(Stmts* s, Expr* e) {
        stmts = s;
        expr = e;
    };
    std::string unparse(),cppCode();
    
    private:
    Stmts* stmts;
    Expr* expr;
};

/*!
 This is an abstract class for IfExpr. It is inherited from the Expr class.
 */
class IfExpr: public Expr{
    public:
    IfExpr(Expr* ex1, Expr* ex2, Expr* ex3) {
        expr1 = ex1;
        expr2 = ex2;
        expr3 = ex3;
    };
    std::string unparse(),cppCode();
    
    private:
    Expr* expr1;
    Expr* expr2;
    Expr* expr3;
};

/*!
 This is an abstract class for NotExpr. It is inherited from the Expr class.
 */
class NotExpr: public Expr{
    public:
    NotExpr(Expr* e) {
        expr = e;
    };
    std::string unparse(),cppCode();
    
    private:
    Expr* expr;
};

#endif