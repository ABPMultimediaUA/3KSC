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


class Item;
class Debug;

#include "characters/Character.hpp"
#include <SFML/System/Clock.hpp>
//#include "Skybox.hpp"
//#include "Texture.hpp"
//#include "WaterLily.hpp"
//#include "Branch.hpp"
//#include "Platform.hpp"
//#include "GravityZone.hpp"


class Arena : public Entity {
public:
    Arena(float p_position[3], float p_scale[3], int p_arenaIndex, bool p_debugMode = false);
    ~Arena();
    static Arena*   getInstance();
    void            spawnPlayers();
    void            addPlayer();
    int             getPlayerCount();
    Character*      getPlayer(int p_index);
	void            spawnItems();
    int             catchItem(int p_owner, float p_where[3]);
	void            finishRound();
    void            movePlatforms();
    void            animateBackground();
    void            restart();
    void            setSpawnPositions();
    void            respawnPlayer(int p_player);
    void            update();
    bool            spawnRandomItem();
    void            setSkybox(int p_arenaIndex);
    void            modeDebug();
    void            onlineUpdate();
    void            spawnItemAt(int p_type, int x, int y);

private: 
    static Arena* m_instance;
    static const char*  m_modelURLs[3];
	static const char*  m_skyboxURLs[3][6];
    //Texture*    m_background;
    float       m_time;
    float       m_spawnPosition[3]; // First []: index. Second []: [0] for x, [1] for y, [2] for z
    
    int         m_maxItems;
    int         m_currentItems;
    Item**      m_items;
    int         m_spawningTime;
    int         m_spawnedItems;
    int         m_usedItems;
    int         m_maxItemsOnScreen = 5;

    int         m_playerCount;
    Character** m_players;

    Debug*      m_debugBattlefield;
    bool        m_debugMode;

    float       m_spawnPositions[4][3];

    sf::Clock*  m_clock;

    //WaterLily*   m_waterLilys;
    //Branch*      m_branches;
    //Platform*    m_platforms;
    //GravityZone* m_gravityZones;
};

#endif