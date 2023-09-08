# Stilt


The UFJF competition team, Rinobot, has developed the Stilt communication library, utilizing MQTT technology and the C++17 programming language. This library was created to enhance and streamline communication interactions, providing an efficient and robust approach to data exchange. Through the use of the MQTT protocol, Stilt offers reliable, low-latency communication, catering to the demands of applications developed by the Rinobot team. Furthermore, the choice of C++17 as the underlying programming language ensures high-quality code, leveraging modern features for effective implementation and easy maintenance.

## Work in progress

- [x] Write a wrapper to send one message
- [x] Single thread multiple message queue.
- [ ] Multithread multiple message queue
- [x] BSON serialization
- [ ] Esp32 receiver
- [ ] Esp32 sender
- [ ] Single Thread Receiver
- [ ] Multithread Receiver

## Documentation

- [Logging](#logging)
- [BasicMessage](#basic-message)

- ## Logging

Stilt provides 5 types of logging, listed below

```c++17
    #define STILT_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
    #define STILT_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define STILT_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define STILT_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
    #define STILT_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)
```

"You can use them in your code that uses the library, as well as the library uses them internally."

Examples:

```c++17
    STILT_INFO("Numero enviado de mensagens = {}, numero minimo esperado: {}", repeater->getSendedMessages(), minimumSendedMessages);
```

## Basic Message

## BSON Messages

This software is distributed under the AGPL (GNU Affero General Public License).s