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

#include "../include/menu_screens/TitleScreen.hpp"

//Returns the only instance of this class
TitleScreen& TitleScreen::instance(){
    static TitleScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
TitleScreen::TitleScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    createFromFile("assets/UI/menu_screens/Title.cgs");
}

//Destructor
TitleScreen::~TitleScreen(){
    std::cout << "~TitleScreen" << std::endl;
}










/* ****************************** ACTIONS ****************************** */
void TitleScreen::select(){
    save();
}