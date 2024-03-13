//
// Created by ztybigcat on 3/9/24.
//
#include "PcmFrameObserver.h"
#include "log.h"

bool PcmFrameObserver::onPlaybackAudioFrame(const char *channelId, AudioFrame &audioFrame)
{
    // Create new file to save received PCM samples
    if (!pcmFile_)
    {
        std::string fileName =
                (++fileCount > 1) ? (outputFilePath_ + std::to_string(fileCount)) : outputFilePath_;
        if (!(pcmFile_ = fopen(fileName.c_str(), "w")))
        {
            AG_LOG(ERROR, "Failed to create received audio file %s", fileName.c_str());
            return false;
        }
        AG_LOG(INFO, "Created file %s to save received PCM samples", fileName.c_str());
    }

    // Write PCM samples
    size_t writeBytes = audioFrame.samplesPerChannel * audioFrame.channels * sizeof(int16_t);
    if (fwrite(audioFrame.buffer, 1, writeBytes, pcmFile_) != writeBytes)
    {
        AG_LOG(ERROR, "Error writing decoded audio data: %s", std::strerror(errno));
        return false;
    }
    fileSize_ += writeBytes;

    // Close the file if size limit is reached
    if (fileSize_ >= DEFAULT_FILE_LIMIT)
    {
        fclose(pcmFile_);
        pcmFile_ = nullptr;
        fileSize_ = 0;
    }
    return true;
}