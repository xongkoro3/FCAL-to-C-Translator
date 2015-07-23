#include "AST.h"

using namespace std ;

//Inherited from Node

string Program::unparse() {
    return varName->unparse() + " () {\n" + stmts->unparse() + "}\n";
}

string Program::cppCode() {
    string s = "#include <iostream>\n";
    s += "#include \"Matrix.h\"\n";
    s += "#include <math.h>\n";
    s += "\nusing namespace std;\n";
    s +="int " + varName->cppCode() + " () {\n" + stmts->cppCode() + "}\n";
    return s;
}

//Inherited from Stmts

string EmptyStmts::unparse() {
    return "";
}

string EmptyStmts::cppCode() {
    return "";
}

string StmtStmts::unparse() {
    return stmt->unparse() + stmts->unparse();
}

string StmtStmts::cppCode() {
    return stmt->cppCode() + stmts->cppCode();
}

//Inherited from Stmt

string StandardDecl::unparse() {
    return type + " " + varName->unparse() + ";\n";
}

string StandardDecl::cppCode() {
    string newKeyword;
    if(type.compare("Int")==0) {
        newKeyword = "int";
    }
    if(type.compare("Float")==0) {
        newKeyword = "float";
    }
    if(type.compare("Str")==0) {
        newKeyword = "string";
    }
    if(type.compare("Bool")==0) {
        newKeyword = "bool";
    }
    return newKeyword + " " + varName->cppCode() + ";\n";
}

string MatrixAdvDecl::unparse() {
    string s = "";
    s += "Matrix " + varName1->unparse() + " [ " + expr1->unparse() + "," + expr2->unparse() + "] ";
    s += varName2->unparse() + " , " + varName3->unparse() + " = " + expr3->unparse() + ";\n";
    return s;
}

string MatrixAdvDecl::cppCode() {
    string s = "";
    s += "Matrix " + varName1->cppCode() + " ( " + expr1->cppCode() + "," + expr2->cppCode() + ");\n ";

    s += "for(int " + varName2->cppCode() + "= 0 ; " + varName2->cppCode() + "<" + expr1->cppCode() + ";" + varName2->cppCode() + "++ ) { \n";
    s += "for(int " + varName3->cppCode() + "= 0 ; " + varName3->cppCode() + "<" + expr2->cppCode() + ";" + varName3->cppCode() + "++ ) { \n";
    s += "*(" + varName1->cppCode() + ".access(" + varName2->cppCode() + "," + varName3->cppCode() + " ))=" + expr3->cppCode() + "; \n" ;
    s += "} \n";
    s += "} \n";
    return s;
}

string MatrixDecl::unparse() {
    return "Matrix " + varName->unparse() + " = " + expr->unparse() + ";\n";
}

string MatrixDecl::cppCode() {
    return "Matrix " + varName->cppCode() + " (Matrix::" + expr->cppCode() + ");\n";
}

string StmtBlock::unparse() {
    return "{\n" + stmts->unparse() + "}";
}

string StmtBlock::cppCode() {
    return "{\n" + stmts->cppCode() + "}";
}

string IfStmt::unparse() {
    return "if ( " + expr->unparse() + " ) " + stmt->unparse();
}

string IfStmt::cppCode() {
    return "if ( " + expr->cppCode() + " ) " + stmt->cppCode();
}

string IfElseStmt::unparse() {
    string s = "";
    s+= "if (" + expr->unparse() + ") " + stmt1->unparse() + " else " + stmt2->unparse() + "\n";
    return s;
}

string IfElseStmt::cppCode() {
    string s = "";
    s+= "if (" + expr->cppCode() + ") " + stmt1->cppCode();
    s+= " else " + stmt2->cppCode() + "\n";
    return s;
}

string StandardAssignStmt::unparse() {
    return varName->unparse() + " = " + expr->unparse() + ";\n";
}

string StandardAssignStmt::cppCode() {
    return varName->cppCode() + " = " + expr->cppCode() + ";\n";
}

string MatrixAssignStmt::unparse() {
    return varName->unparse() + "[" + expr1->unparse() + "," + expr2->unparse() + "] = " + expr3->unparse() + ";\n" ;
}

string MatrixAssignStmt::cppCode() {
    return "*(" +varName->cppCode() + ".access(" + expr1->cppCode() + "," + expr2->cppCode() + ")) = " + expr3->cppCode() + ";\n ";
}

string PrintStmt::unparse() {
    return "print(" + expr->unparse() + ");\n";
}

string PrintStmt::cppCode() {
    return "cout << " + expr->cppCode() + " ;\n";
}

string ForStmt::unparse() {
    return "for(" + varName->unparse() + "=" + expr1->unparse() + " : " + expr2->unparse() + ")" + stmt->unparse() + "\n";
}

string ForStmt::cppCode() {
    return "for(" + varName->cppCode() + "=" + expr1->cppCode() + " ; " + varName->cppCode() + "<=" + expr2->cppCode() + ";" + varName->cppCode() + "++ )\n" + stmt->cppCode() + "\n";
}

string WhileStmt::unparse() {
    return "while(" + expr->unparse() + ")" + stmt->unparse() + "\n";
}

string WhileStmt::cppCode() {
    return "while(" + expr->cppCode() + ")" + "{\n" + stmt->cppCode() + "}" + "\n";
}

//Inherited from Expr

string VarName::unparse() {
    return lexeme;
}

string VarName::cppCode() {
    return lexeme;
}

string AnyConst::unparse() {
    return constStr;
}

string AnyConst::cppCode() {
    return constStr;
}

string BinOpExpr::unparse() {
    return left->unparse() + " " + op + " " + right->unparse();
}

string BinOpExpr::cppCode() {
    return left->cppCode() + " " + op + " " + right->cppCode();
}

string MatrixRefExpr::unparse() {
    return varName->unparse() + "[" + expr1->unparse() + "," + expr2->unparse() + "]";
}

string MatrixRefExpr::cppCode() {
    return "*(" + varName->cppCode() + ".access(" + expr1->cppCode() + "," + expr2->cppCode() + "))";
}

string FunctionCall::unparse() {
    return varName->unparse() + "(" + expr->unparse() + ")";
}

string FunctionCall::cppCode() {
	if(varName->cppCode().compare("readMatrix")==0) {
        return varName->cppCode() + "(" + expr->cppCode() + ")";

    } 
    else if(varName->cppCode().compare("numCols")==0) {
        return expr->cppCode() + "." + varName->cppCode() + "()";
    }

    else if(varName->cppCode().compare("numRows")==0) {
        return expr->cppCode() + "." + varName->cppCode() + "()";
	}        
               
    else{
        return varName->cppCode() + "(" + expr->cppCode() + ")";
    }
}

string ParensExpr::unparse() {
    return "(" + expr->unparse() + ")";
}

string ParensExpr::cppCode() {
    return "(" + expr->cppCode() + ")";
}

string LetExpr::unparse() {
    return "let " + stmts->unparse() + " in " + expr->unparse() + " end ";
}

string LetExpr::cppCode() {
    return "({ " + stmts->cppCode() + expr->cppCode() + ";" + "})";
}

string IfExpr::unparse() {
    return "if " + expr1->unparse() + " then " + expr2->unparse() + " else " + expr3->unparse();
}

string IfExpr::cppCode() {
    string s = "";
    s+= "(";
    s+= "(" + expr1->cppCode() + ") ? (" + expr2->cppCode() +"):";
    s+= expr3->cppCode();
    s+= ")";
    return s;
}

string NotExpr::unparse() {
    return "!" + expr->unparse();
}

string NotExpr::cppCode() {
    return "!" + expr->cppCode();
}
