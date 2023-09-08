# Defina a versão do CMake
cmake_minimum_required(VERSION 3.10)

# Defina o nome do seu projeto de testes
project(StiltTests)

# Encontre a biblioteca do Google Test
find_package(GTest REQUIRED)

# Inclua o diretório de cabeçalhos da sua biblioteca
include_directories(${CMAKE_SOURCE_DIR}/include)

# Defina a versão do C++ (por exemplo, C++17)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DHIGH_PERFORMANCE")

# Adicione os arquivos de teste
add_executable(${PROJECT_NAME}
    test_benchmark_output.cpp
    test_repeater.cpp
    # Adicione mais arquivos de teste conforme necessário
)

# Depend on the main project (Stilt)
add_dependencies(${PROJECT_NAME} stilt_shared_old)

# Link contra o Google Test e sua biblioteca compartilhada localmente construída
target_link_libraries(${PROJECT_NAME}
    GTest::GTest
    GTest::Main
    PahoMqttCpp::paho-mqttpp3
    spdlog
    paho-mqtt3as
    ${CMAKE_SOURCE_DIR}/build/libstilt_shared_old.so # Caminho para sua biblioteca compartilhada localmente construída
)
