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

#include "../include/entities/Snowman.hpp"
#include "../include/entities/Projectile.hpp"
#include "../include/entities/characters/Character.hpp"
#include "../include/entities/Arena.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include <iostream>

//Constructor
Snowman::Snowman(float p_position[3], int p_owner) : Entity(p_position, 3.f, "assets/models/characters/plup/snowman.obj", 5){
    m_physicsManager = &PhysicsManager::instance();
    m_arena          = Arena::getInstance();
    
    m_ammo           = 3;
    m_owner          = p_owner;
    
    m_bulletLaunched = false;
}

//Destructor
Snowman::~Snowman(){}


//Looks for player and fires after finding
bool Snowman::lockNLoad(){
    if(!m_bulletLaunched && m_ammo > 0 && (m_launchClock.getElapsedTime().asSeconds() >= 1.5 || m_ammo == 3)){
        int t_playerCount = m_arena->getPlayerCount();
        Character* t_currentPlayer;
        
        for (int i = 0; i < t_playerCount; i++){
            //Snowman shall not shoot its owner
            if (i == m_owner)
                continue;
            
            t_currentPlayer = m_arena->getPlayer(i);
            m_target[0] = t_currentPlayer->getX();
            m_target[1] = t_currentPlayer->getY();
            m_target[2] = t_currentPlayer->getZ();

            b2Vec2 t_p1 = b2Vec2(m_position[0], m_position[1]);
            b2Vec2 t_p2 = b2Vec2(m_target[0], m_target[1]);

            float t_closestBodyFraction = m_physicsManager->RaycastBetween(t_p1, t_p2);

            //Attack ONLY if in range and in sight
            if(t_closestBodyFraction >= 0.2f){ //If there is not an intersection to the raycast
                //Create snowball (if any left)
                if(m_ammo > 0){
                    m_ammo--;
                    m_snowball = new Projectile(m_position, m_target, true, m_owner, 7, 1);
                    
                    //
                    m_bulletLaunched = true;
                    m_launchClock.restart();
                    break;
                }
            }
        }
    }

    //Update position of the turret (gravity)
    updatePosition(false, false, false);

    //Delete turret when last bullet is gone
    if (m_ammo == -1)
        return false;

    return true;
}

void Snowman::updateBullet(){
    updatePosition(false, false, false);

    if(!m_snowball->update(true)){
        m_bulletLaunched = false;
        delete m_snowball;
        m_snowball = nullptr;
        
        if(m_ammo == 0)
            m_ammo--;
    }
}

Projectile* Snowman::getBullet(){
    return m_snowball;
}

bool Snowman::getBulletLaunched(){
    return m_bulletLaunched;
}