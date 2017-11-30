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

#ifndef ENGINE_MANAGER
#define ENGINE_MANAGER

#include "GraphicManager.hpp"
#include "managers/InputManager.hpp"
#include <irrlicht.h>
using namespace irr;

class EngineManager{
private:
    GraphicManager*         m_graphicManager;
    IrrlichtDevice*         m_device;
    video::IVideoDriver*    m_vDriver;
    scene::ISceneManager*   m_scene;
  
public:
    EngineManager();
    ~EngineManager();

    bool createWindow(InputManager* p_inputManager);
    void drawScene();
    bool deviceIsRunning();
    void dropDevice();

    void createNode();
    void createCamera();

    void loadArena();
    void loadCharacters();
    void loadObjects();

    void putCharacters();
    void putObject();

    void drawArena();
    void drawCharacter();
    void drawObject();
};

#endif