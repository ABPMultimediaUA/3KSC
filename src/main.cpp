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
//#include <fmod.h>
//#include <iostream>

int main(){
    EngineManager* engineManager = EngineManager::instance();
    InputManager* inputManager = InputManager::instance();
    PhysicsManager* physicsManager = PhysicsManager::instance();
    SoundManager*   soundManager = SoundManager::instance();
    UIManager*      uiManager = UIManager::instance();

    if (engineManager->createWindow(false)){  
        float position[3] = {0, 1, 0};
        float scale[3] = {120, 0.5, 2};
        Arena* estadio = new Arena(position, scale, 0, false);
        
        estadio->spawnPlayers();
        estadio->spawnItems();

        engineManager->createCamera();
        engineManager->timeStamp();

        // Play music
        Sound t_music;
        soundManager->createSound(&t_music,"assets/FosfosStadium.mp3");
        soundManager->playSound(t_music, true);

        //For players loop
        int i, playerCount = Arena::getInstance()->getPlayerCount();
        Character* currentPlayer;

        //Game main loop
        while (engineManager->running()){
            //sf::Context context;
            soundManager->update();
            engineManager->updateFrameDeltaTime();

            physicsManager->getWorld()->Step(physicsManager->getTimeStep(), physicsManager->getIterations(), 0);

            //Input and update for every character
            for (i = 0; i < playerCount; i++){
                currentPlayer = Arena::getInstance()->getPlayer(i);

                currentPlayer->playerInput();
                currentPlayer->playerUpdate();
            }
            engineManager->drawScene();
        }
        engineManager->stop();
        return 0;
    }
    return 1;
}
