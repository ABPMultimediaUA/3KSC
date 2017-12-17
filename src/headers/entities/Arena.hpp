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

#ifndef ARENA
#define ARENA

#include "Entity.hpp"
//#include "Skybox.hpp"
//#include "Texture.hpp"
//#include "Item.hpp"
//#include "WaterLily.hpp"
//#include "Branch.hpp"
//#include "Platform.hpp"
//#include "GravityZone.hpp"

class Arena : public Entity {
public:
	        Arena(float p_position[3], float p_scale[3], const char* arenaModelURL);
            ~Arena();
	void    finishRound();
	void    spawnItem();
    void    spawnPlayer();
    void    movePlatforms();
    void    animateBackground();
    void    restart();
private: 
	//Skybox*     m_skybox;
    //Texture*    m_background;
    float       m_time;
    float       m_spawnPosition[3]; // First []: index. Second []: [0] for x, [1] for y, [2] for z
    //Item*       m_itemsToSpawn;

    //WaterLily*   m_waterLilys;
    //Branch*      m_branches;
    //Platform*    m_platforms;
    //GravityZone* m_gravityZones;
};

#endif