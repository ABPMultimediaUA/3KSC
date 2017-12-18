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

#include "../headers/entities/Plup.hpp"

Plup::Plup(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation) : Character(p_position, p_name, p_life, p_damage, p_velocity, p_orientation){
    //For its OWN projectiles, not snowmen ones
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];


    m_maxSnowmen        = 1;
    m_currentSnowmen    = 0;
    m_snowmen           = new Snowman*[m_maxSnowmen];
}

Plup::~Plup(){}

void Plup::jump(){
    Character::jump();
}

void Plup::basicAttack(){
    if (m_basicAttack){

        //PENDING IMPLEMENTATION

        m_basicAttack = false;
    }
}

void Plup::specialAttackUp(){
    if (m_specialAttackUp){

        //PENDING IMPLEMENTATION

        m_specialAttackUp = false;
    }
}

//Place snowmen
void Plup::specialAttackDown(){
    if (m_specialAttackDown){
        if (m_currentSnowmen < m_maxSnowmen){
            //Looking right
            if (m_orientation){
                // Place snowman 10 units to the right
                m_attackPosition[0] = m_position[0] + 10;
                m_attackPosition[1] = m_position[1];
                m_attackPosition[2] = m_position[2];
            }

            //Looking left
            else{
                // Place snowman 10 units to the left
                m_attackPosition[0] = m_position[0] - 10;
                m_attackPosition[1] = m_position[1];
                m_attackPosition[2] = m_position[2];
            }

            //Create snowman and increase snowmen count
            m_snowmen[m_currentSnowmen++] = new Snowman(m_attackPosition, m_playerIndex);
        }

        //Snowmen AI
        for (int i = 0; i < m_currentSnowmen; i++){
            if (!m_snowmen[i]->lockNLoad()){
                m_currentSnowmen--;
                m_specialAttackDown = false;
            }
        }
    }
}

void Plup::specialAttackSide(){
    if (m_specialAttackSide){
    
        //PENDING IMPLEMENTATION
        
        m_specialAttackSide = false;
    }
}


void Plup::ultimateAttack(){
    if (m_ultimateAttack){

        //PENDING IMPLEMENTATION

        m_ultimateAttack = false;
    }
}