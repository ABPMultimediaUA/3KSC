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

#include "../include/menu_screens/MainScreen.hpp"
#include "../include/managers/EngineManager.hpp"
#include <iostream>

//Returns the only instance of this class
MainScreen& MainScreen::instance(){
    static MainScreen instance(MenuState::getInstance());
    return instance;
}

//Constructor
MainScreen::MainScreen(MenuState* p_menu)
    : MenuScreen(p_menu){
    createFromFile("assets/UI/menu_screens/Main.cgs");
}

//Destructor
MainScreen::~MainScreen(){
    std::cout << "~MainScreen" << std::endl;
}

//Draws to the screen
void MainScreen::render(){
    m_engineManager->drawScene2D();
}