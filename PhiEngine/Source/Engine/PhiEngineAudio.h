#pragma once

#include "SFML\Audio.hpp"
#include <vector>


class PhiEngineAudio
{
private:
	std::vector<std::string> m_SFXfileList;
	std::vector<sf::Sound> m_soundFXList;
	sf::SoundBuffer m_soundBuffer;
	sf::Music m_music;
public:
	bool Initialize(sf::SoundBuffer& buffer, std::vector<std::string> m_SFXFileList, std::string musicFile);
	void PlayOneShot(sf::Sound& sfx);
	void PlayMusic(sf::Music& music);
};
