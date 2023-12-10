#pragma once
#include "FileManager.h"
#include "GameManager.h"
#include <vector>
#include "Audio.h"
//	for now (till its refactored)


//	mm serialization tastes so good. it has a hint of caramel but ultimately tastes like cereal.
//	not stupid ass fruit loops tho
//	i promise its not all in the header file...
//
//		...
//			.........
//
//																		...its all in the header file :)







class Settings {
protected:
	//	cute lil file manager
	FileManager plz;

public:

	//	constructor
	Settings()
		: settingsFileDirectory("SaveData/settings.txt")
	{
		bool doesExist = false;
		//	1. check to see if a settings file exists
		if (plz.fileCheck(settingsFileDirectory)) {
			doesExist = true;
			//	load the file contents into the vector
			if (plz.fileLoadToVector(settingsFileContents, settingsFileDirectory)) {
				loadSettings(settingsFileContents);
				cout << "user settings applied\n";
			}
		}

		//	3. if not, apply defaults
		if (doesExist == false)	applyDefaultSettings();
	}



	const char* settingsFileDirectory;
	vector<string> settingsFileContents;


	bool applyDefaultSettings() {
		float DefaultMasterVolume = 0.5f;
		float DefaultSoundEffectVolume = 0.5f;
		float DefaultMusicVolume = 0.5f;

		options::FPS = 60;

		options::MasterVolume = DefaultMasterVolume;
		options::MusicVolume = DefaultMusicVolume;
		options::SoundEffectVolume = DefaultSoundEffectVolume;

		return true;
	}

	//	save all current settings to The File(tm)
	bool saveSettings() {
		//	1. check to see if the file exists
		//	2. save the value to the settings vector
		//	3. write the settings vector to the file directory
		//	4. return

		if(plz.fileCheck(settingsFileDirectory)) {
			string newFps = std::to_string(options::FPS);
			plz.replaceValue("fps", newFps.c_str(), settingsFileContents);
			string newMastV = std::to_string(options::MasterVolume);
			plz.replaceValue("mastervolume", newMastV.c_str(), settingsFileContents);
			string newMusV = std::to_string(options::MusicVolume);
			plz.replaceValue("musicvolume", newMusV.c_str(), settingsFileContents);
			string newSfxV = std::to_string(options::SoundEffectVolume);
			plz.replaceValue("sfxvolume", newSfxV.c_str(), settingsFileContents);

			if (plz.fileWrite(settingsFileContents, settingsFileDirectory)) return true;
		}

		return false;
	}

	//	load all saved settings
	void loadSettings(vector<string>& superVector_) {
		//	fps
		//	master volume
		//	music
		//	sfx

		//	1. read
		string newFps = plz.isWhat("fps", superVector_);
		string newMasterVolume = plz.isWhat("mastervolume", superVector_);
		string newMusicVolume = plz.isWhat("musicvolume", superVector_);
		string newSfxVolume = plz.isWhat("sfxvolume", superVector_);

		//	2. write
		options::FPS = stoi(newFps);
		options::MasterVolume = stof(newMasterVolume);
		options::MusicVolume = stof(newMusicVolume);
		options::SoundEffectVolume = stof(newSfxVolume);

	}




};

