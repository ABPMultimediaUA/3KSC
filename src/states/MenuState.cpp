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

#include "../include/states/MenuState.hpp"
#include "../include/states/InGameState.hpp"
#include "../include/Game.hpp"

#include "../include/menu_screens/MenuScreen.hpp"
#include "../include/menu_screens/MainScreen.hpp"
#include "../include/menu_screens/CharacterLocalScreen.hpp"
#include "../include/menu_screens/CharacterOnlineScreen.hpp"
#include "../include/menu_screens/BattleSettingsScreen.hpp"
#include "../include/menu_screens/MapScreen.hpp"
#include "../include/menu_screens/OnlineModeScreen.hpp"
#include "../include/menu_screens/OnlineCreateScreen.hpp"
#include "../include/menu_screens/OnlineJoinScreen.hpp"
#include "../include/menu_screens/GameSettingsScreen.hpp"

#include "../include/extra/MenuActions.hpp"
#include "../include/managers/EngineManager.hpp"

#include <iostream>

//Struct containing menu actions and its properties
struct MenuActionMapping{
    MenuAction  action;                     //Action to map
    void        (MenuScreen::*function)();  //Function for the action
    bool        onlyOnce;                   //Wait for input release?
    bool        enabled;                    //Enabled or not
};

//Instance initialization
MenuState* MenuState::m_instance = nullptr; 

//Constructor
MenuState::MenuState(Game* p_game){
    m_instance      = this;
    m_game          = p_game;
    m_engineManager = &EngineManager::instance();
    // m_window        = m_engineManager->getWindow();
    
    mapActions();

    createTexture();
    loadSpritesheet();
    loadFont();
    
    initializeScreens();

    m_waitRelease   = false;
    m_keepWaiting   = false;

    m_currentScreen = m_screens[0];
}

//Destructor
MenuState::~MenuState(){
    std::cout << "~MenuState" << std::endl;
    
    if (m_sprite)       { delete m_sprite;      m_sprite = nullptr;         }
    if (m_texture)      { delete m_texture;     m_texture = nullptr;        }
    if (m_spritesheet)  { delete m_spritesheet; m_spritesheet = nullptr;    }
    if (m_font)         { delete m_font;        m_font = nullptr;           }
    if (m_actions)      { delete[] m_actions;   m_actions = nullptr;        }
    m_instance = nullptr;
}

MenuState* MenuState::getInstance(){
    return m_instance;
}


//Change to next state
void MenuState::nextState(){
    m_game->setState(new InGameState(m_game));
}


//Changes to specified screen
void MenuState::setScreen(Screen p_screen){
    if (p_screen != Screen::Undefined){
        m_currentScreen = m_screens[(int) p_screen];

        //Hide cursor in character select
        if (p_screen == Screen::CharacterLocal || p_screen == Screen::CharacterOnline){
            m_engineManager->setCursorVisible(false);
        }
        else{
            m_engineManager->setCursorVisible();
        }
    }
}

//Creates the texture to render to
void MenuState::createTexture(){
    m_texture = new sf::RenderTexture();

    if (!m_texture->create(1280, 720)){
        std::cerr << "Error creating 2D render target!" << std::endl;
    }

    m_sprite = new sf::Sprite();
}

//Loads the common spritesheet for all menu screens
void MenuState::loadSpritesheet(){
    m_spritesheet = new sf::Texture();

    if (!m_spritesheet->loadFromFile("assets/UI/Spritesheet_menus.png")){
        std::cerr << "Error loading menus spritesheet!" << std::endl;
    }
}

//Loads the font for menus
void MenuState::loadFont(){
    m_font = new sf::Font();

    if (!m_font->loadFromFile("assets/fonts/QK Star.ttf")){
        std::cerr << "Error loading menus font!" << std::endl;
    }
}

//Creates the instance of each menu screen
void MenuState::initializeScreens(){
    m_screens[0]    = &MainScreen::instance();
    m_screens[1]    = &CharacterLocalScreen::instance();
    m_screens[2]    = &CharacterOnlineScreen::instance();
    m_screens[3]    = &BattleSettingsScreen::instance();
    m_screens[4]    = &MapScreen::instance();
    m_screens[5]    = &OnlineModeScreen::instance();
    m_screens[6]    = &OnlineCreateScreen::instance();
    m_screens[7]    = &OnlineJoinScreen::instance();
    m_screens[8]    = &GameSettingsScreen::instance();
}

//Initializes actions mapping
void MenuState::mapActions(){
    m_actions = new MenuActionMapping[(int) MenuAction::Count + 1];
                      //Action                //Function                  //onlyOnce  //Enabled
    m_actions[0]    = {MenuAction::Up       , &MenuScreen::up           , true      , false};
    m_actions[1]    = {MenuAction::Down     , &MenuScreen::down         , true      , false};
    m_actions[2]    = {MenuAction::Left     , &MenuScreen::left         , true      , false};
    m_actions[3]    = {MenuAction::Right    , &MenuScreen::right        , true      , false};
    m_actions[4]    = {MenuAction::Select   , &MenuScreen::select       , true      , false};
    m_actions[5]    = {MenuAction::Back     , &MenuScreen::back         , true      , false};
    m_actions[6]    = {MenuAction::Save     , &MenuScreen::save         , true      , false};
    m_actions[7]    = {MenuAction::Settings , &MenuScreen::settings     , true      , false};
    m_actions[8]    = {MenuAction::Count    , nullptr                   , false     , false};
}

void MenuState::input(){
    m_currentScreen->input();
}

void MenuState::update(){
    m_currentScreen->update();
}

void MenuState::render(){
    //Update texture contents
    m_currentScreen->render();

    //Put texture in sprite
    m_sprite->setTexture(m_texture->getTexture());

    //Render the sprite
    // m_window->clear();
    // m_window->draw(*m_sprite);
    // m_window->display();
}