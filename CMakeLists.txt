cmake_minimum_required(VERSION 3.10)
project(Stilt)

# Defina a versão do C++ (por exemplo, C++17)
set(CMAKE_CXX_STANDARD 17)

# Set optimization level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Include the 'include' folder as a header search directory
include_directories(include)

# Find the Paho MQTT C++ library (old version)
find_package(PahoMqttCpp REQUIRED)

# Link your shared library against the old version of the Paho MQTT libraries and spdlog
add_library(stilt_shared_old SHARED src/main.cpp src/Log.cpp)

# Link against the old version of the Paho MQTT libraries and spdlog
target_link_libraries(stilt_shared_old PRIVATE
    PahoMqttCpp::paho-mqttpp3
    spdlog
    paho-mqtt3as
)

# Install the library
install(TARGETS stilt_shared_old
    LIBRARY DESTINATION lib
)

add_subdirectory(test)

