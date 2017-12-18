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

//Iostream esta incluido en el .hpp
#include "headers/main.hpp"
//#include "headers/debug.hpp"
//#include <iostream>

int main(){
    EngineManager* engineManager = EngineManager::instance();
    InputManager* inputManager = InputManager::instance();
    PhysicsManager* physicsManager = PhysicsManager::instance();


    if (engineManager->createWindow()){  
        float positionRawr[3] = {-10, 15, 0};
        float positionPlup[3] = {10, 15, 0};
        float positionTurret[3] = {30, 25, 0};
        float position[3] = {0, 0, 0};
        float scale[3] = {10, 0.5, 2};

        Character* player1 = new Rawr(positionRawr, "Player 1", 100, 30, 50.f, true);
        Character* player2 = new Plup(positionPlup, "Player 2", 100, 30, 50.f, false);

        engineManager->createCamera();
        Arena* estadio = new Arena(position, scale, "assets/models/estadio.obj");

        engineManager->timeStamp();

        //For players loop
        int i;
        Character* currentPlayer;

        //Game main loop
        while (engineManager->running()){
            engineManager->updateFrameDeltaTime();

            physicsManager->getWorld()->Step(physicsManager->getTimeStep(), physicsManager->getIterations(), 0);

            //Input and update for every character
            for (i = 0; i < Character::getPlayerCount(); i++){
                currentPlayer = Character::getPlayer(i);

                currentPlayer->playerInput();
                currentPlayer->updatePosition(currentPlayer->getBody()->GetPosition().y, currentPlayer->isJumping());
            }

            engineManager->drawScene();
        }

        engineManager->stop();

        return 0;
    }

    return 1;
}
