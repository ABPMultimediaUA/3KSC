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
    if(result == 70){
        return;
    }else if (result != FMOD_OK){
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
}

void SoundManager::loadEvents(SoundID p_bank){
    switch(p_bank){
        case SoundID::S_KIRA:
            this->createSoundEvent("event:/characters/kira/death"     , "k_death"       );
            this->createSoundEvent("event:/characters/kira/kill"      , "k_kill"        );
            this->createSoundEvent("event:/characters/kira/random"    , "k_random"      );
            this->createSoundEvent("event:/characters/kira/special"   , "k_special"     );
            this->createSoundEvent("event:/characters/kira/taunt"     , "k_taunt"       );
            this->createSoundEvent("event:/characters/kira/ultimate"  , "k_ultimate"    );
            break;
        
        case SoundID::S_LUKA:
            this->createSoundEvent("event:/characters/luka/death"     , "l_death"       );
            this->createSoundEvent("event:/characters/luka/kill"      , "l_kill"        );
            this->createSoundEvent("event:/characters/luka/random"    , "l_random"      );
            this->createSoundEvent("event:/characters/luka/special"   , "l_special"     );
            this->createSoundEvent("event:/characters/luka/taunt"     , "l_taunt"       );
            this->createSoundEvent("event:/characters/luka/ultimate"  , "l_ultimate"    );
            break;
        
        case SoundID::S_MIYAGI:
            this->createSoundEvent("event:/characters/miyagi/death"     , "m_death"       );
            this->createSoundEvent("event:/characters/miyagi/kill"      , "m_kill"        );
            this->createSoundEvent("event:/characters/miyagi/random"    , "m_random"      );
            this->createSoundEvent("event:/characters/miyagi/special"   , "m_special"     );
            this->createSoundEvent("event:/characters/miyagi/taunt"     , "m_taunt"       );
            this->createSoundEvent("event:/characters/miyagi/ultimate"  , "m_ultimate"    );
            break;
        
        case SoundID::S_PLUP:
            this->createSoundEvent("event:/characters/plup/death"     , "p_death"       );
            this->createSoundEvent("event:/characters/plup/kill"      , "p_kill"        );
            this->createSoundEvent("event:/characters/plup/random"    , "p_random"      );
            this->createSoundEvent("event:/characters/plup/special"   , "p_special"     );
            this->createSoundEvent("event:/characters/plup/taunt"     , "p_taunt"       );
            this->createSoundEvent("event:/characters/plup/ultimate"  , "p_ultimate"    );
            break;
        
        case SoundID::S_RAWR:
            this->createSoundEvent("event:/characters/rawr/death"     , "r_death"       );
            this->createSoundEvent("event:/characters/rawr/kill"      , "r_kill"        );
            this->createSoundEvent("event:/characters/rawr/random"    , "r_random"      );
            this->createSoundEvent("event:/characters/rawr/special"   , "r_special"     );
            this->createSoundEvent("event:/characters/rawr/taunt"     , "r_taunt"       );
            this->createSoundEvent("event:/characters/rawr/ultimate"  , "r_ultimate"    );
            break;
        
        case SoundID::S_SPARKY:
            this->createSoundEvent("event:/characters/sparky/death"     , "s_death"       );
            this->createSoundEvent("event:/characters/sparky/kill"      , "s_kill"        );
            this->createSoundEvent("event:/characters/sparky/random"    , "s_random"      );
            this->createSoundEvent("event:/characters/sparky/special"   , "s_special"     );
            this->createSoundEvent("event:/characters/sparky/taunt"     , "s_taunt"       );
            this->createSoundEvent("event:/characters/sparky/ultimate"  , "s_ultimate"    );
            break;

        case SoundID::S_FOSFOS_STADIUM:
            this->createSoundEvent("event:/music/fosfosStadium"    , "fos_music"    );
            break;
    }
}

void SoundManager::createSoundEvent(const char* p_eventPath, const char* p_name){
    FMOD::Studio::EventDescription* t_eventDescription;

    ERRCHECK(m_system->getEvent(p_eventPath, &t_eventDescription));

    SoundEvent* t_soundEvent = new SoundEvent(t_eventDescription);

    //m_soundEvents.insert(std::pair<const char*, SoundEvent*>(p_name, t_soundEvent));
    m_soundEvents[p_name] = t_soundEvent;
}

void SoundManager::playSound(const char* p_name){    
    /*std::cout << "Vamos a buscar: " << p_name << std::endl;
    std::cout << "----------------------------" << std::endl;;
    for(const auto &p : m_soundEvents){
        std::cout << p.first << " = " << p.second << std::endl;
    }
    */
    m_soundEvents.at(p_name)->start();
}

void SoundManager::modifyParameter(const char* p_name, float p_num, const char* p_parameter){
    m_soundEvents.at(p_name)->modifyParameter(p_num, p_parameter);
}

bool SoundManager::isPlaying(const char* p_name){
    bool playing = m_soundEvents.at(p_name)->getPlaybackState();
    return playing;
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

void SoundEvent::modifyParameter(float p_num, const char* p_parameter){
    ERRCHECK(m_soundInstance->setParameterValue(p_parameter, p_num));
}

bool SoundEvent::getPlaybackState(){
    FMOD_STUDIO_PLAYBACK_STATE t_state;
    ERRCHECK(m_soundInstance->getPlaybackState(&t_state));
    if(t_state ==  FMOD_STUDIO_PLAYBACK_PLAYING){
        return true;
    }
    return false;
}
