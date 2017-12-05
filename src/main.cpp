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

int main(){

    //TODO: Los nodos se crean en la Fachada, luego la informacion que guardan
    //se convierte a nuestro formato y se le pasa a las Entidades mediante
    //GraphicManager

    EngineManager* engineManager = EngineManager::instance();
    InputManager* inputManager = InputManager::instance();

    if (engineManager->createWindow()){  
        float positionPlayer[3] = {0, 10, 0};
        float position[3] = {0, 0, 0};
        float scale[3] = {10, 0.5, 2};

        Rawr* player1 = new Rawr(positionPlayer, "Player 1", 100, 30, 20, true);
        Arena* testArena = new Arena(position, scale);
        engineManager->createCamera();

        inputManager->timeStamp();

        //Game main loop
        while (engineManager->running()){
            inputManager->updateFrameDeltaTime();
            inputManager->playerInput(player1);

            engineManager->drawScene();
        }

        engineManager->stop();

        return 0;
    }

    return 1;
}
