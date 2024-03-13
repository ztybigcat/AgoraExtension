#include "AgoraChannelSender.h"


// Constructor
AgoraChannelSender::AgoraChannelSender(const std::string& appId, const std::string& channelId, const std::string& userId)
        : appId_(appId), channelId_(channelId), userId_(userId) {
    initialize();
}

// Destructor
AgoraChannelSender::~AgoraChannelSender() {
    disconnect();
}

// Method to send a string message
bool AgoraChannelSender::sendString(const std::string& message) {
    if (!connection_ || streamId_ == -1) return false;
    return connection_->sendStreamMessage(streamId_, message.c_str(), message.length()) == 0;
}

// Private method to initialize the Agora service and connection
void AgoraChannelSender::initialize() {
    service_ = createAndInitAgoraService(false, true, false);
    if (!service_) {
        AG_LOG(ERROR, "Failed to create Agora service!");
        return;
    }

    agora::rtc::RtcConnectionConfiguration ccfg;
    ccfg.clientRoleType = agora::rtc::CLIENT_ROLE_BROADCASTER;
    ccfg.autoSubscribeAudio = false;
    ccfg.autoSubscribeVideo = false;
    ccfg.enableAudioRecordingOrPlayout = false; // Subscribe audio but without playback
    ccfg.videoRecvMediaPacket = false;
    connection_ = service_->createRtcConnection(ccfg).get();

    if (!connection_) {
        AG_LOG(ERROR, "Failed to create Agora connection!");
        return;
    }

    // Subcribe streams
    connection_->getLocalUser()->subscribeAllAudio();


    if (connection_->connect(appId_.c_str(), channelId_.c_str(), userId_.c_str())) {
        AG_LOG(ERROR, "Failed to connect to Agora channel!");
        return;
    }

    connection_->createDataStream(&streamId_, true, true, false);
}

// Private method to disconnect from the Agora service
void AgoraChannelSender::disconnect() {
    if (localUserObserver_) {
        localUserObserver_->unsetAudioFrameObserver();
        localUserObserver_.reset();
    }

    if (pcmFrameObserver_) {
        // If there's any specific cleanup needed for pcmFrameObserver_
        pcmFrameObserver_.reset();
    }

    if (connection_) {
        connection_->disconnect();
        connection_.reset(); // This replaces connection_ = nullptr for shared_ptr
    }

    if (service_) {
        service_->release(); // Or appropriate method to clean up the service
        service_ = nullptr;
    }
    AG_LOG(INFO, "Disconnected from Agora channel successfully");
}

bool AgoraChannelSender::listen(const std::string& audioFile, int sampleRate, int numOfChannels) {
    if (!connection_) return false;

    localUserObserver_ = std::make_shared<SampleLocalUserObserver>(connection_->getLocalUser());
    pcmFrameObserver_ = std::make_shared<PcmFrameObserver>(audioFile);

    if (connection_->getLocalUser()->setPlaybackAudioFrameParameters(
            numOfChannels, sampleRate,
            agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_ONLY,
            sampleRate / 100 * numOfChannels)) {
        AG_LOG(ERROR, "Failed to set audio frame parameters!");
        return false;
    }
    localUserObserver_->setAudioFrameObserver(pcmFrameObserver_.get());
    return true;
}
