#include "Log.h"
#include <mqtt/async_client.h>
#include "HasBasicMessageOperator.h"
#include "BasicMessageTrait.h"
#include "Log.h"
#include <stdexcept>
#include <mutex>
#include "thread"
#include "vector"


#ifndef ONE_MESSAGE_PRODUCER_H
#define ONE_MESSAGE_PRODUCER_H


template<typename MessageType>
class OneMessageProducer {
    public:
        OneMessageProducer(std::string server_address, std::string client_id, std::string topic, MessageType message, bool withBson = false) : client(server_address, client_id) {
            bool inherits = std::is_base_of<BasicMessage, MessageType>::value;
            bool is_same = std::is_same<BasicMessage, MessageType>::value;
            bool inherits_2 = std::is_base_of<BasicMessage*, MessageType>::value;
            bool is_same_2 = std::is_same<BasicMessage*, MessageType>::value;
            if(!inherits && !is_same && !inherits_2 && !is_same_2) {
                STILT_CRITICAL("Critical: Class must be inherits from Basic Message or Basic Message itself");
                throw std::runtime_error("");
            }
            bool has_operator = has_cast_operator<MessageType>::value;
            if(!has_operator) {
                STILT_CRITICAL("The class needs to implement the cast operator for BasicMessage");
            }

            this->topic = topic;
            this->serverAddress = server_address;
            this->clientId = client_id;
            this->message = message;
            //SimpleCallback callback;
            //client.set_callback(callback);

            this->withBson = withBson;

            // Configurar as opções de conexão
            mqtt::connect_options connOpts;
            connOpts.set_clean_session(false);
            try {
                // Conectar-se ao broker MQTT
                mqtt::token_ptr conntok = client.connect(connOpts);
                conntok->wait();
            }
            catch (const mqtt::exception& exc) {
                std::cerr << "Erro MQTT: " << exc.what() << std::endl;
            }
        }

        void send() {
            if(withBson) {
                BasicMessage* basicM = this->message;
                json representation = *basicM;
                
                std::vector<std::uint8_t> bsonArray = nlohmann::json::to_bson(representation);
                std::string str(reinterpret_cast<char*>(bsonArray.data()), bsonArray.size());
                mqtt::message_ptr pubmsg = mqtt::make_message(this->topic, reinterpret_cast<const void*>(bsonArray.data()), bsonArray.size());
                pubmsg->set_qos(1); // Qualidade de serviço (QoS) 1 - pelo menos uma vez

                mqtt::token_ptr pubtok = client.publish(pubmsg);
                pubtok->wait(); // Publicar a mensagem
            }
            else {
                BasicMessage* basicM = this->message;
                json representation = *basicM;
                
                mqtt::message_ptr pubmsg = mqtt::make_message(this->topic, representation.dump(4));
                pubmsg->set_qos(1); // Qualidade de serviço (QoS) 1 - pelo menos uma vez

                mqtt::token_ptr pubtok = client.publish(pubmsg);
                pubtok->wait(); // Publicar a mensagem
            }
        }


        ~OneMessageProducer() {
            client.disconnect();
        };

        void setMessage(MessageType _message) {
            this->message = _message;
        }
    
    private:
        mqtt::async_client client;
        MessageType message;
        std::string serverAddress;
        std::string clientId;
        std::string topic;
        std::mutex dataMutex;

        bool withBson;
};

#endif