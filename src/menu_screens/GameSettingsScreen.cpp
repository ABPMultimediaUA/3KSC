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

#include "../include/menu_screens/GameSettingsScreen.hpp"
#include "../include/Game.hpp"
#include "../include/extra/ResolutionPresets.hpp"

//Returns the only instance of this class
GameSettingsScreen& GameSettingsScreen::instance(){
    static GameSettingsScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
GameSettingsScreen::GameSettingsScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    m_game              = Game::getInstance();
    createFromFile("assets/UI/menu_screens/GameSettings.cgs");
}

//Destructor
GameSettingsScreen::~GameSettingsScreen(){
    std::cout << "~GameSettingsScreen" << std::endl;
}










/* ****************************** ACTIONS ****************************** */
void GameSettingsScreen::select(){
    save();
}