#include <cxxtest/TestSuite.h>
#include "readInput.h"
#include "scanner.h"
#include "regex.h"
#include <stdio.h>

using namespace std ;

class ScannerTestSuite : public CxxTest::TestSuite 
{
public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    Scanner *s ;
    void test_setup_code ( ) {
        s = new Scanner() ;
    }
    

    // Tests for components and functions used by "scan"
    // --------------------------------------------------

    /* You may need to write several tests to adequately test the
       functions that are called from "scan".  Once you are confident
       that the components used by "scan" work properly, then you can
       run tests on the "scan" method itself.
    */

    // Here you should place tests for these other functions.


    /* Below is one of the tests for these components in the project
       solution created by your instructor..  It uses a helper
       function called "tokenMaker_tester", which you have
       not been given.  You are expected to design your own components
       for "scan" and your own mechanisms for easily testing them.

        void xtest_TokenMaker_leftCurly ( ) {
            tokenMaker_tester ("{ ", "^\\{", leftCurly, "{" ) ;
        }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
    */


    /* You must have at least one separate test case for each terminal
       symbol.  Thus, you need a test that will pass or fail based
       solely on the regular expression (and its corresponding code)
       for each terminal symbol.

       This requires a test case for each element of the enumerated
       type tokenType.  This may look something like the sample test
       shown in the comment above.
    */

//    void tokenMaker_tester(const char* sentence, tokenType assert_type, string assert_value) {
//        
//    }
//    
//    void test_terminal_intKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(intKwd,"string " , "int"),false);
//    }
//
//    void test_terminal_floatKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(floatKwd,"Float " , "Float"),true);
//    }
//    
//    void test_terminal_boolKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(boolKwd,"Bool " , "Bool"),true);
//    }
//    
//    void test_terminal_trueKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(trueKwd,"True " , "true"),true);
//    }
//    
//    void test_terminal_falseKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(falseKwd,"False " , "False"),true);
//    }
//    
//    void test_terminal_stringKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(stringKwd,"String " , "String"),true);
//    }
//    
//    void test_terminal_matrixKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(matrixKwd,"Matrix " , "Matrix"),true);
//    }
//    
//    void test_terminal_letKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(letKwd,"let " , "let"),true);
//    }
//    
//    void test_terminal_inKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(inKwd,"in " , "in"),true);
//    }
//    
//    void test_terminal_endKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(endKwd,"end " , "end"),true);
//    }
//    
//    void test_terminal_ifKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(ifKwd,"if " , "if"),true);
//    }
//    
//    void test_terminal_thenKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(thenKwd,"then " , "then"),true);
//    }
//
//    void test_terminal_elseKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(elseKwd,"else " , "else"),true);
//    }
//    
//    void test_terminal_forKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(forKwd,"for " , "for"),true);
//    }
//    
//    void test_terminal_whileKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(whileKwd,"while " , "while"),true);
//    }
//    
//    void test_terminal_printKwd() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(printKwd,"print " , "print"),true);
//    }
// 
//
//    //Tests for Constants tokenType
//    
//    void test_terminal_intConst() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(intConst,"123 " , "123"),true);
//    }
//
//    void test_terminal_floatConst() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(floatConst,"0.135 ",  "0.135"), true);
//    }
//
//    void test_terminal_stringConst() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(stringConst,"\"stringConstant\" ",  "\"stringConstant\""), true);
//    }
//
//    //Tests for Names tokenType
//    
//    void test_terminal_variableName() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(variableName,"varname ",  "varname"), true);
//    }
//
//    //Tests for Punctuation tokenType
//
//    void test_terminal_leftParen() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(leftParen,"( ",  "("), true);
//    }
//    
//
//    void test_terminal_rightParen() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(rightParen,") ",  ")"), true);
//    }
//    
//    void test_terminal_leftCurly() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(leftCurly,"{ ",  "{"), true);
//    }
//    
//    void test_terminal_rightCurly() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(rightCurly,"} ",  "}"), true);
//    }
//    
//    void test_terminal_leftSquare() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(leftSquare,"[ ",  "["), true);
//    }
//    
//    void test_terminal_rightSquare() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(rightSquare,"] ",  "]"), true);
//    }
//    
//    void test_terminal_comma() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(comma,":: ",  ","), false);
//    }
//    
//    void test_terminal_semiColon() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(semiColon,": ",  ";"), false);
//    }
//    
//    void test_terminal_colon() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(colon,": ",  ":"), true);
//    }
//    
//    //Tests for Operators tokenType
//    
//    void test_terminal_assign() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(assign,"= ",  "="), true);
//    }
//    
//    void test_terminal_plusSign() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(plusSign,"* ",  "+"), false);
//    }
//    
//    void test_terminal_star() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(star,"* ",  "*"), true);
//    }
//    
//    void test_terminal_dash() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(dash,"- ",  "-"), true);
//    }
//    
//    void test_terminal_forwardSlash() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(forwardSlash,"/ ",  "/"), true);
//    }
//    
//    void test_terminal_lessThan() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(lessThan,"> ",  "<"), false);
//    }
//    
//    void test_terminal_lessThanEqual() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(lessThanEqual,"<= ",  "<="), true);
//    }
//    
//    void test_terminal_greaterThan() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(greaterThan,"> ",  ">"), true);
//    }
//    
//    void test_terminal_greaterThanEqual() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(greaterThanEqual,">= ",  ">="), true);
//    }
//    
//    void test_terminal_equalsEquals () {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(equalsEquals,": ",  "=="), false);
//    }
//    
//    void test_terminal_notEquals() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(notEquals, "!= ", "!="), true);
//    }
//    
//    void test_terminal_andOp() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(andOp,"& ",  "&&"), false);
//    }
//    
//    void test_terminal_orOp() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(orOp, "| ", "||"), false);
//    }
//    
//    void test_terminal_notOp() {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(notOp, "? ", "!"), false);
//    }
    
//    //Tests for Special terminal types tokenType
//    
//    void test_terminal_endOfFile () {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(endOfFile, " ", ""), true);
//    }
//    
//    void test_terminal_lexicalError () {
//        TS_ASSERT_EQUALS(s->tokenMaker_bool(lexicalError, "$$ ", "$"),true);
//    }
    



