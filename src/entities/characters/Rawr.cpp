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

#include "../../include/entities/characters/Rawr.hpp"
#include "../../include/entities/Arena.hpp"
#include "../../include/extra/Actions.hpp"
#include "../../include/managers/SoundManager.hpp"
#include <iostream>

Rawr::Rawr(char* p_name, float p_position[3], bool p_debugMode)
    : Character(p_name, p_position, 100, 100, 15, 70.f, "assets/models/characters/rawr/rawr.obj", p_debugMode){
    m_type                  = 4;
    
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];

    m_soundManager->loadBank(SoundID::S_RAWR);
    m_soundManager->createSoundEvent("event:/characters/rawr/death"     , "death"       );
    m_soundManager->createSoundEvent("event:/characters/rawr/kill"      , "kill"        );
    m_soundManager->createSoundEvent("event:/characters/rawr/random"    , "random"      );
    m_soundManager->createSoundEvent("event:/characters/rawr/special"   , "special"     );
    m_soundManager->createSoundEvent("event:/characters/rawr/taunt"     , "taunt"       );
    m_soundManager->createSoundEvent("event:/characters/rawr/ultimate"  , "ultimate"    );
    //m_soundManager->modifyParameter("random", 0.95, "Prob");
}

Rawr::~Rawr(){}

bool Rawr::jump(){
    return Character::jump();
}

//Headbutt
bool Rawr::basicAttack(){
    std::cout << m_name << ": Headbutt!" << std::endl;
    Character* t_currentPlayer;
    
    float t_prob = ((float)rand() / (float)RAND_MAX);
    std::cout << "RANDOM: " << t_prob << std::endl;
    m_soundManager->modifyParameter("random", t_prob, "Prob");
    m_soundManager->playSound("random");

    for (int i = 0; i < m_playerCount; i++){
        //Ignore myself
        if (i == m_playerIndex)
            continue;

        t_currentPlayer = Arena::getInstance()->getPlayer(i);

        //Looking at the rival
        if ((m_orientation && t_currentPlayer->getX() >= m_position[0]) ||
        (!m_orientation && t_currentPlayer->getX() <= m_position[0])){
            //Rival close enough
            if (checkCloseness(t_currentPlayer->getPosition(), 15)){
                t_currentPlayer->receiveAttack(m_damage/2, true);
            }
        }
    }

    return false;
}

//Range attack
bool Rawr::specialAttackUp(){
    std::cout << "Range attack" << std::endl;
    Character* t_currentPlayer;

    for (int i = 0; i < m_playerCount; i++){
        //Ignore myself
        if (i == m_playerIndex)
            continue;

        t_currentPlayer = Arena::getInstance()->getPlayer(i);

        //Rival close enough
        if (checkCloseness(t_currentPlayer->getPosition(), 35)){
            t_currentPlayer->receiveAttack(m_damage, true);
        }
    }

    return false;
}

bool Rawr::specialAttackDown(){
    //PENDING IMPLEMENTATION
    std::cout << m_name << ": Special Attack Down" << std::endl;
    
    return false;
}

//Fireball
bool Rawr::specialAttackSide(){
    if (m_currentProjectiles < m_maxProjectiles){
        if(m_orientation){   // Looking right
            // Attack 5 units to the right
            m_attackPosition[0] = m_position[0] + 5;
            m_attackPosition[1] = m_position[1];
            m_attackPosition[2] = m_position[2];

            m_attackTarget[0] = m_position[0] + 100;
            m_attackTarget[1] = m_position[1];
            m_attackTarget[2] = m_position[2];
        }
        else{   // Looking left
            // Attack 5 units to the right
            m_attackPosition[0] = m_position[0] - 5;
            m_attackPosition[1] = m_position[1];
            m_attackPosition[2] = m_position[2];

            m_attackTarget[0] = m_position[0] - 100;
            m_attackTarget[1] = m_position[1];
            m_attackTarget[2] = m_position[2];
        }

        //Create attack and increase projectile count
        m_projectiles[m_currentProjectiles++] = new Projectile(m_attackPosition, m_attackTarget, m_playerIndex, 0);
        std::cout << m_name << ": Fireball" << std::endl;
    }

    //Move projectiles, and delete them
    for (int i = 0; i < m_currentProjectiles; i++){
        if (!m_projectiles[i]->update()){
            delete m_projectiles[i];
            m_currentProjectiles--;
            return false;
        }
    }

    return true;
}

bool Rawr::ultimateAttack(){
    //PENDING IMPLEMENTATION
    std::cout << m_name << ": ULTIMATE TIME!!!" << std::endl;

    m_soundManager->modifyParameter("ultimate", 0.95, "Prob");
    m_soundManager->playSound("ultimate");

    return false;
}