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

#include "../include/entities/Projectile.hpp"
#include "../include/entities/Arena.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include <cstring> //For std::memcpy()
#include <cmath> //For std::sqrt()
//#include <iostream>

//Static members
const char* Projectile::m_modelURLs[2] = {"assets/models/characters/sparky/sparky_punch.obj", "assets/models/characters/plup/snowball.obj"};

Projectile::Projectile(float p_position[3], float p_target[3], int p_owner, int p_type) : Entity(p_position, 7.f, m_modelURLs[p_type]){
    std::memcpy(m_target, p_target, 3 * sizeof(float));
    m_owner = p_owner;

    std::cout<<"projectile"<<std::endl;
    //Base damage (from its owner)
    int t_damage = Arena::getInstance()->getPlayer(m_owner)->getDamage();

    switch (p_type){
        //Rawr's fireball
        case 0:{
            m_damage = t_damage * 1.333;
            m_velocity = 4.5;
            m_distanceLeft = 120;
            break;
        }

        //Plup's snowmen's snowball
        case 1:{
            m_damage = t_damage/3;
            m_velocity = 3;
            m_distanceLeft = 150;
            break;
        }
    }

    calculateSteps();
}

Projectile::~Projectile(){}

//Precalculates step for each axis
void Projectile::calculateSteps(){
    float t_distanceX, t_distanceY, t_distanceZ, t_distance, t_time;
    
    //d = target - origin
    t_distanceX = m_target[0] - m_position[0];
    t_distanceY = m_target[1] - m_position[1];
    t_distanceZ = m_target[2] - m_position[2];

    //Apply d²=x²+y²+z²
    t_distance = t_distanceX*t_distanceX + t_distanceY*t_distanceY + t_distanceZ*t_distanceZ;
    t_distance = std::sqrt(t_distance);

    //t = d/v
    t_time = t_distance/m_velocity;

    //Velocity in each axis
    //v = d/t
    m_step[0] = t_distanceX/t_time;
    m_step[1] = t_distanceY/t_time;
    m_step[2] = t_distanceZ/t_time;
}

//Checks if projectile hits a player
bool Projectile::hit(){
    Character* t_currentPlayer;
    int t_playerCount = Arena::getInstance()->getPlayerCount();

    for (int i = 0; i < t_playerCount; i++){
        //Ignore owner
        if (i == m_owner)
            continue;

        t_currentPlayer = Arena::getInstance()->getPlayer(i);

        //Rival close enough
        if (checkCloseness(t_currentPlayer->getPosition(), 10)){
            t_currentPlayer->receiveAttack(m_damage, false);
            return true;
        }
    }

    return false;
}

//Moves projectile right or left. Returns false at end of way.
bool Projectile::update(){
    //Go on
    if (m_distanceLeft > 0){
        moveX(m_step[0]);
        moveY(m_step[1]);
        moveZ(m_step[2]);

        if (hit()){
            return false;
        }

        m_distanceLeft -= m_velocity;
    }

    //End of the way, my friend
    else{
        return false;
    }

    return true;
}