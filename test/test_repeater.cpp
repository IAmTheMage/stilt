#include <gtest/gtest.h>
#include <gtest/internal/gtest-internal.h>
#include "BasicMessage.h"
#include "ConfigEnv.h"
#include "iostream"
#include "Log.h"
#include "Repeater.h"
#include <regex>

TEST(Repeater, RepeaterRunning) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::chrono::seconds durationTime(20);
    Repeater<BasicMessage*>* repeater = new Repeater<BasicMessage*>("tcp://localhost:1883", "mqtt_publisher", "begin_to_chime");
    repeater->startThread();

    int iterations = 0;

    while (true) {
        iterations++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        
        if (elapsed >= durationTime) {
            break;
        }
        
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
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
