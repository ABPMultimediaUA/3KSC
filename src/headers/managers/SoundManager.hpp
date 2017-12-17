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

#ifndef SOUND_MANAGER
#define SOUND_MANAGER

#include <iostream>
#include <fmod/wincompat.h>
#include <fmod/fmod.hpp>
#include <fmod/fmod_event.hpp>
#include <fmod/fmod_errors.h>

typedef FMOD::Sound* Sound;

class SoundManager{
private:
    static SoundManager* m_instance;

    FMOD::System    *m_System;
    FMOD_RESULT     m_Result;
    FMOD::Channel   *m_channel[5];

public:
    static SoundManager* instance();
    SoundManager();
    ~SoundManager();
    void ERRCHECK(FMOD_RESULT result);
    void createSound(Sound *pSound, const char *pFile);
    void playSound(Sound pSound, bool bLoop);
    void releaseSound(Sound pSound);
    bool isPlaying(Sound *pSound);
    void update();
};

#endif