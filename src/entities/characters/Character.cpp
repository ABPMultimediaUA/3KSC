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


#include "../include/entities/characters/Character.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/managers/InputManager.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/managers/UIManager.hpp"
#include "../include/entities/Arena.hpp"
#include "../include/extra/Actions.hpp"

#include <iostream>

struct ActionMapping{
    Action  action;                     //Action to map
    void    (Character::*function)();   //Function for the action
    bool    onlyOnce;                   //Wait for input release?
    bool    enabled;                    //Enabled or not
};

//Static members
int Character::m_playerCount = 0;

Character::Character(char* p_name, float p_position[3], int p_life, int p_magic, int p_damage, float p_velocity, const char* p_modelURL, bool p_debugMode) : Entity(p_position, 5.f, p_modelURL){
    m_name                  = p_name;
    m_lives                 = 3;
    m_life                  = p_life;
    m_magic                 = p_magic;
    m_maxLife               = p_life;
    m_maxMagic              = p_magic;
    m_damage                = p_damage;
    m_velocity              = p_velocity;
    m_stunned               = false;  
    m_blocking              = false;
    m_shielded              = false;
    m_winged                = false;    
    m_alive                 = true;
    m_respawning            = false;

    m_runningFactor         = 1;

    m_maxJumps              = 2;
    m_jumping               = false;
    m_jumpCurrentTime       = 0;
    m_jumpMaxTime           = 10;
    m_jumpTable[0]          = 3.0f;
    m_jumpTable[1]          = 2.4f;
    m_jumpTable[2]          = 1.9f;
    m_jumpTable[3]          = 1.6f;
    m_jumpTable[4]          = 1.25f;
    m_jumpTable[5]          = 0.95;
    m_jumpTable[6]          = 0.75;
    m_jumpTable[7]          = 0.55;
    m_jumpTable[8]          = 0.35;
    m_jumpTable[9]          = 0.15;

    mapActions();

    m_waitRelease           = false;

    m_playerIndex = Character::m_playerCount++;

    switch(m_playerIndex){
        case 0:
            lookRight();
            break;
        case 1:
            lookLeft();
            break;
    }

    m_debugMode = p_debugMode;

}

Character::~Character(){}

//Initializes actions mapping for this player
void Character::mapActions(){
    m_actions = new ActionMapping[(int) Action::Count + 1];

                      //Action                    //Function                      //onlyOnce  //Enabled
    m_actions[0]    = {Action::Left               , &Character::left              , false     , false};
    m_actions[1]    = {Action::Right              , &Character::right             , false     , false};
    m_actions[2]    = {Action::Jump               , &Character::jump              , true      , false};
    m_actions[3]    = {Action::Run                , &Character::run               , false     , false};
    m_actions[4]    = {Action::Block              , &Character::block             , false     , false};
    m_actions[5]    = {Action::Pick               , &Character::pick              , false     , false};
    m_actions[6]    = {Action::BassicAttack       , &Character::basicAttack       , true      , false};
    m_actions[7]    = {Action::SpecialAttackUp    , &Character::specialAttackUp   , true      , false};
    m_actions[8]    = {Action::SpecialAttackDown  , &Character::specialAttackDown , true      , false};
    m_actions[9]    = {Action::SpecialAttackSide  , &Character::specialAttackSide , true      , false};
    m_actions[10]   = {Action::UltimateAttack     , &Character::ultimateAttack    , true      , false};
    m_actions[11]   = {Action::Count              , 0                             , false     , false};
}

//Receives an attack from other player
//Parameters: damage, can you block it?
void Character::receiveAttack(int p_damage, bool p_block){
    if((p_block && m_actions[(int) Action::Block].enabled) || m_shielded)
    {
        changeLife(-p_damage/2);
        std::cout << m_name << " blocked an attack and now has " << m_life << " HP." << std::endl << std::endl;
    }else{
        changeLife(-p_damage);
        std::cout << m_name << " took an attack and now has " << m_life << " HP." << std::endl << std::endl;
    }
}

//Increases or decreases life
void Character::changeLife(int p_variation){
    m_life += p_variation;

    if (m_life <= 0){
        m_life = 0;
        die();
    }
    
    else if (m_life > m_maxLife){
        m_life = m_maxLife;
    }

    //HUD Stuff
    UIManager::instance()->setLife(m_playerIndex, m_life);
}

//Increases or decreases magic
void Character::changeMagic(int p_variation){
    m_magic += p_variation;

    if (m_magic < 0)
        m_magic = 0;
    
    else if (m_magic > m_maxMagic)
        m_magic = m_maxMagic;

    //HUD Stuff
}

//Activates shield
void Character::shield(){
    m_shielded = true;
}

//Activates wings, if not already active
void Character::wings(){
    if (!m_winged){
        m_velocity *= 1.5f;
        m_winged = true;
    }
}

