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

/*
    COSAS POR HACER:
        ATAQUE HACIA ARRIBA (IMPLEMENTAR)
        SI LA TORRETA SE SUICIDA, QUE MUERAN LAS BALAS CON ELLA

    BUGS PARA ARREGLAR:
        SI HACES EL DASH Y CHOCAS CON LA TURRET PETA, MIRAR COMO SOLUCIONARLO
*/

Plup::Plup(char* p_name, float p_position[3], bool p_debugMode, bool p_online) : Character(p_name, p_position, 100, 100, 12, 10.f, "assets/models/characters/plup/plup.obj", p_debugMode, p_online){
    m_type           = 3;

    m_snowmanPlaced  = false;

    m_turretDuration = 15.0;
    m_turretTime     = 0;
    m_basicDuration  = 0.5;
    m_basicTime      = 0;

    if (m_NPC){
        m_AI = new AIPlup(this);
    }
}

Plup::~Plup(){}

bool Plup::jump(){
    return Character::jump();
}

//Slap
bool Plup::basicAttack(){
    float t_currentTime = m_inputManager->getMasterClock();
    if(t_currentTime >= m_basicTime){
        //std::cout << m_name << ": Slap!" << std::endl;
        Character* t_currentPlayer;

        for (int i = 0; i < m_playerCount; i++){
            //Ignore myself
            if (i == m_playerIndex)
                continue;

            t_currentPlayer = Arena::getInstance()->getPlayer(i);

            //Looking at the rival
            if((m_orientation == 1 && t_currentPlayer->getX() >= m_position[0]) || (m_orientation != 1 && t_currentPlayer->getX() <= m_position[0])){
                //Rival close enough
                if(checkCloseness(t_currentPlayer->getPosition(), 15)){                
                    t_currentPlayer->receiveAttack(m_damage/2, true, getOrientation());
                    this->addMP(5);
                }
            }
        }
        m_basicTime = t_currentTime + m_basicDuration;
    }
    ////std::cout << "PLUP MP: " << m_MP << std::endl;

    
    return false;
}

//Range attack
bool Plup::specialAttackUp(){
    if(useMP(30)){
        //std::cout << m_name << ": Range attack" << std::endl;
        Character* t_currentPlayer;

        for (int i = 0; i < m_playerCount; i++){
            //Ignore myself
            if (i == m_playerIndex)
                continue;
            
            t_currentPlayer = Arena::getInstance()->getPlayer(i);
            
            if(t_currentPlayer!=0){
                //Rival close enough
                if (checkCloseness(t_currentPlayer->getPosition(), 35)){
                    t_currentPlayer->receiveAttack(m_damage, true);
                }
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
        m_snowman = new Snowman(m_attackPosition, m_playerIndex);
        //std::cout << m_name << ": Snowman" << std::endl;
        m_snowmanPlaced = true;
        m_turretTime = m_inputManager->getMasterClock() + m_turretDuration;
    }
    return false;
}

//Dash
bool Plup::specialAttackSide(){
    if(m_onGround && useMP(25)){
        //std::cout << m_name << ": Special Attack Side" << std::endl;

        m_physicsManager->getBody(getId())->SetLinearDamping(-0.5);
        m_physicsManager->getBody(getId())->SetLinearVelocity(b2Vec2(4*m_orientation,0));

        //Trigger the atak, if while we are dashing we collide with another player, this player will be stunned and receive damage, also this action finish the dash atak.
        m_dashing = true;
        m_dashTime = m_inputManager->getMasterClock() + m_dashDuration;

        m_stunned = true;

        m_physicsManager->checkCollisionSimple(m_physicsManager->getBody(getId()), true);
    }

    return false;
}

bool Plup::ultimateAttack(){
    if(m_ultimateCharged){
        //std::cout << m_name << ": ULTIMATE TIME!!!" << std::endl;
        Character* t_currentPlayer;

        for(int i = 0; i < m_playerCount; i++){
            //Ignore myself
            if (i == m_playerIndex)
                continue;

            t_currentPlayer = Arena::getInstance()->getPlayer(i);

            t_currentPlayer->setStunned(2.5);
        }
        m_ultimateCharged = false;
    }

    return false;
}

void Plup::updatePlayer(){
    ////std::cout << "PLUP MP: " << m_MP << std::endl;
    if(m_dashing){
        //If time is over or collision, finish atack
        //The second param of collision is true because all dash atacks cause stun
        if(m_inputManager->getMasterClock() > m_dashTime || m_physicsManager->checkCollisionSimple(m_physicsManager->getBody(getId()), true)){
            m_physicsManager->getBody(getId())->SetLinearDamping(0);
            m_dashing = false;
            m_stunned = false;

        }
    }

    if(m_snowmanPlaced){
        updateSnowman();
    }
}

void Plup::updateSnowman(){
    std::cout << "updateSnowman" << std::endl;
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
    //delete m_snowman->getBullet();
    delete m_snowman;
    m_snowman = nullptr;
    m_snowmanPlaced = false;
}

int Plup::getCurrentSnowmen(){
    return m_snowmanPlaced;
}
