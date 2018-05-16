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
#include "../include/menu_screens/TitleScreen.hpp"
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
#include <string>

//Struct containing menu actions and its properties
struct MenuActionMapping{
    MenuAction  action;                     //Action to map
    void        (MenuScreen::*function)();  //Function for the action
    bool        onlyOnce;                   //Wait for input release?
    bool        enabled;                    //Enabled or not
};

//Maps a string to a Screen
struct ScreenMapping{
    std::string string;
    Screen      screen;
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
    mapScreens();
    
    initializeScreens();

    m_waitRelease   = false;
    m_keepWaiting   = false;
}

//Destructor
MenuState::~MenuState(){
    std::cout << "~MenuState" << std::endl;

    if (m_actions)      { delete[] m_actions;       m_actions = nullptr;        }
    if (m_screenMaps)   { delete[] m_screenMaps;    m_screenMaps = nullptr;     }
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
        m_currentScreen->hideElements();
        m_currentScreen = m_screens[(int) p_screen];
        m_currentScreen->showElements();


        //Hide cursor in character select
        if (p_screen == Screen::CharacterLocal || p_screen == Screen::CharacterOnline){
            m_engineManager->setCursorVisible(false);
        }
        else{
            m_engineManager->setCursorVisible();
        }
    }
}

//Creates the instance of each menu screen
void MenuState::initializeScreens(){
    m_screens[0]    = &TitleScreen::instance();
    m_screens[1]    = &MainScreen::instance();
    m_screens[2]    = &CharacterLocalScreen::instance();
    m_screens[3]    = &CharacterOnlineScreen::instance();
    m_screens[4]    = &BattleSettingsScreen::instance();
    m_screens[5]    = &MapScreen::instance();
    m_screens[6]    = &OnlineModeScreen::instance();
    m_screens[7]    = &OnlineCreateScreen::instance();
    m_screens[8]    = &OnlineJoinScreen::instance();
    m_screens[9]    = &GameSettingsScreen::instance();

    for (int i = 0; i < 10; i++){
        m_screens[i]->hideElements();
    }

    m_currentScreen = m_screens[1];
    m_currentScreen->showElements();
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

//Initializes actions mapping
void MenuState::mapScreens(){
    m_screenMaps = new ScreenMapping[(int) Screen::Count + 1];
                            //String              //Screen
    m_screenMaps[0]     = { "Title"             , Screen::Title             };
    m_screenMaps[1]     = { "Main"              , Screen::Main              };
    m_screenMaps[2]     = { "CharacterLocal"    , Screen::CharacterLocal    };
    m_screenMaps[3]     = { "CharacterOnline"   , Screen::CharacterOnline   };
    m_screenMaps[4]     = { "BattleSettings"    , Screen::BattleSettings    };
    m_screenMaps[5]     = { "Map"               , Screen::Map               };
    m_screenMaps[6]     = { "OnlineMode"        , Screen::OnlineMode        };
    m_screenMaps[7]     = { "OnlineCreate"      , Screen::OnlineCreate      };
    m_screenMaps[8]     = { "OnlineJoin"        , Screen::OnlineJoin        };
    m_screenMaps[9]     = { "GameSettings"      , Screen::GameSettings      };
    m_screenMaps[10]    = { ""                  , Screen::Undefined         };
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
}