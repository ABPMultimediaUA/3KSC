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

#include <irrlicht.h>
//#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "../entities/Entity.hpp"

class EngineManager : public irr::IEventReceiver{
private:
    static EngineManager* m_instance;

    std::vector<irr::scene::ISceneNode*>    m_entityNodes;
    irr::IrrlichtDevice*                    m_device;
    irr::video::IVideoDriver*               m_vDriver;
    irr::scene::ISceneManager*              m_scene;

    irr::u32        m_prevTime;
    irr::u32        m_nowTime;
    irr::f32        m_frameDeltaTime;

    //sf::RenderWindow* m_window;

public:
    static EngineManager* instance();
    EngineManager();
    ~EngineManager();

    bool createWindow(bool p_fullscreen = true);
    bool running();
    void stop();

    virtual bool OnEvent(const irr::SEvent& p_event); 
    void timeStamp();
    float updateFrameDeltaTime();

    void createCamera();
    void createEntity(int p_id, float p_position[3]);
    void deleteEntity(int p_id);
    void load3DModel(int p_id, float p_position[3], float p_scale[3], const char* p_modelURL);
    void loadArena(const char* arenaModelURL);
    void loadSkybox(const char* p_skyboxURLs[6]); 
    void moveEntity(Entity* p_entity);
    void setRotation(int p_id, float p_degrees);
    void scale(int p_id, float p_scale[3]);
    
    void drawScene();

    //sf::RenderWindow* getWindow();
    float getFrameDeltaTime();
    irr::scene::ISceneManager* getSceneManager();
    irr::scene::ISceneNode* getEntityNode(int p_id);






    irr::video::IVideoDriver* getVideoDriver();
    irr::IrrlichtDevice* getDevice();

    void loadCharacter();
    void loadObject();

    void putCharacter();
    void putObject();

    void drawArena();
    void drawCharacter();
    void drawObject();
};

#endif