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
    along with this program.  If not, see <http://www.gnu.org/m_licenses/>.m_

    m_You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*********************************************************************************
*********************************************************************************/

#include "headers/debug.hpp"
#include "headers/managers/EngineManager.hpp"
#include <iostream>

Debug::Debug(s32 p_id, b2Body* p_body): scene::ISceneNode(EngineManager::instance()->getSceneManager()->getRootSceneNode(), EngineManager::instance()->getSceneManager(), p_id) {
    m_Material.Wireframe = false;
    m_Material.Lighting = false;

    video::SColor red = video::SColor(50,255,0,0);

    m_body = p_body;
    b2Fixture* t_fixture = p_body->GetFixtureList();
    while(t_fixture != NULL){
        b2Shape* t_shape = t_fixture->GetShape();
        if(t_shape->GetType() == 2){
            m_shape = static_cast<b2PolygonShape*>(t_shape);
        
            int t_bodyPositionX = m_body->GetPosition().x;
            int t_bodyPositionY = m_body->GetPosition().y;

            int t_count = m_shape->GetVertexCount();
            std::cout << "++++++++++++++++++" << std::endl;
            for(int i = 0; i < t_count; i++){
                b2Vec2 t_verts = m_shape->GetVertex(i);
                m_posVertex[i][0] = t_verts.x + t_bodyPositionX;
                m_posVertex[i][1] = t_verts.y + t_bodyPositionY;
                std::cout << "(" << t_verts.x << "," << t_verts.y << ")\n";
            }
            
            for(int i = 0; i < 4; i++){
                m_VerticesVector.push_back(video::S3DVertex(m_posVertex[i][0], m_posVertex[i][1],0, 0,0,0, red, 0, 0));
            }
        }
        t_fixture = t_fixture->GetNext();
    }
    render();
}

void Debug::OnRegisterSceneNode(){
    if(IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void Debug::render(){
    u16 indices[] = {0,2,3, 2,1,3, 1,0,3, 2,0,1};
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    int t_times = m_VerticesVector.size();

    for(int i = 0; i < t_times; i++){
        for(int j = 0; j < 4; j++){
            m_Vertices[j] = m_VerticesVector.back();
            m_VerticesVector.pop_back();   
        }
        driver->setMaterial(m_Material);
        driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        driver->drawVertexPrimitiveList(&m_Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
    }
}

const core::aabbox3d<f32>& Debug::getBoundingBox() const{
    return m_Box;
}

u32 Debug::getMaterialCount() const{
    return 1;
}

video::SMaterial& Debug::getMaterial(u32 i){
    return m_Material;
}

void Debug::update(){
    video::SColor red = video::SColor(50,255,0,0);
    
    b2Fixture* t_fixture = m_body->GetFixtureList();

    while(t_fixture != NULL){
        b2Shape* t_shape = t_fixture->GetShape();
        if(t_shape->GetType() == 1){
            m_shape = static_cast<b2PolygonShape*>(t_shape);
        
            int t_bodyPositionX = m_body->GetPosition().x;
            int t_bodyPositionY = m_body->GetPosition().y;

            int t_count = m_shape->GetVertexCount();
            for(int i = 0; i < t_count; i++){
                b2Vec2 t_verts = m_shape->GetVertex(i);
                m_posVertex[i][0] = t_verts.x + t_bodyPositionX;
                m_posVertex[i][1] = t_verts.y + t_bodyPositionY;
            }
            
            for(int i = 0; i < 4; i++){
                m_VerticesVector.push_back(video::S3DVertex(m_posVertex[i][0], m_posVertex[i][1],0, 0,0,0, red, 0, 0));
            }
        }
        t_fixture = t_fixture->GetNext();
    }
}