    // Tests for "scan"
    // --------------------------------------------------

    /* Below are some helper functions and sample tests for testing the 
       "scan" method on Scanner.
    */

    // Test that a list of tokens has no lexicalError tokens.
    bool noLexicalErrors (Token *tks) {
        Token *currentToken = tks ;
        while (currentToken != NULL) {
            if (currentToken->terminal == lexicalError) {
                printf("priblem: %s\n",currentToken->lexeme.c_str());
				return false ;
            }
            else {
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned. 
    */
    void scanFileNoLexicalErrors ( const char* filename ) {
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT (noLexicalErrors(tks));
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminals (Token *tks, int numTerms, tokenType *ts) {
        Token *currentToken = tks ;
        int termIndex = 0 ;
        while (currentToken != NULL && termIndex < numTerms ) {
            if (currentToken->terminal != ts[termIndex]) {
            printf("%i: %i should be %i\n",termIndex,currentToken->terminal , ts[termIndex]);
			fflush(stdout);
                return false ;
            }
            else {
                ++ termIndex ;
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }


    /* Below are the provided test files that your code should also
       pass.

       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.

    */

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_scan_empty ( ) {
        Token *tks = s->scan ("  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    void test_scan_empty_comment ( ) {
        Token *tks = s->scan (" /* a comment */ ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    // When a lexical error occurs, the scanner creates a token with a 
    // single-character lexeme and lexicalError as the terminal.
   void test_scan_lexicalErrors ( ) {
        Token *tks = s->scan ("$&1  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "$");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "&");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, intConst) ;
        TS_ASSERT_EQUALS (tks->lexeme, "1");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }


    // A test for scanning numbers and a variable.
    void test_scan_nums_vars ( ) {
        Token *tks = s->scan (" 123 x 12.34 ") ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { intConst, variableName, floatConst, endOfFile } ;
        TS_ASSERT ( sameTerminals ( tks, 4, ts ) ) ;
    }



    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexeme
       are correct.
     */
    
    void test_scan_bad_syntax_good_tokens ( ) {
        const char *filename = "../samples/bad_syntax_good_tokens.dsl" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
            intConst, intConst, intConst, intConst, 

            stringConst, stringConst, stringConst,

            floatConst, floatConst, floatConst,

                   matrixKwd,



            semiColon, comma, colon,
            leftCurly, leftParen, rightCurly, rightParen,

            plusSign, star, dash, forwardSlash, 

            equalsEquals, lessThanEqual, 
            greaterThanEqual, notEquals, 
            assign,

            variableName, variableName, variableName, variableName, 
            variableName, variableName, variableName,


            intKwd, floatKwd,  stringKwd,  whileKwd,

            endOfFile
       } ;
        int count = 39; 
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }

    void test_scan_sample_forestLoss ( ) {
        scanFileNoLexicalErrors ("../samples/forest_loss_v2.dsl") ;
    }

      

} ;
