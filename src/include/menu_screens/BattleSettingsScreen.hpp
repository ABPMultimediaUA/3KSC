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

#ifndef BATTLE_SETTINGS_SCREEN
#define BATTLE_SETTINGS_SCREEN

class Game;

#include "MenuScreen.hpp"

class BattleSettingsScreen : public MenuScreen{
    private:
        BattleSettingsScreen(MenuState* p_menu);
        
        Game*                   m_game;

        MenuNode*               m_roundsNode;
        MenuNode*               m_livesNode;
        MenuNode*               m_timeLimitNode;

        sf::Sprite*             m_rounds;
        sf::Sprite*             m_lives;
        sf::Sprite*             m_timeLimit;

        sf::Text*               m_roundsText;
        sf::Text*               m_livesText;
        sf::Text*               m_timeLimitText;


        void clipElements()         override;
        void setElementsOrigins()   override;
        void placeElements()        override;
        void initializeNodes()      override;

    public:
        static BattleSettingsScreen& instance();
        ~BattleSettingsScreen();

        void render()               override;

        void select()               override;
};

#endif