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

void SoundManager::loadBank(int bank){
    switch(bank){
        case S_KIRA:
            ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Kira.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
        break;
        
        case S_LUKA:
            ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Luka.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
        break;
        
        case S_MIYAGI:
            ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Miyagi.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
        break;
        
        case S_PLUP:
            ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Plup.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
        break;
        
        case S_RAWR:
            ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Rawr.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
        break;
        
        case S_SPARKY:
            ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Sparky.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
        break;

        case S_FOSFOSSTADIUM:
            ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/FosFosStadium.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
        break;
    }
}
/*
void SoundManager::loadEvents(int bank){
    switch(bank){
        case S_KIRA:
            createSoundEvent("event:/characters/kira/death"     , "death"       );
            createSoundEvent("event:/characters/kira/kill"      , "kill"        );
            createSoundEvent("event:/characters/kira/random"    , "random"      );
            createSoundEvent("event:/characters/kira/special"   , "special"     );
            createSoundEvent("event:/characters/kira/taunt"     , "taunt"       );
            createSoundEvent("event:/characters/kira/ultimate"  , "ultimate"    );
        break;
        
        case S_LUKA:
            createSoundEvent("event:/characters/luka/death"     , "death"       );
            createSoundEvent("event:/characters/luka/kill"      , "kill"        );
            createSoundEvent("event:/characters/luka/random"    , "random"      );
            createSoundEvent("event:/characters/luka/special"   , "special"     );
            createSoundEvent("event:/characters/luka/taunt"     , "taunt"       );
            createSoundEvent("event:/characters/luka/ultimate"  , "ultimate"    );
        break;
        
        case S_MIYAGI:
            createSoundEvent("event:/characters/miyagi/death"     , "death"       );
            createSoundEvent("event:/characters/miyagi/kill"      , "kill"        );
            createSoundEvent("event:/characters/miyagi/random"    , "random"      );
            createSoundEvent("event:/characters/miyagi/special"   , "special"     );
            createSoundEvent("event:/characters/miyagi/taunt"     , "taunt"       );
            createSoundEvent("event:/characters/miyagi/ultimate"  , "ultimate"    );
        break;
        
        case S_PLUP:
            createSoundEvent("event:/characters/plup/death"     , "death"       );
            createSoundEvent("event:/characters/plup/kill"      , "kill"        );
            createSoundEvent("event:/characters/plup/random"    , "random"      );
            createSoundEvent("event:/characters/plup/special"   , "special"     );
            createSoundEvent("event:/characters/plup/taunt"     , "taunt"       );
            createSoundEvent("event:/characters/plup/ultimate"  , "ultimate"    );
        break;
        
        case S_RAWR:
            createSoundEvent("event:/characters/rawr/death"     , "death"       );
            createSoundEvent("event:/characters/rawr/kill"      , "kill"        );
            createSoundEvent("event:/characters/rawr/random"    , "random"      );
            createSoundEvent("event:/characters/rawr/special"   , "special"     );
            createSoundEvent("event:/characters/rawr/taunt"     , "taunt"       );
            createSoundEvent("event:/characters/rawr/ultimate"  , "ultimate"    );
        break;
        
        case S_SPARKY:
            createSoundEvent("event:/characters/sparky/death"     , "death"       );
            createSoundEvent("event:/characters/sparky/kill"      , "kill"        );
            createSoundEvent("event:/characters/sparky/random"    , "random"      );
            createSoundEvent("event:/characters/sparky/special"   , "special"     );
            createSoundEvent("event:/characters/sparky/taunt"     , "taunt"       );
            createSoundEvent("event:/characters/sparky/ultimate"  , "ultimate"    );
        break;
        case S_FOSFOSSTADIUM:
            createSoundEvent("event:/music/fosfosStadium"       , "music"    );
        break;
    }
}
*/
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
