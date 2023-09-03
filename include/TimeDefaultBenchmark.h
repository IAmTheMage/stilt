#include "iostream"
#include "json.h"
#include "vector"
#include "Log.h"
#include <chrono>
#include <thread>
#include "OneMessageProducer.h"

using json = nlohmann::json;


#ifndef BENCHMARK_INCLUDE_H
#define BENCHMARK_INCLUDE_H

enum class SaveType {
    FILE = 0, CONSOLE = 1
};

const std::string SERVER_ADDRESS = "tcp://localhost:1883"; // Endereço do servidor MQTT
const std::string CLIENT_ID = "mqtt_publisher";
const std::string TOPIC = "begin_to_chime";

template<typename MessageType>
class Benchmark {
    public:
        Benchmark(MessageType _message, int _duration) {
            message = _message;
            duration = _duration;
        };
        ~Benchmark() {};
        
        void saveType(SaveType save) {
            _save = save;
        }

        virtual json execBenchmark() {
            auto startTime = std::chrono::high_resolution_clock::now();
            std::chrono::seconds durationTime(duration);
            STILT_INFO("Starting Benchmark for: {} seconds", duration);
            int iterations = 0;
            json pretty_info;
            OneMessageProducer<MessageType>* producer = new OneMessageProducer<MessageType>(SERVER_ADDRESS, CLIENT_ID, TOPIC, this->message);
            while (true) {
                iterations++;
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
                
                if (elapsed >= durationTime) {
                    break;
                }
                producer->send();
            }
            pretty_info["sended_messages"] = iterations;
            STILT_TRACE(pretty_info.dump(4));
            STILT_INFO("Finished benchmark");

            return pretty_info;
        };
        virtual void save() {};


        void setVerbose(bool _verbose) {
            verbose = _verbose;
        }


    protected:
        int duration;
        std::vector<double> times;
        SaveType _save;
        bool verbose;
        MessageType message;
};

#endif
