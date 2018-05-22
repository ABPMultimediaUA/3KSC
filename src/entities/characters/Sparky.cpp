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
#include "../../include/managers/EngineManager.hpp"

#include <iostream>

Sparky::Sparky(char* p_name, float p_position[3], bool p_online, bool p_NPC) : Character(p_name, p_position, 150, 70, 65.f, "assets/models/characters/sparky/sparky.obj", p_online, p_NPC){
    m_type               = 4;
    
    m_jumpingDuration    = 0.10;
    m_jumpingTime        = 0;

    m_gravity            = false;
    m_sparkyJumping      = false;
    m_punchLaunched      = false;
    m_ultimateMode       = false;
    m_ultiBulletLaunched = false;
    m_ultimateAmmo       = 10;

    m_damageBasic        = 20.0f;
    m_damageSide         = 35.0f;
    m_damageUp           = 30.0f;
    m_damageDown         = 30.0f;
    m_damageUlti         = 10.0f;

    m_knockbackBasic     = 1.0f;
    m_knockbackSide      = 1.0f;
    m_knockbackUp        = 1.5f;
    m_knockbackDown      = 1.5f;
    m_knockbackUlti      = 0.25f;
    m_system             = -1;

    if(m_NPC){
        toggleAI();
        m_AI = new AISparky(this);
    }

    m_soundManager->loadBank(SoundID::S_SPARKY);
    m_soundManager->loadEvents(SoundID::S_SPARKY);

}

Sparky::~Sparky(){
    std::cout << "~Sparky" << std::endl;

}

bool Sparky::jump(){
    return Character::jump();
}

//Headbutt
bool Sparky::basicAttack(){
    if(!m_ultimateMode){
        Character* t_currentPlayer;

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
                    this->addMP(15);
                }
            }
        }
    }
    return false;
}

bool Sparky::specialAttackUp(){
    if(useMP(10)){
        m_soundManager->modifyParameter("s_atak", 0.5, "Atak");
        m_soundManager->playSound("s_atak");
        m_physicsManager->sparkyJump(getId());
        m_jumpingTime = m_inputManager->getMasterClock() + m_jumpingDuration;
        m_sparkyJumping = true;
        m_system = m_engineManager->createParticleSystem("assets/fire.png", 20, -m_position[0]*5, (10-m_position[1])*(5),150, 0.5, 0, 360, true, 0.5);

    }
    
    return false;
}

bool Sparky::specialAttackDown(){
    if(useMP(20) && !m_ultimateMode){
        m_soundManager->modifyParameter("s_atak", 0.7, "Atak");
        m_soundManager->playSound("s_atak");
        m_physicsManager->shockwaveBox(getId(), m_damageDown, m_knockbackDown);
        m_system = m_engineManager->createParticleSystem("assets/spark.png", 10, -m_position[0]*5, (10-m_position[1])*(5),100, 0.5, 0, 360, true, 1);
        //m_system  = m_engineManager->createParticleSystem("assets/fire.png", 50, -m_position[0], 9- m_position[1], 10, 2, -20, 20, false,30);
    }

    return false;
}

bool Sparky::specialAttackSide(){
    if(!m_punchLaunched && useMP(35) && !m_ultimateMode){
        m_attackPosition[0] = m_position[0] + 0.5*m_orientation;
        m_attackPosition[1] = m_position[1];
        m_attackPosition[2] = m_position[2];
     
        m_attackTarget[0] = m_position[0] + 10*m_orientation;
        m_attackTarget[1] = m_position[1];
        m_attackTarget[2] = m_position[2];

        //Create attack and increase projectile count
        m_punch = new Projectile(m_attackPosition, m_attackTarget, m_orientation, m_playerIndex, m_damageSide, m_knockbackSide, 0);
        m_punchLaunched = true;

        m_soundManager->modifyParameter("s_atak", 0.3, "Atak");
        m_soundManager->playSound("s_atak");
    }

    return false;
}

bool Sparky::ultimateAttack(){
    // m_ultimateCharged = true;
    if(m_ultimateCharged){
        m_ultimateMode = true;
        m_ultimateAmmo = 10;
        m_ultimateCharged = false;
        m_soundManager->modifyParameter("s_ultimate", 0, "Prob");
        m_soundManager->playSound("s_ultimate");
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
    
    //  if(m_system>=0)
    //  {
    //      m_engineManager->particlePosition(m_system, -m_position[0], 9- m_position[1], 0);
    //  }
    randomSounds();
}

void Sparky::updateJump(){
    if(m_inputManager->getMasterClock() > m_jumpingTime){
        if(!m_gravity){
            m_gravity = true;
            m_physicsManager->fastGravity(getId());
        }else if(m_onGround){
            m_gravity       = false;
            m_sparkyJumping = false;
            m_physicsManager->shockwaveBox(getId(), m_damageUp, m_knockbackUp);
            m_physicsManager->resetVelocity(getId());
        }
    }
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
        m_physicsManager->machineGun(getId(), m_orientation, m_damageUlti, m_knockbackUlti, true);
        m_ultiBulletLaunched = true;
        m_ultimateAmmo--;
    }else if(m_ultiBulletLaunched){
        if(!m_ultimateBullet->update(false)){
            delete m_ultimateBullet;
            m_ultimateBullet     = nullptr;
            m_ultiBulletLaunched = false;
        }
    }else{
        m_soundManager->modifyParameter("s_ultimate", 1.0, "Prob");
        m_ultimateMode    = false;
    }
}

void Sparky::randomSounds(){
    if(!m_soundManager->isPlaying("s_random")){
        float t_prob = ((float)rand() / (float)RAND_MAX);
        m_soundManager->modifyParameter("s_random", t_prob, "Prob");
        m_soundManager->playSound("s_random");
    }
}

bool Sparky::tauntSound(){
    m_soundManager->playSound("s_taunt");
    
    return false;
}

void Sparky::deathSound(){
    m_soundManager->playSound("s_death");
}
