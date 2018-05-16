/*
    3KSC: A fighting game
    Copyright (C);

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

#ifndef CHARACTER_LOCAL_SCREEN
#define CHARACTER_LOCAL_SCREEN

class Game;

#include "MenuScreen.hpp"
#include <vector>

class CharacterLocalScreen : public MenuScreen{
    private:
        CharacterLocalScreen(MenuState* p_menu);
        
        Game*           m_game;

        int             m_localPlayers;
        bool            m_enabledPlayers[4];

        void chooseCharacter(int p_player, int p_character);
        void enablePlayer(int p_player, bool p_playable = true);
        void disablePlayer(int p_player);

    public:
        static CharacterLocalScreen& instance();
        ~CharacterLocalScreen();

        void input();
        void update();
        void render();

        void select()               override;
};

#endif