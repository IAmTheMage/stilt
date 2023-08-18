cmake_minimum_required(VERSION 3.10)
project(MQTTExample)

# Define the C++ standard version (e.g., C++11)
set(CMAKE_CXX_STANDARD 11)

# Include the 'include' folder as a header search directory
include_directories(include)

# Add the 'src' folder to the source file search path
add_subdirectory(src)

# Add the 'test' folder to the source file search path for tests
add_subdirectory(test)

# Specify where CMake should look for libraries
link_directories(/usr/local/lib)

# Enable testing in CMake
enable_testing()

# Define the main executable and link necessary libraries
add_executable(mqtt_example src/main.cpp src/Log.cpp)

# Add the Paho MQTT libraries
find_package(PahoMqttCpp REQUIRED)
target_link_libraries(mqtt_example PRIVATE PahoMqttCpp::paho-mqttpp3)
add_test(NAME cast_to_basic_message_test COMMAND cast_to_basic_message_test_exec)