//Decreases number of lives
void Character::die(){
    m_lives--;
    //m_alive = false;
    Arena::getInstance()->respawnPlayer(m_playerIndex);
    //HUD Stuff

    //Delete when m_lives == 0
}

void Character::lookLeft(){
    if(m_orientation){
        m_orientation = false;
        this->rotate(0);
    }
}

void Character::lookRight(){
    if(!m_orientation){
        m_orientation = true;
        this->rotate(180);
    }
}

bool Character::isJumping(){
    return m_actions[(int) Action::Jump].enabled;
}


//Calls action functions when they are active
void Character::doActions(){
    ActionMapping* t_iterator = m_actions;

    while(t_iterator->function){
        if(t_iterator->enabled){
            (this->*(t_iterator->function))();
        }

        ++t_iterator;
    }

    /*
    if(m_jumping)
        jump();

    if(m_basicAttack){
        changeMagic(5);
        basicAttack();
    }

    if(m_specialAttackUp){
        if(m_magic >= 30){
            changeMagic(-30);
            specialAttackUp();
        }
    }

    if(m_specialAttackDown){
        if(m_magic >= 35){
            changeMagic(-35);
            specialAttackDown();
        }
    }

    if(m_specialAttackSide){
        if(m_magic >= 25){
            changeMagic(-25);
            specialAttackSide();
        }
    }

    if(m_ultimateAttack){
        EngineManager::instance()->moveCamera(getX(), getY(), getZ());
        ultimateAttack();
    }
    */
}

void Character::input(){
    InputManager* t_inputManager = InputManager::instance();
    t_inputManager->updateInputs(m_playerIndex);
    //m_frameDeltaTime = EngineManager::instance()->getFrameDeltaTime();

//    //Change to keyboard (RETURN KEY)
//    if (t_inputManager->isKeyPressed(58)){
//        t_inputManager->assignDevice(-1, m_playerIndex);
//    }
//    
//    //Change to joystick (START BUTTON)
//    t_inputManager->updateJoysticks();
//    if (t_inputManager->isButtonPressed(0, 7)){
//        t_inputManager->assignDevice(0, m_playerIndex);
//    }
//
//    //Exit
//    if(t_inputManager->isKeyPressed(Key_Escape))
//        EngineManager::instance()->stop();
//
//    if(t_inputManager->isKeyPressed(15)){
//        EngineManager::instance()->resetCamera();
//    }


    //Block
    m_actions[(int) Action::Block].enabled = t_inputManager->checkInput(Action::Block, m_playerIndex);

    //Input blocked if stunned, blocking or dead
    if(!m_stunned && !m_actions[(int) Action::Block].enabled && m_alive){

        ActionMapping* t_iterator = m_actions;
        bool           t_keepWaiting = false;
        
        //Loop through actions to enable them
        while(t_iterator->function){
            if (t_inputManager->checkInput(t_iterator->action, m_playerIndex)){
                //Wait for release (if necesary)
                if (t_iterator->onlyOnce){
                    t_keepWaiting = true;

                    if (!m_waitRelease){
                        t_iterator->enabled = true;
                        m_waitRelease = true;
                    }
                }

                else{
                    t_iterator->enabled = true;
                }
            }

            //If an "onlyOnce" input is detected, we still have to wait for release
            m_waitRelease = t_keepWaiting;

            ++t_iterator;
        }

        /*
        //Jump
        // 10 frames going up, where gravity is disabled. Then gravity gets enabled again
        if(t_inputManager->checkAction(Action_Jump, m_playerIndex) && m_maxJumps > 0){
            if (!m_waitRelease){
                m_jumping = true;
                m_waitRelease = true;
            }
        }

        //Basic Attack
        else if(t_inputManager->checkAction(Action_BasicAttack, m_playerIndex)){
            if (!m_waitRelease){
                m_basicAttack = true;
                m_waitRelease = true;
            }
        }

        //Special attack up
        else if(t_inputManager->checkAction(Action_SpecialAttackUp, m_playerIndex)){
            if (!m_waitRelease){
                m_specialAttackUp = true;
                m_waitRelease = true;
            }
        }

        //Special attack down
        else if(t_inputManager->checkAction(Action_SpecialAttackDown, m_playerIndex)){
            if (!m_waitRelease){
                m_specialAttackDown = true;
                m_waitRelease = true;
            }
        }

        //Special attack side
        else if(t_inputManager->checkAction(Action_SpecialAttackSide, m_playerIndex)){
            if (!m_waitRelease){
                m_specialAttackSide = true;
                m_waitRelease = true;
            }
        }

        //Ultimate Attack
        else if(t_inputManager->checkAction(Action_UltimateAttack, m_playerIndex)){
            if (!m_waitRelease){
                m_ultimateAttack = true;
                m_waitRelease = true;
            }
        }

        //No attack
        else{
            m_waitRelease = false;
        }

        m_runningFactor = 1;

        //Sprint
        if(t_inputManager->checkAction(Action_Run, m_playerIndex)){
            if(m_winged){
                m_runningFactor = 1.5f;
            }
            else{
                m_runningFactor = 2.0f;
            }
            //std::cout << m_name << " is running" << std::endl;
        }

        //Left
        if(t_inputManager->checkAction(Action_Left, m_playerIndex)){
            moveX(m_velocity * m_frameDeltaTime * m_runningFactor * -1);
            lookLeft();
        }

        //Right
        if(t_inputManager->checkAction(Action_Right, m_playerIndex)){
            moveX(m_velocity * m_frameDeltaTime * m_runningFactor);
            lookRight();
        }

        //Pick object
        if (t_inputManager->checkAction(Action_Pick, m_playerIndex)){
            pickItem();
        }
        */
    }    
}

