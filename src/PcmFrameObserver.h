//
// Created by ztybigcat on 3/9/24.
//

#include <csignal>
#include <cstring>
#include <sstream>
#include <string>
#include <thread>

#include "IAgoraService.h"
#include "NGIAgoraRtcConnection.h"

#include "NGIAgoraAudioTrack.h"
#include "NGIAgoraLocalUser.h"
#include "NGIAgoraMediaNodeFactory.h"
#include "NGIAgoraMediaNode.h"
#include "NGIAgoraVideoTrack.h"

#ifndef AGORAEXTENSION_PCMFRAMEOBSERVER_H
#define AGORAEXTENSION_PCMFRAMEOBSERVER_H
#define DEFAULT_FILE_LIMIT (100 * 1024 * 1024)

class PcmFrameObserver : public agora::media::IAudioFrameObserverBase
{
public:
    PcmFrameObserver(const std::string &outputFilePath)
            : outputFilePath_(outputFilePath), pcmFile_(nullptr), fileCount(0), fileSize_(0) {}

    bool onPlaybackAudioFrame(const char *channelId, AudioFrame &audioFrame) override;

    bool onRecordAudioFrame(const char *channelId, AudioFrame &audioFrame) override { return true; };

    bool onMixedAudioFrame(const char *channelId, AudioFrame &audioFrame) override { return true; };

    bool onPlaybackAudioFrameBeforeMixing(const char *channelId, agora::media::base::user_id_t userId, AudioFrame &audioFrame) override { return true; };

    int getObservedAudioFramePosition() override { return 0; };

    AudioParams getEarMonitoringAudioParams() override { return AudioParams(); };

    bool onEarMonitoringAudioFrame(AudioFrame &audioFrame) override { return true; };

    AudioParams getPlaybackAudioParams() override { return AudioParams(); };

    AudioParams getRecordAudioParams() override { return AudioParams(); };

    AudioParams getMixedAudioParams() override { return AudioParams(); };

private:
    std::string outputFilePath_;
    FILE *pcmFile_;
    int fileCount;
    int fileSize_;
};

#endif //AGORAEXTENSION_PCMFRAMEOBSERVER_H