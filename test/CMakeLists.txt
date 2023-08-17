# CMakeLists.txt na pasta 'test'

# Define o executável do teste e vincula as bibliotecas necessárias
add_executable(cast_to_basic_message_test test_cast_to_basic_message.cpp)

# Adiciona a pasta 'include' como diretório de busca de cabeçalhos para o teste
target_include_directories(cast_to_basic_message_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Vincula a biblioteca Paho MQTT ao teste
target_link_libraries(cast_to_basic_message_test libpaho-mqtt3cs.so.1.3.7)

# Adiciona um teste usando o ctest
add_test(NAME cast_to_basic_message_test COMMAND cast_to_basic_message_test)