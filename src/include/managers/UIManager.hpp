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
        sf::RenderWindow*       m_window;

        sf::Sprite**            m_faces;            //Player faces
        sf::Sprite**            m_names;            //Player names
        sf::CircleShape***      m_lives;            //Player lives left
        sf::RectangleShape**    m_barsBG;            //Basic bars backgrounds
        sf::RectangleShape**    m_HPBarsFG;         //HP bars foregrounds
        sf::RectangleShape**    m_HPShieldBarsFG;   //HP Shields foregrounds
        sf::RectangleShape**    m_MPBarsFG;         //MP foregrounds
        sf::Text**              m_barTexts;         //Text over bars
        sf::RectangleShape*     m_selected;         //Rectangle over selected player

        int m_players;
        int* m_playersLives;

        int* m_buttons;
        int* m_menus;
        int* m_callbacks;
        
        void initializeHUD();
        void clipFace(int p_player, int p_face, int p_variant);
        void clipFace(int p_player, int p_variant);
        void clipName(int p_player, int p_name, int p_variant);
        void clipName(int p_player, int p_variant);

    public:
        static UIManager& instance();
        UIManager();
        ~UIManager();

        void setLives(int p_player, int p_lives);
        void setHP(int p_player, int p_HP);
        void setHPShield(int p_player, int p_HPShield);
        void setMP(int p_player, int p_MP);
        void selectPlayer(int p_player);

        void update();
        void render();
        

        void start();
        void pause();
        void showMenu();
        void hideMenu();
};

#endif