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

#include "../headers/entities/Projectile.hpp"
#include "../headers/managers/EngineManager.hpp"
#include <cstring> //For std::memcpy()

Projectile::Projectile(float p_position[3], bool p_orientation, float p_velocity, float p_distanceLeft, int p_damage):Entity(p_position){
    std::memcpy(m_initialPosition, p_position, 3 * sizeof(float));
    m_orientation   = p_orientation;
    m_velocity      = p_velocity;
    m_distanceLeft  = p_distanceLeft;
    m_damage        = p_damage;
}

Projectile::~Projectile(){}

bool Projectile::hit(){
    
}

//Moves projectile right or left. Returns false at end of way.
bool Projectile::move(){
    //Go on
    if (m_distanceLeft > 0){
        //Right
        if (m_orientation){
            moveX(m_velocity);
        }

        //Left
        else{
            moveX(-m_velocity);
        }

        m_distanceLeft -= m_velocity;
    }

    //End of the way, my friend
    else{
        EngineManager::instance()->deleteEntity(this->getId());
        return false;
    }

    return true;
}