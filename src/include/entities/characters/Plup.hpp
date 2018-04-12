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

#ifndef PLUP
#define PLUP

class Snowman;

#include "Character.hpp"
#include <SFML/System/Clock.hpp>

class Plup: public Character {
public:
    Plup(char* p_name, float p_position[3], bool p_debugMode, bool p_online = false);
    ~Plup();
    bool        jump();
    bool        basicAttack();
    bool        specialAttackUp();
    bool        specialAttackDown();
    bool        specialAttackSide();
    bool        ultimateAttack();
    void        updatePlayer();
    int         getCurrentSnowmen();


private:
    bool        m_snowmanPlaced;

    int         m_maxSnowmen;
    Snowman*    m_snowman;

    sf::Clock   m_turretClock;
    sf::Clock   m_basicClock;

    float           m_turretDuration;
    float           m_turretTime;
    float           m_basicDuration;
    float           m_basicTime;

    void        updateSnowman();
    void        deleteSnowman();
};

#endif