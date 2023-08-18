# CMakeLists.txt in the 'test' folder

# Define the test executable and link necessary libraries
add_executable(cast_to_basic_message_test_exec test_cast_to_basic_message.cpp)

# Add the 'include' folder as a header search directory for the test
target_include_directories(cast_to_basic_message_test_exec PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the Paho MQTT library to the test
target_link_libraries(cast_to_basic_message_test_exec libpaho-mqtt3cs.so.1.3.7)

