/**
 * @file main.cpp
 * @Brief 
 * @author Red Li
 * @version 
 * @date 2014-12-19
 */

#include <memory>
#include <vector>
#include <stdio.h>
#include <windows.h>

#include <gtest/gtest.h>

namespace testing{




class BenchmarkPrinter : public EmptyTestEventListener
{
    virtual void OnTestProgramStart(const UnitTest &ut)
    {
        fprintf(stdout, "[==========] Running %d test from %d test case\n", 
                ut.test_to_run_count(), ut.total_test_count());
    }

    virtual void OnEnvironmentsSetUpEnd(const UnitTest& /*unit_test*/)
    {
        fprintf(stderr, "[----------] Global test environment set-up\n");
    }

    virtual void OnEnvironmentsTearDownEnd(const UnitTest& /*unit_test*/)
    {
        fprintf(stderr, "[----------] Global test environment tear-down\n");
    }
    
    virtual void OnTestCaseStart(const TestCase& tc)
    {
        fprintf(stderr, "[----------] %d test from %s",
                tc.test_to_run_count(), tc.name());
        if(tc.type_param())
            fprintf(stderr, ", TypeParam = %s", tc.type_param());
        fprintf(stderr, "\n");
    }

    virtual void OnTestCaseEnd(const TestCase& tc)
    {
        fprintf(stderr, "[----------] %d test from %s (%d ms total)\n",
                tc.test_to_run_count(), tc.name(), tc.elapsed_time());
    }

    virtual void OnTestStart(const TestInfo& ti)
    {
        fprintf(stderr, "[ RUN      ] %s", ti.name());
        if(ti.value_param())
            fprintf(stderr, ", ValueParam = %s", ti.value_param());
        fprintf(stderr, "\n");
    }

    virtual void OnTestEnd(const TestInfo &ti)
    {
        auto result = ti.result();
        const char *benchCountStr = 0,
                   *benchCountUnitStr = 0;

        for(int i = 0; i < result->test_property_count(); ++i){
            auto &p = result->GetTestProperty(i);
            if(p.key() == std::string("BenchCount")){
                benchCountStr = p.value();
            }
            else if(p.key() == std::string("BenchCountUnit")){
                benchCountUnitStr = p.value();
            }
        }

        if(!benchCountUnitStr)
            benchCountUnitStr = "";

        int benchCount = 0;
        if(benchCountStr){
            std::stringstream ss(benchCountStr);
            ss >> benchCount;

            auto ms = result->elapsed_time();
            double v = benchCount * 1000. / (ms ? ms : 1);
            printf("[ RESULT   ] %s %.3lf %s/s\n", ti.name(), v, benchCountUnitStr); 
        }
    }
};

}




int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    
    auto &listeners = ::testing::UnitTest::GetInstance()->listeners();

    delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new ::testing::BenchmarkPrinter);

    return RUN_ALL_TESTS();
}
