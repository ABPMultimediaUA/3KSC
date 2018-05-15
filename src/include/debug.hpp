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

#ifndef DEBUG
#define DEBUG

#include <Box2D.h>
#include <vector>
/*
class Debug : public scene::ISceneNode{
public:
    Debug(b2Body* p_body, int p_num);
    void OnRegisterSceneNode();
    void render();
    const core::aabbox3d<f32>& getBoundingBox() const;
    u32 getMaterialCount() const;
    video::SMaterial& getMaterial(u32 i);

    void update();
private:
    core::aabbox3d<f32> m_Box;
    video::S3DVertex    m_Vertices[4];
    video::SMaterial    m_Material;
    video::SColor       m_color;
    std::vector<video::S3DVertex>    m_VerticesVector;
    
    b2Body*             m_body;
    b2Shape*            m_shape;
    float               m_posVertex[4][2];
};
*/
#endif 
