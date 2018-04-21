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

#include "../../include/entities/characters/Sparky.hpp"
#include "../../include/AI/AISparky.hpp"
#include "../../include/entities/Arena.hpp"
#include "../../include/extra/Actions.hpp"
#include "../../include/managers/SoundManager.hpp"
#include "../../include/managers/PhysicsManager.hpp"
#include "../../include/managers/InputManager.hpp"
#include <iostream>

Sparky::Sparky(char* p_name, float p_position[3], bool p_online) : Character(p_name, p_position, 100, 100, 15, 70.f, "assets/models/characters/sparky/sparky.obj", p_online){
    m_type                  = 4;
    
    m_sparkyJumping      = false;
    m_punchLaunched      = false;
    m_ultimateMode       = false;
    m_ultiBulletLaunched = false;
    m_ultimateAmmo       = 10;

    /*m_soundManager->loadBank(SoundID::S_SPARKY);
    m_soundManager->createSoundEvent("event:/characters/rawr/death"     , "death"       );
    m_soundManager->createSoundEvent("event:/characters/rawr/kill"      , "kill"        );
    m_soundManager->createSoundEvent("event:/characters/rawr/random"    , "random"      );
    m_soundManager->createSoundEvent("event:/characters/rawr/special"   , "special"     );
    m_soundManager->createSoundEvent("event:/characters/rawr/taunt"     , "taunt"       );
    m_soundManager->createSoundEvent("event:/characters/rawr/ultimate"  , "ultimate"    );*/
    //m_soundManager->modifyParameter("random", 0.95, "Prob");

    if(m_NPC)
        m_AI = new AISparky(this);

    m_damageBasic    = 5.0f;
    m_damageSide     = 15.0f;
    m_damageUp       = 50.0f;
    m_damageDown     = 15.0f;
    m_damageUlti     = 10.0f;

    m_knockbackBasic = 1.0f;
    m_knockbackSide  = 1.0f;
    m_knockbackUp    = 1.0f;
    m_knockbackDown  = 1.0f;
    m_knockbackUlti  = 1.0f;

}

Sparky::~Sparky(){}

bool Sparky::jump(){
    return Character::jump();
}

//Headbutt
bool Sparky::basicAttack(){
    if(!m_ultimateMode){
        Character* t_currentPlayer;
        
        /*float t_prob = ((float)rand() / (float)RAND_MAX);
        //std::cout << "RANDOM: " << t_prob << std::endl;
        m_soundManager->modifyParameter("random", t_prob, "Prob");
        m_soundManager->playSound("random");*/

        for(int i = 0; i < m_playerCount; i++){
            //Ignore myself
            if(i == m_playerIndex)
                continue;

            t_currentPlayer = Arena::getInstance()->getPlayer(i);

            //Looking at the rival
            if((m_orientation == 1 && t_currentPlayer->getX() >= m_position[0]) || (m_orientation != 1 && t_currentPlayer->getX() <= m_position[0])){
                //Rival close enough
                if(checkCloseness(t_currentPlayer->getPosition(), 1.5)){
                    t_currentPlayer->receiveAttack(m_damageBasic, true, m_knockbackBasic, getOrientation());
                    this->addMP(5);
                }
            }
        }
    }
    return false;
}

//Range attack
bool Sparky::specialAttackUp(){
    
    return false;
}

bool Sparky::specialAttackDown(){
    if(useMP(35) && !m_ultimateMode)   
        m_physicsManager->shockwaveBox(getId(), m_damageDown, m_knockbackDown);

    return false;
}

bool Sparky::specialAttackSide(){
    if(!m_punchLaunched && useMP(25) && !m_ultimateMode){
        m_attackPosition[0] = m_position[0] + 0.5*m_orientation;
        m_attackPosition[1] = m_position[1];
        m_attackPosition[2] = m_position[2];
     
        m_attackTarget[0] = m_position[0] + 10*m_orientation;
        m_attackTarget[1] = m_position[1];
        m_attackTarget[2] = m_position[2];

        //Create attack and increase projectile count
        m_punch = new Projectile(m_attackPosition, m_attackTarget, m_orientation, m_playerIndex, m_damageSide, m_knockbackSide, 0);
        m_punchLaunched = true;
    }

    return false;
}

bool Sparky::ultimateAttack(){
    //m_soundManager->modifyParameter("ultimate", 0.95, "Prob");
    //m_soundManager->playSound("ultimate");
    if(m_ultimateCharged){
        m_ultimateMode = true;
        m_ultimateAmmo = 10;
        m_ultimateCharged = false;
    }

    return false;
}

void Sparky::updatePlayer(){
    if(m_punchLaunched)
        updatePunch();

    if(m_sparkyJumping)
        updateJump();

    if(m_ultimateMode)
        updateUltimate();
}

void Sparky::updateJump(){
    m_physicsManager->fastGravity(getId());
}

void Sparky::updatePunch(){
    //Move projectiles, and delete them
    if(!m_punch->update(true)){
        delete m_punch;
        m_punch = nullptr;
        m_punchLaunched = false;
    }
}

void Sparky::updateUltimate(){
    if(!m_ultiBulletLaunched && m_ultimateAmmo > 0){
        m_attackPosition[0] = m_position[0] + 0.5*m_orientation;
        m_attackPosition[1] = m_position[1];
        m_attackPosition[2] = m_position[2];
     
        m_attackTarget[0] = m_position[0] + 10*m_orientation;
        m_attackTarget[1] = m_position[1];
        m_attackTarget[2] = m_position[2];
        
        m_ultimateBullet = new Projectile(m_attackPosition, m_attackTarget, m_orientation, m_playerIndex, m_damageSide, m_knockbackSide, 2);
        m_physicsManager->machineGun(getId(), m_orientation, m_damageUlti, m_knockbackUlti);
        m_ultiBulletLaunched = true;
        m_ultimateAmmo--;
    }else if(m_ultiBulletLaunched){
        if(!m_ultimateBullet->update(false)){
            delete m_ultimateBullet;
            m_ultimateBullet     = nullptr;
            m_ultiBulletLaunched = false;
        }
    }else
        m_ultimateMode    = false;
}