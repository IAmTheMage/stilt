#include "string"
#include "iostream"
#include "json.h"

using json = nlohmann::json;

#ifndef BASIC_MESSAGE_H
#define BASIC_MESSAGE_H

class BasicMessage {
    public:
        BasicMessage(int size) {
            this->size = size;
        };
        ~BasicMessage();

        

        virtual std::string to_string() {
            std::string composed;
            return composed;
        }

        friend std::ostream& operator<<(std::ostream& os, const BasicMessage& message) {
            os << "Total message size: " << message.size << "\n";
            return os;
        }

        operator json() const {
            json representation;
            representation["left_vel"] = this->left_vel;
            representation["right_vel"] = this->right_vel;
            return representation;
        }

        operator BasicMessage* () {
            return this;
        }

        operator BasicMessage () {
            return *this;
        }

        void setLeftVel(int left_vel) {
            this->left_vel = left_vel;
        }

        void setRightVel(int right_vel) {
            this->right_vel = right_vel;
        }


    protected:
        int size;
        int left_vel;
        int right_vel;
    private:
};

#endif