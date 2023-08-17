#include "Log.h"
#include <mqtt/async_client.h>

#ifndef ONE_MESSAGE_PRODUCER_H
#define ONE_MESSAGE_PRODUCER_H

class OneMessageProducer {
    public:
        OneMessageProducer();
        ~OneMessageProducer();
    
    private:
        std::string serverAddress;
        std::string clientId;
};

#endif