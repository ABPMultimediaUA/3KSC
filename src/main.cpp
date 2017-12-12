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

int main(){

    //TODO: Los nodos se crean en la Fachada, luego la informacion que guardan
    //se convierte a nuestro formato y se le pasa a las Entidades mediante
    //GraphicManager

    EngineManager* engineManager = EngineManager::instance();
    InputManager* inputManager = InputManager::instance();
    PhysicsManager* physicsManager = PhysicsManager::instance();

    if (engineManager->createWindow()){  
        float positionPlayer[3] = {0, 10, 0};
        float position[3] = {0, 0, 0};
        float scale[3] = {10, 0.5, 2};

        Character* player1 = new Rawr(positionPlayer, "Player 1", 100, 30, 50.f, true);
        Arena* testArena = new Arena(position, scale);
        engineManager->createCamera();

        engineManager->timeStamp();

        //Game main loop
        while (engineManager->running()){
            engineManager->updateFrameDeltaTime();

            physicsManager->getWorld()->Step(physicsManager->getTimeStep(), physicsManager->getIterations(), 0);
            
            player1->playerInput();
            player1->updatePosition(player1->getBody()->GetPosition().y, player1->isJumping());
            //std::cout << "(" << player1->getBody()->GetPosition().x << "," << player1->getBody()->GetPosition().y << ")" << std::endl;

            engineManager->drawScene();
        }

        engineManager->stop();

        return 0;
    }

    return 1;
}
