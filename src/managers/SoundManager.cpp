/*
    3KSC: A fighting game
    Copyright (C) 2018  Chaotic Games

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*/

#include "../include/managers/SoundManager.hpp"
#include <iostream>

//Returns the only instance of this class
SoundManager& SoundManager::instance(){
    static SoundManager instance;
    return instance;
}

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

//Constructor
SoundManager::SoundManager(){
    //banksPath = "../../assets/fmod/Build/Desktop/";

    ERRCHECK(FMOD::Studio::System::create(&m_system));
    ERRCHECK(m_system->getLowLevelSystem(&m_lowLevelSystem));
    ERRCHECK(m_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRCHECK(m_lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERRCHECK(m_system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

    loadBanks();
    //getEvents();
}

//Destructor
SoundManager::~SoundManager(){}

void SoundManager::update(bool p_paused){
    ERRCHECK(m_system->update());
}

void SoundManager::loadBanks(){
    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_masterBank));

    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_stringsBank));

    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Music.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
}
/*
void SoundManager::getEvents(){
    ERRCHECK(m_system->getEvent("event:/Music/Music", &m_musicEvent));

    ERRCHECK(m_musicEvent->createInstance(&m_musicInstance));

    ERRCHECK(m_musicInstance->start());
}
*/

void SoundManager::createSoundEvent(const char* eventPath, const char* name){
    FMOD::Studio::EventDescription* t_eventDescription;

    ERRCHECK(m_system->getEvent(eventPath, &t_eventDescription));

    SoundEvent* t_soundEvent = new SoundEvent(t_eventDescription);

    m_soundEvents.insert(std::pair<const char*, SoundEvent*>(name, t_soundEvent));
}

void SoundManager::playSound(const char* name){
    m_soundEvents.at(name)->start();
}

void SoundManager::modifyParameter(const char* name, float num, const char* parameter){
    m_soundEvents.at(name)->modifyParameter(num, parameter);
}

/*
 * SOUND EVENT CLASS METHODS!
 */
SoundEvent::SoundEvent(FMOD::Studio::EventDescription* p_eventDescription){
    ERRCHECK(p_eventDescription->createInstance(&m_soundInstance));
}

void SoundEvent::start(){
    ERRCHECK(m_soundInstance->start());
}

void SoundEvent::modifyParameter(float num, const char* parameter){
    ERRCHECK(m_soundInstance->setParameterValue(parameter, num));
}
