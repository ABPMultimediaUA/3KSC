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
#include "../../include/entities/Snowman.hpp"
#include "../../include/entities/Arena.hpp"
#include "../../include/extra/Actions.hpp"
#include "../../include/managers/PhysicsManager.hpp"
//#include "../../include/managers/SoundManager.hpp"
#include <iostream>

/*
    COSAS POR HACER:
        ATAQUE HACIA ARRIBA (IMPLEMENTAR)
        SI LA TORRETA SE SUICIDA, QUE MUERAN LAS BALAS CON ELLA
*/

Plup::Plup(char* p_name, float p_position[3], bool p_debugMode)
    : Character(p_name, p_position, 100, 100, 12, 80.f, "assets/models/characters/plup/plup.obj", p_debugMode){
    m_type                  = 3;
    
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];

    m_snowmanPlaced = false;
}

Plup::~Plup(){}

bool Plup::jump(){
    return Character::jump();
}

//Slap
bool Plup::basicAttack(){
    std::cout << m_name << ": Slap!" << std::endl;
    Character* t_currentPlayer;

    for (int i = 0; i < m_playerCount; i++){
        //Ignore myself
        if (i == m_playerIndex)
            continue;

        t_currentPlayer = Arena::getInstance()->getPlayer(i);

        //Looking at the rival
        if((m_orientation && t_currentPlayer->getX() >= m_position[0]) || (!m_orientation && t_currentPlayer->getX() <= m_position[0])){
            //Rival close enough
            if(checkCloseness(t_currentPlayer->getPosition(), 15)){                
                t_currentPlayer->receiveAttack(m_damage/2, true);
                t_currentPlayer->knockback(getOrientation());
                this->changeMP(5);
            }
        }
    }
    
    return false;
}

//Range attack
bool Plup::specialAttackUp(){
    if(m_MP >= 30){
        changeMP(-30);
        std::cout << m_name << ": Range attack" << std::endl;
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
    }
    return false;
}

//Snowman
bool Plup::specialAttackDown(){
    if(!m_snowmanPlaced && m_MP >= 35){
        changeMP(-35);
        //Looking right
        if(m_orientation)
            m_attackPosition[0] = m_position[0] + 10;   // Place snowman 10 units to the right
        else
            m_attackPosition[0] = m_position[0] - 10;   // Place snowman 10 units to the left
        
        m_attackPosition[1] = m_position[1];
        m_attackPosition[2] = m_position[2];

        //Create snowman and increase snowmen count
        m_snowman = new Snowman(m_attackPosition, m_playerIndex);
        std::cout << m_name << ": Snowman" << std::endl;
        m_snowmanPlaced = true;
        m_turretClock.restart();
    }

    return false;
}

void Plup::updateSnowman(){
    //Snowmen AI
    if(m_turretClock.getElapsedTime().asSeconds() < 15.0){
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
    m_snowman = 0;
    m_snowmanPlaced = false;
}

//Dash
bool Plup::specialAttackSide(){
    if(m_onGround && m_MP >= 25){
        changeMP(-25);
        std::cout << m_name << ": Special Attack Side" << std::endl;
        Character* t_currentPlayer;

        int t_side = 1;
        //True => Right
        if(!m_orientation)
            t_side = -1;

        m_physicsManager->getBody(getId())->SetLinearDamping(-0.5);
        m_physicsManager->getBody(getId())->SetLinearVelocity(b2Vec2(10*t_side,0));

        //Trigger the atak, if while we are dashing we collide with another player, this player will be stunned and receive damage, also this action finish the dash atak.
        m_dashing = true;
        m_dashClock.restart();

        m_physicsManager->checkCollision(m_physicsManager->getBody(getId()), true);
    }

    return false;
}

bool Plup::ultimateAttack(){
    //PENDING IMPLEMENTATION
    std::cout << m_name << ": ULTIMATE TIME!!!" << std::endl;

    return false;
}

int Plup::getCurrentSnowmen(){
    return m_currentSnowmen;
}

void Plup::updatePlayer(){
    //std::cout << "PLUP MP: " << m_MP << std::endl;
    if(m_dashing){
        //If time is over or collision, finish atack
        //The second param of collision is true because all dash atacks cause stun
        if(m_dashClock.getElapsedTime().asSeconds() > 0.5 || m_physicsManager->checkCollision(m_physicsManager->getBody(getId()), true)){
            m_physicsManager->getBody(getId())->SetLinearDamping(0);
            m_dashing = false;
        }
    }

    if(m_snowmanPlaced)
        updateSnowman();
}
