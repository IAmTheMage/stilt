cmake_minimum_required(VERSION 3.10)
project(MQTTExample)

# Define a versão do C++ usada (por exemplo, C++11)
set(CMAKE_CXX_STANDARD 11)

# Inclui a pasta 'include' como diretório de busca de cabeçalhos
include_directories(include)

# Adiciona a pasta 'src' ao caminho de busca de arquivos de origem
add_subdirectory(src)

# Especifica onde o CMake deve procurar as bibliotecas
link_directories(/usr/local/lib)

# Define o executável e vincula as bibliotecas necessárias
add_executable(mqtt_example src/main.cpp)

# Vincula a biblioteca Paho MQTT ao executável
target_link_libraries(mqtt_example libpaho-mqtt3cs.so.1.3.7)

# Adiciona a pasta 'include' como diretório de busca de cabeçalhos para o alvo
target_include_directories(mqtt_example PRIVATE include)
