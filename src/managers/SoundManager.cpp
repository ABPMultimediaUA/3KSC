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

#include "../headers/managers/SoundManager.hpp"
#include <iostream>

//Instance initialization
SoundManager* SoundManager::m_instance = 0;

//Returns the only instance of this class
SoundManager* SoundManager::instance(){
    if(!m_instance)
        m_instance = new SoundManager();

    return m_instance;
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
    getEvents();
}

//Destructor
SoundManager::~SoundManager(){}

void SoundManager::createSound(Sound p_sound, const char *pFile){
    ERRCHECK(m_lowLevelSystem->createSound(pFile, FMOD_DEFAULT, 0, &p_sound));
}

void SoundManager::playSound(Sound p_sound){
    ERRCHECK(m_lowLevelSystem->playSound(p_sound, 0, false, &m_channel));
}

void SoundManager::update(){
    ERRCHECK(m_system->update());
    ERRCHECK(m_lowLevelSystem->update());
}

void SoundManager::loadBanks(){
    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_masterBank));

    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_stringsBank));

    ERRCHECK(m_system->loadBankFile("assets/fmod/Build/Desktop/Music.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &m_musicBank));
}

void SoundManager::getEvents(){
    ERRCHECK(m_system->getEvent("event:/Music/Music", &m_musicEvent));

    ERRCHECK(m_musicEvent->createInstance(&m_musicInstance));

    ERRCHECK(m_musicInstance->start());
}

void SoundManager::modifyParameter(float num){
    ERRCHECK(m_musicInstance->setParameterValue("Intensity", num));
}

