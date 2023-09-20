#include "Audio.h"
#include "FileManager.h"
FileManager fileAudio;

std::vector<std::string> Audio::getAudioDirectories() {
    return audioDirectories;
}

const char* Audio::getAudioDirectory() {
    return audioDirectory;
}

Audio::Audio() {
    audioDirectories = fileAudio.parseTHIS(audioDirectory);

}
