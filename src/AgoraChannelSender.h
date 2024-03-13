#ifndef AGORA_CHANNEL_SENDER_H
#define AGORA_CHANNEL_SENDER_H

#include <csignal>
#include <cstring>
#include <sstream>
#include <string>

#include "IAgoraService.h"
#include "NGIAgoraRtcConnection.h"
#include "NGIAgoraAudioTrack.h"
#include "NGIAgoraLocalUser.h"
#include "NGIAgoraMediaNodeFactory.h"
#include "NGIAgoraMediaNode.h"
#include "NGIAgoraVideoTrack.h"
#include "sample_common.h"
#include "log.h"
#include "sample_local_user_observer.h"
#include "PcmFrameObserver.h"

class AgoraChannelSender {
public:
    AgoraChannelSender(const std::string& appId, const std::string& channelId, const std::string& userId);
    ~AgoraChannelSender();
    bool sendString(const std::string& message);
    bool listen(const std::string& audioFile = "received_audio.pcm",
                int sampleRate = 16000,
                int numOfChannels = 1);

private:
    void initialize();
    void disconnect();

    std::string appId_; // Stores the application ID provided by Agora for SDK initialization
    std::string channelId_; // The ID of the channel that this sender will connect to
    std::string userId_; // The user ID for this sender
    agora::base::IAgoraService* service_ = nullptr;
    agora::agora_refptr<agora::rtc::IRtcConnection> connection_; // The Agora connection object
    int streamId_ = -1; // ID for the data stream used to send messages
    std::shared_ptr<SampleLocalUserObserver> localUserObserver_;
    std::shared_ptr<PcmFrameObserver> pcmFrameObserver_;
};

#endif // AGORA_CHANNEL_SENDER_H
