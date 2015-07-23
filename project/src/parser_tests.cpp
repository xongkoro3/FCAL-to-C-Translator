/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#define _CXXTEST_ABORT_TEST_ON_FAIL
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_ParserTestSuite_init = false;
#include "/Users/Chau/3081/group/repo-group-He-Nguyen/project/src/parser_tests.h"

static ParserTestSuite suite_ParserTestSuite;

static CxxTest::List Tests_ParserTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ParserTestSuite( "parser_tests.h", 13, "ParserTestSuite", suite_ParserTestSuite, Tests_ParserTestSuite );

static class TestDescription_suite_ParserTestSuite_test_setup_code : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_setup_code() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 18, "test_setup_code" ) {}
 void runTest() { suite_ParserTestSuite.test_setup_code(); }
} testDescription_suite_ParserTestSuite_test_setup_code;

static class TestDescription_suite_ParserTestSuite_test_parse_bad_syntax : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_bad_syntax() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 23, "test_parse_bad_syntax" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_bad_syntax(); }
} testDescription_suite_ParserTestSuite_test_parse_bad_syntax;

static class TestDescription_suite_ParserTestSuite_test_parse_sample_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_sample_1() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 30, "test_parse_sample_1" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_sample_1(); }
} testDescription_suite_ParserTestSuite_test_parse_sample_1;

static class TestDescription_suite_ParserTestSuite_test_parse_sample_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_sample_2() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 39, "test_parse_sample_2" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_sample_2(); }
} testDescription_suite_ParserTestSuite_test_parse_sample_2;

static class TestDescription_suite_ParserTestSuite_test_parse_sample_3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_sample_3() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 48, "test_parse_sample_3" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_sample_3(); }
} testDescription_suite_ParserTestSuite_test_parse_sample_3;

static class TestDescription_suite_ParserTestSuite_test_parse_sample_4 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_sample_4() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 57, "test_parse_sample_4" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_sample_4(); }
} testDescription_suite_ParserTestSuite_test_parse_sample_4;

static class TestDescription_suite_ParserTestSuite_test_parse_sample_5 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_sample_5() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 66, "test_parse_sample_5" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_sample_5(); }
} testDescription_suite_ParserTestSuite_test_parse_sample_5;

static class TestDescription_suite_ParserTestSuite_test_parse_mysample : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_mysample() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 75, "test_parse_mysample" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_mysample(); }
} testDescription_suite_ParserTestSuite_test_parse_mysample;

static class TestDescription_suite_ParserTestSuite_test_parse_forestLossV2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ParserTestSuite_test_parse_forestLossV2() : CxxTest::RealTestDescription( Tests_ParserTestSuite, suiteDescription_ParserTestSuite, 84, "test_parse_forestLossV2" ) {}
 void runTest() { suite_ParserTestSuite.test_parse_forestLossV2(); }
} testDescription_suite_ParserTestSuite_test_parse_forestLossV2;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
