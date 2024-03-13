cmake_minimum_required(VERSION 3.27)
project(AgoraExtension)

# Find the Python interpreter and development headers
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Add pybind11 subdirectory (assumes pybind11 is located in a subdirectory of your project)
add_subdirectory(pybind11)

# Set the C++ standard to be used
set(CMAKE_CXX_STANDARD 14)

# Include directories for Agora SDK and pybind11
include_directories(agora_sdk)
include_directories(agora_sdk/include)

# If you have additional include directories, specify them here
include_directories(src)
include_directories(common)

# Define your module/library. Specify the target name first and then the source files.
add_library(AgoraExtension MODULE
        src/AgoraChannelSender.cpp
        src/AgoraExtension.cpp
        common/sample_common.cpp
        src/PcmFrameObserver.h
        src/PcmFrameObserver.cpp
        common/sample_local_user_observer.cpp
)

add_executable(AgoraTestApp
        src/main.cpp # Ensure this file exists and contains your main function
        src/AgoraChannelSender.cpp
        common/sample_common.cpp
        src/PcmFrameObserver.cpp
        common/sample_local_user_observer.cpp
)
# Link the target library against pybind11 and potentially other libraries
target_link_libraries(AgoraExtension PRIVATE pybind11::module)
target_link_libraries(AgoraExtension PRIVATE
        ${CMAKE_SOURCE_DIR}/agora_sdk/libagora-fdkaac.so
        ${CMAKE_SOURCE_DIR}/agora_sdk/libagora-ffmpeg.so
        ${CMAKE_SOURCE_DIR}/agora_sdk/libagora_rtc_sdk.so
)
target_link_libraries(AgoraTestApp PRIVATE
        ${CMAKE_SOURCE_DIR}/agora_sdk/libagora-fdkaac.so
        ${CMAKE_SOURCE_DIR}/agora_sdk/libagora-ffmpeg.so
        ${CMAKE_SOURCE_DIR}/agora_sdk/libagora_rtc_sdk.so
)