//Update state of player
void Character::update(){
    doActions();
    
    if(!m_respawning)
        updatePosition(m_actions[(int) Action::Jump].enabled);
    else{
        updatePosition(true);
        m_respawning = false;
    }
    if(m_debugMode)
        playerDebug->update();
    //Increase magic every second and with attacks
    if(getY() < -200 || getY() > 200 || getX() < -230 || getX() > 230){
        die();
    }

    if(m_maxJumps < 2){
        if(PhysicsManager::instance()->isTouchingGround()){
            //std::cout << m_name << " - Tocando el suelo" << std::endl;
            m_maxJumps = 2;
        }
        else
            //std::cout << m_name << " - En el airee" << std::endl;
    }
}

//Returns the damage of the player
int Character::getDamage(){
    return m_damage;
}

//Returns the index of the player
int Character::getIndex(){
    return m_playerIndex;
}

//Returns the name of the player
char* Character::getName(){
    return m_name;
}

//Returns the life of the player
int Character::getLife(){
    return m_life;
}

void Character::modeDebug(){
    if(m_debugMode)
        playerDebug = new Debug(666, PhysicsManager::instance()->getBody(Arena::getInstance()->getPlayer(m_playerIndex)->getId()));
}

void Character::respawn(float p_position[3]){
    m_respawning = true;
    moveTo(p_position);
    m_life = m_maxLife;
    m_magic = m_maxMagic;
    m_shielded = false;

    if(m_winged){
        m_velocity /= 1.5f;
        m_winged = false;
    }

    UIManager::instance()->setLife(m_playerIndex, m_life);
}










//ACTIONS
void Character::left(){
    moveX(m_velocity * m_frameDeltaTime * m_runningFactor * -1);
    lookLeft();
}

void Character::right(){
    moveX(m_velocity * m_frameDeltaTime * m_runningFactor);
    lookRight();
}

void Character::jump(){
    // Start or continue jump movement
    if(m_jumpCurrentTime < m_jumpMaxTime){
        moveY(m_jumpTable[m_jumpCurrentTime++]*2);
    }
    // Jump has ended. Starting to go down
    else{
        // If there is collision
        m_maxJumps--;
        m_jumpCurrentTime = 0;
        m_actions[(int) Action::Jump].enabled = false; // We are on the floor. Reset jump
    }
}

void Character::run(){
    if(m_winged){
        m_runningFactor = 1.5f;
    }
    else{
        m_runningFactor = 2.0f;
    }
}

void Character::block(){
    m_actions[(int) Action::Block].enabled = true;
}

void Character::pick(){
    int t_itemType = Arena::getInstance()->catchItem(m_playerIndex, m_position);
    
    switch (t_itemType){
        //Life tank
        case 0:{
            std::cout << m_name <<" got a Life Tank." << std::endl
            << m_name << "'s life is now " << m_life << " HP." << std::endl << std::endl;
            break;
        }

        //Shield
        case 1:{
            std::cout << m_name <<" got a Shield." << std::endl
            << m_name << "'s now protected against attacks." << std::endl << std::endl;
            break;
        }

        //Wings
        case 2:{
            std::cout << m_name <<" got Wings." << std::endl
            << m_name << "'s speed increased." << std::endl << std::endl;
            break;
        }

        //Fosforian Obedience Automatic Hammer (F.O.A.H)
        case 3:{
            std::cout << m_name <<" got a F.O.A.H." << std::endl
            << m_name << "'s going to make rivals suffer." << std::endl << std::endl;
            break;
        }

        default:{
            //std::cout << "No object here" << std::endl;
        }
    }
}

void Character::basicAttack(){}

void Character::specialAttackUp(){}

void Character::specialAttackDown(){}

void Character::specialAttackSide(){}

void Character::ultimateAttack(){}