/********************************************************************************
*********************************************************************************
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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*********************************************************************************
*********************************************************************************/

#include "headers/main.hpp"
#include <iostream>

int main(){
    InputManager* inputManager = InputManager::instance();
    UIManager* uiManager = UIManager::instance();
    Character* player = Character::instance();
    
    sf::RenderWindow* window = uiManager->getWindow();

    bool keyPressed = false;

    //Main loop
    while (window->isOpen()){

        sf::Event* event = new sf::Event;

        while (window->pollEvent(*event)){
            switch (event->type){
                //Close window
                case sf::Event::Closed:{
                    window->close();
                    break;
                }

                //Key detected
                case sf::Event::KeyPressed:{
                    keyPressed = true;
                    break;
                }
            }
        }

        if (keyPressed){
            player->playerInput();
        }

        player->playerUpdate();

        keyPressed = false;

        uiManager->render();

    }
}
