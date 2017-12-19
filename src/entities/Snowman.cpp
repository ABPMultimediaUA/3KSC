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

#include "../headers/entities/Snowman.hpp"
#include "../headers/entities/Character.hpp"
#include "../headers/managers/EngineManager.hpp"

//Constructor
Snowman::Snowman(float p_position[3], int p_owner) : Entity(p_position, 3.f, "assets/models/characters/plup/snowman.obj"){
    m_maxSnowballs          = 1;
    m_currentSnowballs      = 0;
    m_snowballs             = new Projectile*[m_maxSnowballs];
    m_ammo                  = 6;

    m_owner                 = p_owner;
}

//Destructor
Snowman::~Snowman(){}


//Looks for player and fires after finding
bool Snowman::lockNLoad(){
    if (m_ammo > 0){
        if (m_currentSnowballs < m_maxSnowballs){
            int t_playerCount = Character::getPlayerCount();
            Character* t_currentPlayer;

            for (int i = 0; i < t_playerCount; i++){
                //Snowman shall not shoot its owner
                if (i == m_owner)
                    continue;

                t_currentPlayer = Character::getPlayer(i);
                m_target[0] = t_currentPlayer->getX();
                m_target[1] = t_currentPlayer->getY();
                m_target[2] = t_currentPlayer->getZ();
                
                //Create snowball (if any left)
                if (m_ammo-- > 0){        
                    m_snowballs[m_currentSnowballs] = new Projectile(m_position, m_target, 30, 4, 200);
                    m_currentSnowballs++;
                }
            }
        }
    }

    //Update position and delete snowballs
    for (int i = 0; i < m_currentSnowballs; i++){
        if (!m_snowballs[i]->update()){
            delete m_snowballs[i];
            m_currentSnowballs--;
            
            if (m_ammo == 0)
                m_ammo--;
        }
    }

    //Delete turret when last bullet is gone
    if (m_ammo == -1){
        EngineManager::instance()->deleteEntity(this->getId());
        getBody()->GetWorld()->DestroyBody(getBody());
        
        return false;
    }

    return true;
}