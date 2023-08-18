#include "string"
#include "iostream"
#include "json.h"

using json = nlohmann::json;

#ifndef BASIC_MESSAGE_H
#define BASIC_MESSAGE_H

class BasicMessage {
    public:
        BasicMessage(char start, char end, int size) {
            this->start = start;
            this->end = end;
            this->size = size;
        };
        ~BasicMessage();

        

        virtual std::string to_string() {
            std::string composed;
            composed.push_back(start);
            composed.push_back(end);
            return composed;
        }

        friend std::ostream& operator<<(std::ostream& os, const BasicMessage& message) {
            os << "Total message size: " << message.size << "\n" << "Start operator: " << message.start << "\n" << "End operator: " << message.end << "\n";
            return os;
        }

        void externalJsonConverter(json (*externalJsonParser)(std::string data)) {

        }

        virtual json internalJsonConverter() {
            representation["start"] = "<";
            representation["end"] = ">";
            representation["size"] = 16;
        }

        operator BasicMessage* () {
            return this;
        }

        operator BasicMessage () {
            return *this;
        }

        char getStartChar() {
            return start;
        }

        char getEndChar() {
            return end;
        }

        virtual json getJsonRepresentation() {
            return representation;
        }

    protected:
        char start;
        char end;
        int size;


    
    private:
        json representation;
};

#endif