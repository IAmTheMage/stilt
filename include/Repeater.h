#include "mutex"
#include "BasicMessage.h"
#include "queue"
#include "OneMessageProducer.h"
#include "Log.h"
#include "thread"

#ifndef REPEATER_H
#define REPEATER_H

enum class ThreadSignature {
    SingleThread = 0, MultiThread = 1, Auto = 2
};

enum class LimitBreakAction {
    Ignore = 0, Pop = 1
};



// ... Outros includes ...

template<typename MessageType>
class Repeater {

    public:
        Repeater(std::string server, std::string clientId, std::string topic, int fps, int messageLimit = 3, 
        LimitBreakAction breakAction = LimitBreakAction::Ignore, bool withBson = false) :
            Server(server), ClientId(clientId), Topic(topic), fps(fps), isRunning(true), messageLimit(messageLimit), 
            breakAction(breakAction) {
                this->producer = new OneMessageProducer<MessageType>(Server, ClientId, Topic, NULL, withBson);
        }

        ~Repeater() {
            stopThread();
        }

        void startThread(ThreadSignature signature) {

            if(signature == ThreadSignature::SingleThread) {
                STILT_INFO("Communcation started, SingleThreadMode, with limit of messages: {}", messageLimit);
            }
            else if(signature == ThreadSignature::MultiThread) {
                
            }
            else {

            }
        }

        void stopThread() {
            if (repeaterThread.joinable()) {
                isRunning = false;
                cv.notify_all(); // Notifica a thread para encerrar
                repeaterThread.join();
            }
        }

        void sendMessages() {
            while (!sendingQueue.empty()) {
                MessageType message = sendingQueue.front();
                sendingQueue.pop();
                producer->setMessage(message);
                producer->send();
                sendedMessages++;
            }
        }

        int getSendedMessages() { return this->sendedMessages; }

        void runThread() {
            
        }

        void addMessage(const MessageType& message) {
            std::lock_guard<std::mutex> lock(queueMutex);
            if(sendingQueue.size() == messageLimit) {
                if(breakAction == LimitBreakAction::Pop) {
                    sendingQueue.pop();
                    sendingQueue.push(message);
                }
            }
            else {
                sendingQueue.push(message);
            }
            cv.notify_one(); // Notifica a thread para processar mensagens
        }

    private:
        std::queue<MessageType> sendingQueue;
        bool isRunning;
        std::thread repeaterThread;

        std::string Server;
        std::string ClientId;
        int fps;
        int messageLimit;
        std::string Topic;

        std::mutex threadMutex;  // Mutex para proteger a thread e a condição
        std::mutex queueMutex;   // Mutex para proteger a fila sendingQueue
        std::condition_variable cv; // Variável de condição para sincronização
        LimitBreakAction breakAction;
        OneMessageProducer<MessageType>* producer;

        int sendedMessages = 0;
};


#endif