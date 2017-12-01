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

bool collision(scene::ISceneNode* one, scene::ISceneNode* two) {
   core::aabbox3d<f32> b1, b2;

   b1 = one->getBoundingBox();
   b2 = two->getBoundingBox();

   one->getRelativeTransformation().transformBoxEx(b1);
   two->getRelativeTransformation().transformBoxEx(b2);
   return b1.intersectsWithBox(b2);
}

core::vector3df calculateRadius(scene::ISceneNode* object){
    const core::aabbox3d<f32>& box = object->getBoundingBox();
    core::vector3df radius = box.MaxEdge - box.getCenter();

    return radius;
}

int main(){

    //TODO: Los nodos se crean en la Fachada, luego la informacion que guardan
    //se convierte a nuestro formato y se le pasa a las Entidades mediante
    //GraphicManager

    EngineManager* engineManager = EngineManager::instance();
    GraphicManager* graphicManager = GraphicManager::instance();
    InputManager* inputManager = InputManager::instance();

    if (graphicManager->createWindow()){  

        //Rawr* pRawr = new Rawr();
        engineManager->createCubeNode();
        graphicManager->createCamera();
        /////////////

        //Game main loop
        while (graphicManager->running()){
            /////////

            graphicManager->draw();
        }

        graphicManager->stop();

        return 0;
    }

    return 1;
}
