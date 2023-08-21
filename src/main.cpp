#include "BasicMessage.h"
#include "ConfigEnv.h"
#include "iostream"
#include "Log.h"
#include "TimeDefaultBenchmark.h"



int main(int argc, char const *argv[])
{
    Log::Init();
    BasicMessage* basicM = new BasicMessage(16);
    basicM->setLeftVel(100);
    basicM->setRightVel(50);
    Benchmark<BasicMessage*>* benchmark = new Benchmark<BasicMessage*>(basicM, 5);
    benchmark->execBenchmark();
    return 0;
}
