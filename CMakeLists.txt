# CMakeLists.txt na raiz do projeto

cmake_minimum_required(VERSION 3.10)
project(MQTTExample)

# Define a versão do C++ usada (por exemplo, C++11)
set(CMAKE_CXX_STANDARD 11)

# Inclui a pasta 'include' como diretório de busca de cabeçalhos
include_directories(include)

# Adiciona a pasta 'src' ao caminho de busca de arquivos de origem
add_subdirectory(src)

# Adiciona a pasta 'test' ao caminho de busca de arquivos de origem para testes
add_subdirectory(test)

# Especifica onde o CMake deve procurar as bibliotecas
link_directories(/usr/local/lib)

# Habilita os testes no CMake
enable_testing()

# Define o executável principal e vincula as bibliotecas necessárias
add_executable(mqtt_example src/main.cpp src/Log.cpp)

# Vincula a biblioteca Paho MQTT ao executável
target_link_libraries(mqtt_example libpaho-mqtt3cs.so.1.3.7)

# Adiciona a pasta 'include' como diretório de busca de cabeçalhos para o alvo
target_include_directories(mqtt_example PRIVATE include)

add_test(NAME cast_to_basic_message_test COMMAND cast_to_basic_message_test)