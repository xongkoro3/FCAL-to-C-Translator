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
bool suite_ScannerTestSuite_init = false;
#include "/Users/Chau/3081/group/repo-group-He-Nguyen/project/src/scanner_tests.h"

static ScannerTestSuite suite_ScannerTestSuite;

static CxxTest::List Tests_ScannerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ScannerTestSuite( "scanner_tests.h", 9, "ScannerTestSuite", suite_ScannerTestSuite, Tests_ScannerTestSuite );

static class TestDescription_suite_ScannerTestSuite_test_setup_code : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScannerTestSuite_test_setup_code() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 18, "test_setup_code" ) {}
 void runTest() { suite_ScannerTestSuite.test_setup_code(); }
} testDescription_suite_ScannerTestSuite_test_setup_code;

static class TestDescription_suite_ScannerTestSuite_test_scan_empty : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScannerTestSuite_test_scan_empty() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 329, "test_scan_empty" ) {}
 void runTest() { suite_ScannerTestSuite.test_scan_empty(); }
} testDescription_suite_ScannerTestSuite_test_scan_empty;

static class TestDescription_suite_ScannerTestSuite_test_scan_empty_comment : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScannerTestSuite_test_scan_empty_comment() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 336, "test_scan_empty_comment" ) {}
 void runTest() { suite_ScannerTestSuite.test_scan_empty_comment(); }
} testDescription_suite_ScannerTestSuite_test_scan_empty_comment;

static class TestDescription_suite_ScannerTestSuite_test_scan_lexicalErrors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScannerTestSuite_test_scan_lexicalErrors() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 345, "test_scan_lexicalErrors" ) {}
 void runTest() { suite_ScannerTestSuite.test_scan_lexicalErrors(); }
} testDescription_suite_ScannerTestSuite_test_scan_lexicalErrors;

static class TestDescription_suite_ScannerTestSuite_test_scan_nums_vars : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScannerTestSuite_test_scan_nums_vars() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 366, "test_scan_nums_vars" ) {}
 void runTest() { suite_ScannerTestSuite.test_scan_nums_vars(); }
} testDescription_suite_ScannerTestSuite_test_scan_nums_vars;

static class TestDescription_suite_ScannerTestSuite_test_scan_bad_syntax_good_tokens : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScannerTestSuite_test_scan_bad_syntax_good_tokens() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 380, "test_scan_bad_syntax_good_tokens" ) {}
 void runTest() { suite_ScannerTestSuite.test_scan_bad_syntax_good_tokens(); }
} testDescription_suite_ScannerTestSuite_test_scan_bad_syntax_good_tokens;

static class TestDescription_suite_ScannerTestSuite_test_scan_sample_forestLoss : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScannerTestSuite_test_scan_sample_forestLoss() : CxxTest::RealTestDescription( Tests_ScannerTestSuite, suiteDescription_ScannerTestSuite, 418, "test_scan_sample_forestLoss" ) {}
 void runTest() { suite_ScannerTestSuite.test_scan_sample_forestLoss(); }
} testDescription_suite_ScannerTestSuite_test_scan_sample_forestLoss;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
