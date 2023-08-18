#include "BasicMessage.h"
#include "ConfigEnv.h"
#include "iostream"
#include "Log.h"
#include "OneMessageProducer.h"

const std::string SERVER_ADDRESS = "tcp://localhost:1883"; // Endereço do servidor MQTT
const std::string CLIENT_ID = "mqtt_publisher";
const std::string TOPIC = "begin_to_chime";

int main(int argc, char const *argv[])
{
    Log::Init();
    BasicMessage* basicM = new BasicMessage('<', '>', 16);
    ConfigEnv<BasicMessage*>* configEnv = new ConfigEnv<BasicMessage*>(basicM);
    std::cout << *configEnv << std::endl;

    BasicMessage* message = configEnv->getFormerObject();
    std::cout << *message << std::endl;

    OneMessageProducer<BasicMessage*>* one = new OneMessageProducer<BasicMessage*>(SERVER_ADDRESS, CLIENT_ID, TOPIC, basicM);
    one->send();
    return 0;
}
