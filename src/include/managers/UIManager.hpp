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

//#include <SFML/Graphics.hpp>
//#include <SFML/Window/Context.hpp>
#include <irrlicht.h>

class UIManager{
    private:
        //sf::RenderTexture*  m_renderTexture;
        //const sf::Texture*  m_texture;
        //sf::Context*        m_gameContext;
        //sf::Context*        m_SFMLContext;

        //irr::gui::IGUIStaticText** m_playerNames;
        //irr::gui::IGUIStaticText** m_HPTexts;
        //irr::gui::IGUIStaticText** m_playerHPs;
        //irr::gui::IGUIStaticText** m_MPTexts;
        //irr::gui::IGUIStaticText** m_playerMPs;

        irr::gui::IGUIFont* m_font;
        irr::scene::ITextSceneNode** m_playerHPs;

        int* m_buttons;
        int* m_menus;
        int* m_callbacks;

    public:
        static UIManager& instance();
        UIManager();
        ~UIManager();
        
        void update();
        void render();

        void setLife(int p_player, int p_life);

        void start();
        void pause();
        void showMenu();
        void hideMenu();
};

#endif