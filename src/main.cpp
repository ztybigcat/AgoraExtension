#include <iostream>
#include "AgoraChannelSender.h"

int main() {
    // Replace these with your actual Agora app ID, channel ID, and user ID
    std::string appId = "f41264d544d0427ba2d47a4f975857ef";
    std::string channelId = "agoratest";
    std::string userId = "1";

    // For testing listen function
    std::string audioFile = "received_audio.pcm"; // Example audio file name
    int sampleRate = 16000; // Example sample rate
    int numOfChannels = 1; // Example number of channels

    // Create an instance of AgoraChannelSender
    AgoraChannelSender agoraSender(appId, channelId, userId);

    // Example to test listening for incoming audio
    if (agoraSender.listen(audioFile, sampleRate, numOfChannels)) {
        std::cout << "Listening for incoming audio." << std::endl;
    } else {
        std::cout << "Failed to start listening for audio." << std::endl;
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
    }

    return 0; // This line will never be reached
    // Wait or perform other tasks...

    // When done, explicitly or implicitly the destructor will be called, cleaning up resources.
    // Optionally, you can directly call disconnect if needed before the destructor is invoked.

    return 0;
}
