#include "BasicMessage.h"
#include "string"

#ifndef CONFIG_MESSAGE_H
#define CONFIG_MESSAGE_H

class ConfigMessage : public BasicMessage {
    public:
        ConfigMessage(int size) : BasicMessage(size) {

        }

        ~ConfigMessage();

        std::string to_string() override {
            std::string composed;
            std::string str_size = std::to_string(size);
            composed.push_back(start);
            composed.append(str_size);
            composed.push_back(end);
            return composed;
        }
};

#endif