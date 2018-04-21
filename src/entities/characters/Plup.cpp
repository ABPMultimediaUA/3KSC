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

#include "../../include/entities/characters/Plup.hpp"
#include "../../include/AI/AIPlup.hpp"
#include "../../include/entities/Snowman.hpp"
#include "../../include/entities/Arena.hpp"
#include "../../include/extra/Actions.hpp"
#include "../../include/managers/PhysicsManager.hpp"
#include "../../include/managers/InputManager.hpp"
//#include "../../include/managers/SoundManager.hpp"
#include <iostream>

Plup::Plup(char* p_name, float p_position[3], bool p_online) : Character(p_name, p_position, 100, 100, 12, 80.f, "assets/models/characters/plup/plup.obj", p_online){
    m_type              = 3;

    m_snowmanPlaced     = false;
    m_ultimateMode      = false;

    m_turretDuration    = 15.0f;
    m_turretTime        = 0.0f;
    m_basicDuration     = 0.5f;
    m_basicTime         = 0.0f;
    m_ultimateDuration  = 3.0f;
    m_ultimateTime      = 0.0f;

    m_damageBasic       = 5.0f;
    m_damageSide        = 15.0f;
    m_damageUp          = 50.0f;
    m_damageDown        = 15.0f;
    m_damageUlti        = 15.0f;

    m_knockbackBasic    = 1.0f;
    m_knockbackSide     = 1.0f;
    m_knockbackUp       = 1.0f;
    m_knockbackDown     = 1.0f;
    m_knockbackUlti     = 2.5f;

    if(m_NPC)
        m_AI = new AIPlup(this);
}

Plup::~Plup(){}

bool Plup::jump(){
    return Character::jump();
}

//Slap
bool Plup::basicAttack(){
    float t_currentTime = m_inputManager->getMasterClock();
    if(t_currentTime >= m_basicTime){
        Character* t_currentPlayer;

        for (int i = 0; i < m_playerCount; i++){
            //Ignore myself
            if (i == m_playerIndex)
                continue;

            t_currentPlayer = Arena::getInstance()->getPlayer(i);

            //Looking at the rival
            if((m_orientation == 1 && t_currentPlayer->getX() >= m_position[0]) || (m_orientation != 1 && t_currentPlayer->getX() <= m_position[0])){
                //Rival close enough
                if(checkCloseness(t_currentPlayer->getPosition(), 1.5)){
                    if(!m_ultimateMode)
                        t_currentPlayer->receiveAttack(m_damageBasic, true, m_knockbackBasic, getOrientation());
                    else
                        t_currentPlayer->receiveAttack(m_damageUlti, true, m_knockbackUlti, getOrientation());
                    this->addMP(5);
                }
            }
        }
        m_basicTime = t_currentTime + m_basicDuration;
    }
    return false;
}

//Range attack
bool Plup::specialAttackUp(){
    if(useMP(30)){
        Character* t_currentPlayer;

        for(int i = 0; i < m_playerCount; i++){
            //Ignore myself
            if(i == m_playerIndex)
                continue;
            
            t_currentPlayer = Arena::getInstance()->getPlayer(i);
            if(t_currentPlayer != 0){
                //Rival close enough
                if(checkCloseness(t_currentPlayer->getPosition(), 3.5))
                    t_currentPlayer->receiveAttack(m_damageUp, true, m_knockbackBasic, getOrientation());
            }
        }
    }
    return false;
}

//Snowman
bool Plup::specialAttackDown(){
    if(!m_snowmanPlaced && useMP(35)){
        m_attackPosition[0] = m_position[0] + 1*m_orientation;
        m_attackPosition[1] = m_position[1];
        m_attackPosition[2] = m_position[2];

        //Create snowman and increase snowmen count
        m_snowman = new Snowman(m_attackPosition, m_playerIndex, m_damageDown, m_knockbackDown);
        m_snowmanPlaced = true;
        m_turretTime = m_inputManager->getMasterClock() + m_turretDuration;
    }
    return false;
}

//Dash
bool Plup::specialAttackSide(){
    if(m_onGround && !m_dashing && useMP(25)){
        //Trigger the atak, if while we are dashing we collide with another player, this player will be stunned and receive damage, also this action finish the dash atak.
        m_dashTime = m_inputManager->getMasterClock() + m_dashDuration;
        m_dashing = true;

        m_physicsManager->dash(getId(), m_orientation);
        m_physicsManager->checkCollisionSimple(m_physicsManager->getBody(getId()), true, m_damageSide, m_damageSide);
    }

    return false;
}

bool Plup::ultimateAttack(){
    if(m_ultimateCharged){
        m_ultimateMode = true;

        Character* t_currentPlayer;
        for(int i = 0; i < m_playerCount; i++){
            //Ignore myself
            if(i == m_playerIndex)
                continue;

            t_currentPlayer = Arena::getInstance()->getPlayer(i);
            t_currentPlayer->setStunned(3.0);
        }
        m_ultimateTime = m_inputManager->getMasterClock() + m_ultimateDuration;
        m_ultimateCharged = false;
    }

    return false;
}

void Plup::updatePlayer(){
    if(m_inputManager->getMasterClock() > m_ultimateTime)
        m_ultimateMode = false;
    
    if(m_dashing)
        updateDash();

    if(m_snowmanPlaced)
        updateSnowman();
}

void Plup::updateSnowman(){
    //Snowmen AI
    if(m_inputManager->getMasterClock() < m_turretTime){
        if(!m_snowman->getBulletLaunched()){
            if(!m_snowman->lockNLoad())
                deleteSnowman();
        }else
            m_snowman->updateBullet();
    }else if(m_snowman->getBulletLaunched())
        m_snowman->updateBullet();
    else
        deleteSnowman();
}

void Plup::deleteSnowman(){
    delete m_snowman;
    m_snowman = nullptr;
    m_snowmanPlaced = false;
}

int Plup::getCurrentSnowmen(){
    return m_snowmanPlaced;
}

void Plup::updateDash(){
    if(m_inputManager->getMasterClock() < m_dashTime){
        m_physicsManager->dash(getId(), m_orientation);
        if(m_physicsManager->checkCollisionSimple(m_physicsManager->getBody(getId()), true, m_damageSide, m_damageSide)){
            m_physicsManager->resetVelocity(getId());
            m_dashing = false;
        }
    }else{
        m_physicsManager->resetVelocity(getId());
        m_dashing = false;
    }
}