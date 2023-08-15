#include "BasicMessageTrait.h"
#include "iostream"

#include "memory"

#ifndef CONFIG_ENV_H
#define CONFIG_ENV_H

template<typename MessageType>
class ConfigEnv {
    public:

        static_assert(InheritsFromBasicMessage<MessageType>::value, "MessageType must inherit from BasicMessage");


        ConfigEnv(MessageType _data) {
            this->data = std::make_shared<MessageType>(_data);
            this->_object = static_cast<BasicMessage*>(_data);
        }

        ~ConfigEnv() {};

        void setMessageBody() {

        }

        std::shared_ptr<MessageType> getData() const {
            return this->data;
        }

        friend std::ostream& operator<<(std::ostream& os, const ConfigEnv& env) {
            std::shared_ptr<MessageType> converted = env.getData();
            os << **converted << "\n";
            return os;
        }

        BasicMessage* getFormerObject() {
            return this->_object;
        }

        

    private:
        std::shared_ptr<MessageType> data;
        BasicMessage* _object;
};

#endif