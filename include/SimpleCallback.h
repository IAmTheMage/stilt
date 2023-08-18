#include "Log.h"
#include <mqtt/async_client.h>


#ifndef SAMPLE_CALLBACK_H
#define SAMPLE_CALLBACK_H

class SampleCallbacks : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
    // Implementação dos callbacks necessários
    void on_failure(const mqtt::token& tok) override {
        STILT_ERROR("MQTT Operation error {}", tok.get_reason_code());
    }

    void on_success(const mqtt::token& tok) override {
        STILT_INFO("Sucessifuly publish message");
    }

    void connection_lost(const std::string& cause) override {
        STILT_ERROR("MQTT Connection Lost");
    }
};

#endif