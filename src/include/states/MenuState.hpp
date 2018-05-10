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

#ifndef MENU_STATE
#define MENU_STATE

class EngineManager;
class MenuScreen;
struct MenuActionMapping;

#include "State.hpp"
#include "../extra/Screens.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public State{
    friend class MenuScreen;
    friend class BattleSettingsScreen;
    friend class CharacterLocalScreen;
    friend class CharacterOnlineScreen;
    friend class GameSettingsScreen;
    friend class MainScreen;
    friend class MapScreen;
    friend class OnlineCreateScreen;
    friend class OnlineJoinScreen;
    friend class OnlineModeScreen;

    private:
        static MenuState*   m_instance;
        EngineManager*      m_engineManager;
        MenuScreen*         m_screens[(int) Screen::Count];
        MenuScreen*         m_currentScreen;

        // sf::RenderWindow*   m_window;                   //Window to render the sprite 
        sf::Sprite*         m_sprite;                   //Sprite to hold the texture
        sf::RenderTexture*  m_texture;                  //Texture to draw elements to 
        sf::Texture*        m_spritesheet;              //Spritesheet with all menu textures
        sf::Font*           m_font;                     //Font (for changing texts like settings)

        void initializeScreens();

        MenuActionMapping*  m_actions;
        void mapActions();

        bool m_waitRelease;
        bool m_keepWaiting;

    public:
        MenuState(Game* p_game);
        ~MenuState();
        static MenuState* getInstance();

        void    nextState();
        void    setScreen(Screen p_screen);

        void    createTexture();
        void    loadSpritesheet();
        void    loadFont();
        
        void    input();
        void    update();
        void    render();
};

#endif