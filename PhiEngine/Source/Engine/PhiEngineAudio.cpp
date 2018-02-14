
#include "PhiEngineAudio.h"

//std::vector<std::string> PhiEngineAudio::m_SFXfileList;
//std::vector<sf::Sound> PhiEngineAudio::m_soundFXList;
//sf::SoundBuffer PhiEngineAudio::m_soundBuffer;
//sf::Music PhiEngineAudio::m_music;

bool PhiEngineAudio::Initialize(sf::SoundBuffer& buffer, std::vector<std::string> m_SFXfileList, std::string musicFile)
{
	m_soundBuffer = sf::SoundBuffer(buffer);
	// Load it from a file
	for each (std::string file in m_SFXfileList)
	{
		if (!buffer.loadFromFile("../Audio/" + file))
		{
			// error...
			return false;
		}
		sf::Sound tmpSound;
		tmpSound.setBuffer(buffer);
		m_soundFXList.push_back(tmpSound);
	}
	if (m_music.openFromFile("../Audio/" + musicFile))
		return false;
	
	return true;
}

void PhiEngineAudio::PlayOneShot(sf::Sound& sfx) {

}

void PhiEngineAudio::PlayMusic(sf::Music& music) {

}
