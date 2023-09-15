#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include "BasicMessage.h"
#include "ConfigEnv.h"
#include "iostream"
#include "Log.h"
#include "TimeDefaultBenchmark.h"
#include <regex>

TEST(BenchmarkOutputSuite, BenchmarkTerminalOutput) {
    BasicMessage* basicM = new BasicMessage(16);
    basicM->setLeftVel(100);
    basicM->setRightVel(50);
    Benchmark<BasicMessage*>* benchmark = new Benchmark<BasicMessage*>(basicM, 5);
    json ret = benchmark->execBenchmark();
    std::regex pattern("\\[\\d{2}:\\d{2}:\\d{2}\\] Stilt: \\{\\s*\"sended_messages\": \\d+\\s*\\}");
    
    EXPECT_GT(ret["sended_messages"], 0);
}

int main(int argc, char **argv) {
    Log::Init();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}