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
#include <cstring>

const char* m_dataBank[] = {
    "assets/fmod/Build/Desktop/Kira.bank",
    "assets/fmod/Build/Desktop/Luka.bank",
    "assets/fmod/Build/Desktop/Miyagi.bank",
    "assets/fmod/Build/Desktop/Plup.bank",
    "assets/fmod/Build/Desktop/Rawr.bank",
    "assets/fmod/Build/Desktop/Sparky.bank",
    "assets/fmod/Build/Desktop/FosFosStadium.bank"
};

//Returns the only instance of this class
SoundManager& SoundManager::instance(){
    static SoundManager instance;
    return instance;
}

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    /*if(result == 70)
        return;
    else*/
    if(result != FMOD_OK){
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

//Constructor
SoundManager::SoundManager(){
    ERRCHECK(FMOD::Studio::System::create(&m_system));
    ERRCHECK(m_system->getLowLevelSystem(&m_lowLevelSystem));
    ERRCHECK(m_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));
    ERRCHECK(m_lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));
    ERRCHECK(m_system->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

    loadBanks();
}

//Destructor
SoundManager::~SoundManager(){}

void SoundManager::update(bool p_paused){
    ERRCHECK(m_system->update());
}

void SoundManager::loadBanks(){
    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_masterBank));

    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_stringsBank));
}

void SoundManager::loadBank(SoundID p_bank){
    ERRCHECK(m_system->loadBankFile(m_dataBank[(int)p_bank], FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
    std::cout << "Banco " << m_dataBank[(int)p_bank] << " leido correctamente." << std::endl;
}

void SoundManager::loadEvents(SoundID p_bank){
    switch(p_bank){
        case SoundID::S_KIRA:
            createSoundEvent("event:/characters/kira/death"     , "k_death"       );
            createSoundEvent("event:/characters/kira/kill"      , "k_kill"        );
            createSoundEvent("event:/characters/kira/random"    , "k_random"      );
            createSoundEvent("event:/characters/kira/special"   , "k_special"     );
            createSoundEvent("event:/characters/kira/taunt"     , "k_taunt"       );
            createSoundEvent("event:/characters/kira/ultimate"  , "k_ultimate"    );
            break;
        
        case SoundID::S_LUKA:
            createSoundEvent("event:/characters/luka/death"     , "l_death"       );
            createSoundEvent("event:/characters/luka/kill"      , "l_kill"        );
            createSoundEvent("event:/characters/luka/random"    , "l_random"      );
            createSoundEvent("event:/characters/luka/special"   , "l_special"     );
            createSoundEvent("event:/characters/luka/taunt"     , "l_taunt"       );
            createSoundEvent("event:/characters/luka/ultimate"  , "l_ultimate"    );
            break;
        
        case SoundID::S_MIYAGI:
            createSoundEvent("event:/characters/miyagi/death"     , "m_death"       );
            createSoundEvent("event:/characters/miyagi/kill"      , "m_kill"        );
            createSoundEvent("event:/characters/miyagi/random"    , "m_random"      );
            createSoundEvent("event:/characters/miyagi/special"   , "m_special"     );
            createSoundEvent("event:/characters/miyagi/taunt"     , "m_taunt"       );
            createSoundEvent("event:/characters/miyagi/ultimate"  , "m_ultimate"    );
            break;
        
        case SoundID::S_PLUP:
            createSoundEvent("event:/characters/plup/death"     , "p_death"       );
            createSoundEvent("event:/characters/plup/kill"      , "p_kill"        );
            createSoundEvent("event:/characters/plup/random"    , "p_random"      );
            createSoundEvent("event:/characters/plup/special"   , "p_special"     );
            createSoundEvent("event:/characters/plup/taunt"     , "p_taunt"       );
            createSoundEvent("event:/characters/plup/ultimate"  , "p_ultimate"    );
            break;
        
        case SoundID::S_RAWR:
            createSoundEvent("event:/characters/rawr/death"     , "r_death"       );
            createSoundEvent("event:/characters/rawr/kill"      , "r_kill"        );
            createSoundEvent("event:/characters/rawr/random"    , "r_random"      );
            createSoundEvent("event:/characters/rawr/special"   , "r_special"     );
            createSoundEvent("event:/characters/rawr/taunt"     , "r_taunt"       );
            createSoundEvent("event:/characters/rawr/ultimate"  , "r_ultimate"    );
            break;
        
        case SoundID::S_SPARKY:
            createSoundEvent("event:/characters/sparky/death"     , "s_death"       );
            createSoundEvent("event:/characters/sparky/kill"      , "s_kill"        );
            createSoundEvent("event:/characters/sparky/random"    , "s_random"      );
            createSoundEvent("event:/characters/sparky/special"   , "s_special"     );
            createSoundEvent("event:/characters/sparky/taunt"     , "s_taunt"       );
            createSoundEvent("event:/characters/sparky/ultimate"  , "s_ultimate"    );
            break;

        case SoundID::S_FOSFOS_STADIUM:
            createSoundEvent("event:/music/fosfosStadium"    , "fos_music"    );
            break;
    }
}

void SoundManager::createSoundEvent(const char* eventPath, const char* name){
    FMOD::Studio::EventDescription* t_eventDescription;

    ERRCHECK(m_system->getEvent(eventPath, &t_eventDescription));

    SoundEvent* t_soundEvent = new SoundEvent(t_eventDescription);
    m_soundEvents.insert(std::pair<const char*, SoundEvent*>(name, t_soundEvent));
}

void SoundManager::playSound(const char* name, float p_volume){
    for(m_iterator = m_soundEvents.begin(); m_iterator != m_soundEvents.end(); m_iterator++){
        if(strcmp(m_iterator->first, name) == 0){
            std::cout << "Play " << name << std::endl;
            m_iterator->second->setVolume(p_volume);
            m_iterator->second->start();
            break;
        }
    }

    //m_soundEvents.at(name)->start();
}

void SoundManager::pauseAll(){
    for(m_iterator = m_soundEvents.begin(); m_iterator != m_soundEvents.end(); m_iterator++){
        bool t_pause = false;
        m_iterator->second->getEventInstance()->getPaused(&t_pause);
        if(!t_pause){
            m_iterator->second->pause();
            m_mutedSounds.push_back(m_iterator->second);
        }
    }
}

void SoundManager::unPauseAll(){
    for(int i = 0; i < m_mutedSounds.size(); i++){
        m_mutedSounds.at(i)->unPause();
    }
    m_mutedSounds.clear();
}

void SoundManager::modifyParameter(const char* name, float num, const char* parameter){
    for(m_iterator = m_soundEvents.begin(); m_iterator != m_soundEvents.end(); m_iterator++){
        if(strcmp(m_iterator->first, name) == 0){
            std::cout << "Modify " << name << " " << num << std::endl;
            m_iterator->second->modifyParameter(num, parameter);
            std::cout << "MODIFICADO" << std::endl;
            break;
        }
    }

    //m_soundEvents.at(name)->modifyParameter(num, parameter);
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

void SoundEvent::pause(){
    ERRCHECK(m_soundInstance->setPaused(true));
}

void SoundEvent::unPause(){
    ERRCHECK(m_soundInstance->setPaused(false));
}

void SoundEvent::setVolume(float p_volume){
    ERRCHECK(m_soundInstance->setVolume(p_volume));
}

void SoundEvent::modifyParameter(float num, const char* parameter){
    ERRCHECK(m_soundInstance->setParameterValue(parameter, num));
}

FMOD::Studio::EventInstance* SoundEvent::getEventInstance(){
    return m_soundInstance;
}
