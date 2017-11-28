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

class MyEventReceiver : public IEventReceiver {
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

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
    // create device
    MyEventReceiver receiver;

    // create a NULL device to detect screen resolution
    IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);

    core::dimension2d<u32> desktopResolution = nulldevice->getVideoModeList()->getDesktopResolution();

    nulldevice -> drop();

    // now the dimensions can be used to create the real device
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, desktopResolution, 16, true, false, false, &receiver);

    if(!device)
        return 1;

    device->setWindowCaption(L"Pruebas");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();

    //**********************************************************
    //                          PLAYER
    //**********************************************************
    Character * p1 = new Character(driver,smgr);

    scene::ITriangleSelector* enemySelector = 0;
    scene::ISceneNode * enemyNode = smgr->addCubeSceneNode();
    if (enemyNode){
        enemyNode->setPosition(core::vector3df(10,5,0));
        enemyNode->setMaterialFlag(video::EMF_LIGHTING, false);
        enemySelector = smgr->createTriangleSelectorFromBoundingBox(enemyNode);
    }

    //**********************************************************
    //                          MAP
    //**********************************************************
    //scene::IAnimatedMesh* mapMesh = smgr->getMesh("assets/map.dae");
    //scene::ISceneNode* mapNode = smgr->addAnimatedMeshSceneNode(mapMesh);
    //mapNode->setMaterialFlag(video::EMF_LIGHTING,false);
    //mapNode->setPosition(core::vector3df(0,0,0));
    //mapNode->setScale(core::vector3df(2,2,2));
    //std::cout << mapMesh->getMeshBufferCount() << std::endl;

    //**********************************************************
    //                          FLOOR
    //**********************************************************
    scene::ISceneNode * floorNode = smgr->addCubeSceneNode();
    if(floorNode){
        floorNode->setPosition(core::vector3df(0,-10,0));
        floorNode->setMaterialFlag(video::EMF_LIGHTING, false);
        floorNode->setScale(core::vector3df(15,0.5,2));
        floorNode->setMaterialTexture(0, driver->getTexture("../assets/wall.bmp"));
        scene::ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(floorNode);
        floorNode->setTriangleSelector(selector);
        selector->drop();
    }

    scene::ISceneNode * floorNode2 = smgr->addCubeSceneNode();
    if(floorNode2){
        floorNode2->setPosition(core::vector3df(-100,6,0));
        floorNode2->setMaterialFlag(video::EMF_LIGHTING, false);
        floorNode2->setScale(core::vector3df(10,0.5,2));
        floorNode2->setMaterialTexture(0, driver->getTexture("../assets/wall.bmp"));
        scene::ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(floorNode2);
        floorNode2->setTriangleSelector(selector);
        selector->drop();       
    }

    //Creo un meta en el cual guardo todos los TriangeSelector del suelo para hacer las colisiones con el jugador
    scene::IMetaTriangleSelector* meta = smgr->createMetaTriangleSelector();
    meta->addTriangleSelector(floorNode->getTriangleSelector());   
    meta->addTriangleSelector(floorNode2->getTriangleSelector());

    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(meta, p1->getNode(),
        calculateRadius(p1->getNode()),core::vector3df(0,-10,0), core::vector3df(0,0,0));
    p1->getNode()->addAnimator(anim);
    anim->drop();

    anim = smgr->createCollisionResponseAnimator(meta, enemyNode,
        calculateRadius(enemyNode),core::vector3df(0,-10,0), core::vector3df(0,0,0));
    enemyNode->addAnimator(anim);
    anim->drop();

    meta->drop();
    meta = smgr->createMetaTriangleSelector();
    meta->addTriangleSelector(enemyNode->getTriangleSelector());
    meta->addTriangleSelector(p1->getNode()->getTriangleSelector());

    anim = smgr->createCollisionResponseAnimator(meta, p1->getNode(),
        calculateRadius(p1->getNode()),core::vector3df(0,0,0), core::vector3df(0,0,0));
    p1->getNode()->addAnimator(anim);
    anim->drop();

    //**********************************************************
    //                          CAMERA
    //**********************************************************
    scene::ICameraSceneNode * cameraNode = smgr->addCameraSceneNode();
    if(cameraNode){
        cameraNode->setPosition(core::vector3df(0,35,-100));
        cameraNode->setTarget(core::vector3df(floorNode->getPosition().X, floorNode->getPosition().Y+25,floorNode->getPosition().Z));
    }

    int lastFPS = -1;

    // In order to do framerate independent movement, we have to know
    // how long it was since the last frame
    u32 then = device->getTimer()->getTime();

    // This is the movemen speed in units per second.
    const f32 MOVEMENT_SPEED = 50.f;
    int run = 1;

    while(device->run())
    {
        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        //UPDATE PLAYER (MOVEMENT)
        core::vector3df nodePosition = p1->getNode()->getPosition();

        if(receiver.IsKeyDown(irr::KEY_SPACE))
            nodePosition.Y += MOVEMENT_SPEED*3 * frameDeltaTime;

        if(receiver.IsKeyDown(irr::KEY_ESCAPE))
            device->drop();

        run = 1;
        if(receiver.IsKeyDown(irr::KEY_LSHIFT))
            run = 2;

        if(receiver.IsKeyDown(irr::KEY_KEY_A))
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime * run;
        else if(receiver.IsKeyDown(irr::KEY_KEY_D))
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime * run;

        p1->getNode()->setPosition(nodePosition);

        //UPDATE ENEMY (MOVEMENT)
        core::vector3df nodePositionEnemy = enemyNode->getPosition();
        if(abs(enemyNode->getPosition().X - p1->getNode()->getPosition().X) > 1){
            if(enemyNode->getPosition().X < p1->getNode()->getPosition().X)
                nodePositionEnemy.X += MOVEMENT_SPEED/2 * frameDeltaTime;
            else
                nodePositionEnemy.X -= MOVEMENT_SPEED/2 * frameDeltaTime;

            if(!collision(p1->getNode(), enemyNode))
                enemyNode->setPosition(nodePositionEnemy);
        }

        driver->beginScene(true, true, video::SColor(255,100,100,140));

        smgr->drawAll();

        driver->endScene();
    }

    device->drop();

    return 0;
}
