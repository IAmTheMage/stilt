#include "mutex"
#include "BasicMessage.h"
#include "queue"
#include "OneMessageProducer.h"
#include "Log.h"
#include "thread"

#ifndef REPEATER_H
#define REPEATER_H

template<typename MessageType>
class Repeater {

    public:
        Repeater(std::string server, std::string clientId, std::string topic) {
            this->Server = server;
            this->ClientId = clientId;
            this->Topic = topic;
        }
        ~Repeater() {

        }

        void startThread() {
            this->repeaterThread = std::thread(&Repeater::runThread, this);
        }

        void runThread() {
            OneMessageProducer<MessageType>* producer = 
            new OneMessageProducer<MessageType>(Server, 
            ClientId, Topic, NULL);
            while(isRunning) {
                while(sendingQueue.empty() == false) {
                    producer->setMessage(sendingQueue.front());
                    sendingQueue.pop();
                    producer->send();
                    
                }
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            this->repeaterThread.join();
        }

        void addMessage(const MessageType& message) {
            sendingQueue.push(message);
        }

    private:
        std::queue<MessageType> sendingQueue;
        bool is_modified = false;
        bool isRunning = true;
        std::thread repeaterThread;

        std::string Server;
        std::string ClientId;
        std::string Topic;

};

#endif