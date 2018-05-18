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

#include "../include/menu_screens/CharacterLocalScreen.hpp"

#include "../include/managers/InputManager.hpp"
#include "../include/Game.hpp"
#include <iostream>

#define k_characters    3
#define k_players       2

//Instance initialization
CharacterLocalScreen* CharacterLocalScreen::m_instance = nullptr;

//Returns the only instance of this class
CharacterLocalScreen* CharacterLocalScreen::instance(){
    if (!m_instance){
        m_instance = new CharacterLocalScreen(MenuState::getInstance());
    }

    return m_instance;
}

//Constructor
CharacterLocalScreen::CharacterLocalScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    m_game              = Game::getInstance();
    createFromFile("assets/UI/menu_screens/CharacterSelect.cgs");
}

//Destructor
CharacterLocalScreen::~CharacterLocalScreen(){
    std::cout << "~CharacterLocalScreen" << std::endl;
}

//Chooses a character for a player
void CharacterLocalScreen::chooseCharacter(int p_player, int p_character){
    
}

//Enables a player
void CharacterLocalScreen::enablePlayer(int p_player, bool p_playable){
    
}

//Disables a player
void CharacterLocalScreen::disablePlayer(int p_player){
    
}

//Handles the user inputs for the screen
void CharacterLocalScreen::input(){
    //Call to default input for navigation purposes
    MenuScreen::input();

}

//Updates the state of the screen
void CharacterLocalScreen::update(){
    //Call to default update for navigation purposes
    MenuScreen::update();
}










/* ****************************** ACTIONS ****************************** */
void CharacterLocalScreen::select(){
    save();
}

//Create override save method (don't save until everyone chooses)