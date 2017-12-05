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

Projectile::Projectile(float p_position[3], float p_angle):Entity(p_position){
    std::memcpy(m_initialPosition, p_position, 3 * sizeof(float));
    m_angle     = p_angle;
    m_velocity  = 10;
    m_lifeTime  = 100;
    m_damage    = 30;
}

Projectile::~Projectile(){}

bool Projectile::hit(){
    
}

//Moves projectile in the direction the angle tells
void Projectile::move(){
    
}