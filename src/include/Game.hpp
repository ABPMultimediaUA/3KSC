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

#ifndef GAME
#define GAME

class EngineManager;
class InputManager;
class State;

class Game{
    private:
        static Game*    m_instance;

        EngineManager*  m_engineManager;
        InputManager*   m_inputManager;
        State*          m_state;
        
        long long       m_elapsedTotal;
        long long       m_nanoFrames;

        bool            m_quitRequest;

        //Video settings
        int             m_resolutionPreset;
        bool            m_fullscreen;

        //Audio settings
        int             m_volBGM;
        int             m_volFX;
        int             m_volVoices;

        //Character settings
        bool            m_NPC[2];
        int             m_chosenPlayers[2];

        //Battle settings
        int             m_rounds;
        int             m_lives;
        int             m_timeLimit;
        int             m_map;

    public:
        Game();
        ~Game();
        static Game* getInstance() { return m_instance; }

        void setState(State* p_state);
        void nextState();
        
        void run();
        void fixedUpdate(long long p_delta);
        void quit()                                 { m_quitRequest = true; }

        //Getters
        int         getResolutionPreset()           { return m_resolutionPreset; }
        bool        isFullscreen()                  { return m_fullscreen; }

        int         getVolBGM()                     { return m_volBGM; }
        int         getVolFX()                      { return m_volFX; }
        int         getVolVoices()                  { return m_volVoices; }

        bool        isNPC(int p_player)             { return m_NPC[p_player]; }
        int         getChosenPlayer(int p_player)   { return m_chosenPlayers[p_player]; }

        int         getRounds()                     { return m_rounds; }
        int         getLives()                      { return m_lives; }
        int         getTimeLimit()                  { return m_timeLimit; }
        int         getMap()                        { return m_map; }
        
        //Setters
        void        setResolutionPreset(int p_preset);
        void        changeVideoMode();

        void        setVolBGM(int p_vol)            { m_volBGM = p_vol; }
        void        setVolFX(int p_vol)             { m_volFX = p_vol; }
        void        setVolVoices(int p_vol)         { m_volVoices = p_vol; }

        void        setPlayerNPC(int p_player, bool p_NPC = true)   { m_NPC[p_player] = p_NPC; }
        void        setChosenPlayer(int p_player, int p_character)  { m_chosenPlayers[p_player] = p_character; }
        
        void        setRounds(int p_rounds)         { m_rounds = p_rounds; }
        void        setLives(int p_lives)           { m_lives = p_lives; }
        void        setTimeLimit(int p_timeLimit)   { m_timeLimit = p_timeLimit; }
        void        setMap(int p_map)               { m_map = p_map; }        
};

#endif