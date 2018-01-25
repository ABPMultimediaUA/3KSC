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

#ifndef UI_MANAGER
#define UI_MANAGER

#include <SFML/Graphics.hpp>

class UIManager{
    private:
        static UIManager*   m_instance;

        sf::RenderWindow*   m_window;
        sf::Text*           m_life;
        sf::Text*           m_lifeShield;
        sf::Text*           m_magic;
        sf::Sprite*         m_magicBarBackground;
        sf::Sprite*         m_magicBarForeground;
        int                 m_magicBarFragments;
        sf::Sprite*         m_player;

        int* m_buttons;
        int* m_menus;
        int* m_callbacks;
        
        void initializeHUDTexts();
        void initializeHUDSprites();

    public:
        static UIManager* instance();
        UIManager();
        ~UIManager();

        void update();
        void render();
        
        void setLife(int p_life);
        void setLifeShield(int p_lifeShield);
        void setMagic(int p_magic);

        sf::RenderWindow*   getWindow();

        void start();
        void pause();
        void showMenu();
        void hideMenu();
};

#endif