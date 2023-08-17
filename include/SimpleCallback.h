#include "Log.h"
#include <mqtt/async_client.h>


class SampleCallbacks : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
    // Implementação dos callbacks necessários
    void on_failure(const mqtt::token& tok) override {
        std::cout << "Falha na operação MQTT: " << tok.get_reason_code() << std::endl;
    }

    void on_success(const mqtt::token& tok) override {
        std::cout << "Mensagem publicada com sucesso!" << std::endl;
    }

    void connection_lost(const std::string& cause) override {
        std::cout << "Conexão MQTT perdida: " << cause << std::endl;
    }
};