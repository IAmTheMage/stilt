#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include "BasicMessage.h"
#include "ConfigEnv.h"
#include "iostream"
#include "Log.h"
#include "Repeater.h"
#include <regex>

#define ALLOWED_FRAMES_MARGIN_SINGLE_THREAD 30 //Porcentagem de queda de frames que pode ter, no caso 25% de 80 = média minima de 56 frames
#define FPS 80
#define MAX_MESSAGE_QUEUE_SIZE 3
#define DURATION 10

TEST(Repeater, RepeaterRunning) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::chrono::seconds durationTime(DURATION);
    Repeater<BasicMessage*>* repeater = new Repeater<BasicMessage*>("tcp://localhost:1883", "mqtt_publisher", "begin_to_chime2", FPS, 3);
    repeater->startThread(ThreadSignature::SingleThread);

    int iterations = 0;

    while (true) {
        iterations++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        
        if (elapsed >= durationTime) {
            break;
        }
        
        int index = 3;
        while(index > 0) {
            BasicMessage* basicM = new BasicMessage(16);
            if(!(iterations % 5 == 0)) {
                basicM->setLeftVel(100);
                basicM->setRightVel(50);
            }
            else {
                basicM->setLeftVel(80);
                basicM->setRightVel(30);
            }
            repeater->addMessage(basicM);
            index--;
        }

        repeater->sendMessages();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    }
    int minimumSendedMessages = FPS * MAX_MESSAGE_QUEUE_SIZE * (100 - ALLOWED_FRAMES_MARGIN_SINGLE_THREAD) / 100 * DURATION;
    EXPECT_GE(repeater->getSendedMessages(), minimumSendedMessages);
    STILT_INFO("Numero enviado de mensagens = {}, numero minimo esperado: {}", repeater->getSendedMessages(), minimumSendedMessages);

}
