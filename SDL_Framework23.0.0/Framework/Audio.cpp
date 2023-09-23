//#include "Audio.h"
//#include "FileManager.h"
//FileManager fileAudio;
//
////std::vector<std::string> Audio::getAudioDirectories() {
////    return audioDirectories;
////}
////
////const char* Audio::getAudioDirectory() {
////    return audioDirectory;
////}
//
//Audio::Audio(const char* fileDir) {
//    // initialize the SDL_mixer library
//    if (Mix_Init(MIX_INIT_MP3) == -1) {
//        throw std::runtime_error(Mix_GetError());
//    }
//    // open an audio device for playback
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
//        throw std::runtime_error(Mix_GetError());
//    }
//    // load the sound effect from the file
//    chunk = Mix_LoadWAV(fileDir);
//    if (chunk == NULL) {
//        throw std::runtime_error(Mix_GetError());
//    }
//}
//
//Audio::~Audio() {
//    // free the sound effect object
//    //Mix_FreeChunk(chunk);
//    // close the audio device
//    //Mix_CloseAudio();
//    // quit the SDL_mixer library
//    //Mix_Quit();
//}
//
//void Audio::playSound(int times) {
//    // play the sound effect on any available channel
//    // with the specified number of times (-1 means infinite loop)
//    //if (Mix_PlayChannel(-1, chunk, times) == -1) {
//        //throw std::runtime_error(Mix_GetError()); }
//}
