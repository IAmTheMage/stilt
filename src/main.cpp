#include "BasicMessage.h"
#include "ConfigEnv.h"
#include "iostream"

int main(int argc, char const *argv[])
{
    BasicMessage* basicM = new BasicMessage('<', '>', 16);
    ConfigEnv<BasicMessage*>* configEnv = new ConfigEnv<BasicMessage*>(basicM);
    std::cout << *configEnv << std::endl;

    BasicMessage* message = configEnv->getFormerObject();
    std::cout << *message << std::endl;
    return 0;
}
