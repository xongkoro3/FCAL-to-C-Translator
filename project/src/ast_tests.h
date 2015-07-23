#include <cxxtest/TestSuite.h>
#include <iostream>
#include "parser.h"
#include "readInput.h"

#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std ;

/*! This is the base class for the AST tests. Embedded in this class are helper test methods makeArgs, writeFile, readFile, unparse_tests, as well as 7 AST tests.
 */
class AstTestSuite : public CxxTest::TestSuite
{
public:
    
    Parser p ;
    ParseResult pr ;
    
    /*! This is a method to generate arguments from inputted texts from the file. It requires two parameters: the first character which is a phrase from the text file, and the second character (initially empty) used to store the first phrase.
     
     \param *a0 reference to a character from the inputted text file, in 'char'
     \param *a1 reference to a second character, that's used to store the content of the first string, in 'char'
     */
    char **makeArgs ( const char *a0, const char *a1) {
        char **aa = (char **) malloc (sizeof(char *) * 2) ;
        aa[0] = (char *) malloc ( sizeof(char) * (strlen(a0) + 1) ) ;
        strcpy (aa[0], a0 ) ;
        aa[1] = (char *) malloc ( sizeof(char) * (strlen(a1) + 1) ) ;
        strcpy (aa[1], a1 ) ;
        return aa ;
    }
    
    /*! This is a method to write the content of the file out to the terminal. It requires two parameters: a string of text, and the file name.
     
     \param text a string of text from the file, in 'string'
     \param filename the name of the file we're writing from, in 'string'
     */
    void writeFile ( const string text, const string filename ) {
        ofstream out(filename.c_str());
        out << (string) text << endl ;
    }
    
    /*! This is a method to read input from a given file. It requires one parameter: a string of text to store the content read from the file.
     
     \param *fn reference to a character that's used to store the content read from the file, in 'char'
     */
    char *readFile ( const char *fn ) {
        return readInput (2, makeArgs("translator", fn) ) ;
    }
    
    
    /*! This is a method to unparse the content of a file and compare it to the expected result. It requires one parameter: the file name.
     
     \param file the name of the file to be unparsed, in 'string'
     */
    void unparse_tests ( string file ) {
        string path = "../samples/" + file ;
        
        // 1. Test that the file can be parsed.
        ParseResult pr1 = p.parse (
                                   readInput (2, makeArgs("translator", path.c_str() ) )
                                   ) ;
        TSM_ASSERT ( file + " failed to parse.", pr1.ok ) ;
        
        // 2. Verify that the ast field is not null
        TSM_ASSERT ( file + " failed to generate an AST.", pr1.ast != NULL );
        
        // 3. Verify that the "unparsing" is non-empty.
        string up1 = pr1.ast->unparse() ;
        writeFile(up1,(path+"up1").c_str());
        TSM_ASSERT ( file + " failed to generate non-empty unparsing.",
                    up1.length() > 0 ) ;
        
        // 4. Verify that the un-parsed string can be parsed.
        ParseResult pr2 = p.parse ( up1.c_str() ) ;
        TSM_ASSERT ( file + " failed to parse the first un-parsing.",
                    pr2.ok ) ;
        
        // 5. Verify that the ast field is not null after first unparsing
        TSM_ASSERT ( file + " first unparsing failed to generate an AST.",
                    pr2.ast != NULL );
        
        // 6. Verify that this second unparsing can be parsed.
        string up2 = pr2.ast->unparse() ;
        writeFile(up2,(path+"up2").c_str());
        ParseResult pr3 = p.parse ( up2.c_str() ) ;
        TSM_ASSERT ( file + " failed to pares the second un-parsing.",
                    pr3.ok ) ;
        
        string up3 = pr3.ast->unparse() ;
        writeFile(up3,(path+"up3").c_str());
        // 7. Verify that the first and second unparsings are the same.
        TSM_ASSERT_EQUALS ( file + " unparse-1 != unparse-2.", up1, up2 ) ;
        // 8. Verifty that the second and third unparsings are the same.
        TSM_ASSERT_EQUALS ( file + " unparse-2 != unparse-3.", up2, up3 ) ;
    }


/*! This is a method to compare the unparsed content of the "sample_1.dsl" file in the FCAL language to the expected result. It requires one parameter: the unparsed content of "sample_1.dsl"
 
 \param unparse_tests("sample_1.dsl") the unparsed content of the "sample_1.dsl" file
 */
void test_sample_1 ( void ) { unparse_tests ( "sample_1.dsl" ); }


/*! This is a method to compare the unparsed content of the "sample_2.dsl" file in the FCAL language to the expected result. It requires one parameter: the unparsed content of "sample_2.dsl"
 
 \param unparse_tests("sample_2.dsl") the unparsed content of the "sample_2.dsl" file
 */
void test_sample_2 ( void ) { unparse_tests ( "sample_2.dsl" ); }


/*! This is a method to compare the unparsed content of the "sample_3.dsl" file in the FCAL language to the expected result. It requires one parameter: the unparsed content of "sample_3.dsl"
 
 \param unparse_tests("sample_3.dsl") the unparsed content of the "sample_3.dsl" file
 */
void test_sample_3 ( void ) { unparse_tests ( "sample_3.dsl" ); }


/*! This is a method to compare the unparsed content of the "sample_4.dsl" file in the FCAL language to the expected result. It requires one parameter: the unparsed content of "sample_4.dsl"
 
 \param unparse_tests("sample_4.dsl") the unparsed content of the "sample_1.dsl" file
 */
void test_sample_4 ( void ) { unparse_tests ( "sample_4.dsl" ); }


/*! This is a method to compare the unparsed content of the "sample_5.dsl" file in the FCAL language to the expected result. It requires one parameter: the unparsed content of "sample_5.dsl"
 
 \param unparse_tests("sample_5.dsl") the unparsed content of the "sample_5.dsl" file
 */
void test_sample_5 ( void ) { unparse_tests ( "sample_5.dsl" ); }


/*! This is a method to compare the unparsed content of the "mysample.dsl" file in the FCAL language to the expected result. It requires one parameter: the unparsed content of "mysample.dsl"
 
 \param unparse_tests("mysample.dsl") the unparsed content of the "mysample.dsl" file
 */
void test_mysample ( void ) { unparse_tests ( "mysample.dsl" ); }


/*! This is a method to compare the unparsed content of the "forest_loss_v2.dsl" file in the FCAL language to the expected result. It requires one parameter: the unparsed content of "forest_loss_v2.dsl"
 
 \param unparse_tests("forest_loss_v2.dsl") the unparsed content of the "forest_loss_v2.dsl" file
 */
void test_forest_loss ( void ) { unparse_tests ( "forest_loss_v2.dsl" ); }
} ;