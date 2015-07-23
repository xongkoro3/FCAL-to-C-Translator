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
bool suite_CodeGenTestSuite_init = false;
#include "/Users/Chau/3081/group/repo-group-He-Nguyen/project/src/codegeneration_tests.h"

static CodeGenTestSuite suite_CodeGenTestSuite;

static CxxTest::List Tests_CodeGenTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CodeGenTestSuite( "codegeneration_tests.h", 11, "CodeGenTestSuite", suite_CodeGenTestSuite, Tests_CodeGenTestSuite );

static class TestDescription_suite_CodeGenTestSuite_test_sample_4 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_sample_4() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 89, "test_sample_4" ) {}
 void runTest() { suite_CodeGenTestSuite.test_sample_4(); }
} testDescription_suite_CodeGenTestSuite_test_sample_4;

static class TestDescription_suite_CodeGenTestSuite_test_sample_5 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_sample_5() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 90, "test_sample_5" ) {}
 void runTest() { suite_CodeGenTestSuite.test_sample_5(); }
} testDescription_suite_CodeGenTestSuite_test_sample_5;

static class TestDescription_suite_CodeGenTestSuite_test_sample_6 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_sample_6() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 91, "test_sample_6" ) {}
 void runTest() { suite_CodeGenTestSuite.test_sample_6(); }
} testDescription_suite_CodeGenTestSuite_test_sample_6;

static class TestDescription_suite_CodeGenTestSuite_test_sample_7 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_sample_7() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 92, "test_sample_7" ) {}
 void runTest() { suite_CodeGenTestSuite.test_sample_7(); }
} testDescription_suite_CodeGenTestSuite_test_sample_7;

static class TestDescription_suite_CodeGenTestSuite_test_sample_8 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_sample_8() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 93, "test_sample_8" ) {}
 void runTest() { suite_CodeGenTestSuite.test_sample_8(); }
} testDescription_suite_CodeGenTestSuite_test_sample_8;

static class TestDescription_suite_CodeGenTestSuite_test_my_code_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_my_code_1() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 98, "test_my_code_1" ) {}
 void runTest() { suite_CodeGenTestSuite.test_my_code_1(); }
} testDescription_suite_CodeGenTestSuite_test_my_code_1;

static class TestDescription_suite_CodeGenTestSuite_test_my_code_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_my_code_2() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 99, "test_my_code_2" ) {}
 void runTest() { suite_CodeGenTestSuite.test_my_code_2(); }
} testDescription_suite_CodeGenTestSuite_test_my_code_2;

static class TestDescription_suite_CodeGenTestSuite_test_forest_loss : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CodeGenTestSuite_test_forest_loss() : CxxTest::RealTestDescription( Tests_CodeGenTestSuite, suiteDescription_CodeGenTestSuite, 101, "test_forest_loss" ) {}
 void runTest() { suite_CodeGenTestSuite.test_forest_loss(); }
} testDescription_suite_CodeGenTestSuite_test_forest_loss;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
