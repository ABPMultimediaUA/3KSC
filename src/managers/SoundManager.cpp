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

//Instance initialization
SoundManager* SoundManager::m_instance = 0;

//Returns the only instance of this class
SoundManager* SoundManager::instance(){
    if(!m_instance)
        m_instance = new SoundManager();

    return m_instance;
}

//Constructor
SoundManager::SoundManager(){
    ERRCHECK(FMOD::System_Create(&m_System));
    ERRCHECK(m_System->setOutput(FMOD_OUTPUTTYPE_ALSA));
    ERRCHECK(m_System->init(32, FMOD_INIT_NORMAL, 0));
}

//Destructor
SoundManager::~SoundManager(){}

void SoundManager::ERRCHECK(FMOD_RESULT result){
    if (result != FMOD_OK){
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void SoundManager::createSound(Sound *pSound, const char *pFile){
    ERRCHECK(m_System->createSound(pFile, FMOD_SOFTWARE, 0, pSound));
}

void SoundManager::playSound(Sound pSound, bool bLoop){
    if (!bLoop){
       pSound->setMode(FMOD_LOOP_OFF);
    }
    else{
       pSound->setMode(FMOD_LOOP_NORMAL);
       pSound->setLoopCount(-1);
    }
 
    ERRCHECK(m_System->playSound(FMOD_CHANNEL_FREE, pSound, false, &m_channel[0]));
}

bool SoundManager::isPlaying(Sound *pSound){
    bool isplaying = true;
    for(int i = 0; i < 5; i++){
        if(m_channel[i]->isPlaying(&isplaying) == FMOD_OK && m_channel[i]->getCurrentSound(pSound) == FMOD_OK)
            return true;
        else
            return false;
    }
}

void SoundManager::update(){
    m_System->update();
}