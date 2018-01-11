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


#include "../headers/entities/Character.hpp"
#include "../headers/managers/EngineManager.hpp"
#include "../headers/managers/InputManager.hpp"
#include "../headers/managers/PhysicsManager.hpp"
#include "../headers/managers/UIManager.hpp"
#include "../headers/extra/Keycodes.hpp"
#include "../headers/extra/Axis.hpp"
#include "../headers/extra/Buttons.hpp"
#include "../headers/entities/Arena.hpp"
#include <iostream>

//Static members
int Character::m_playerCount = 0;

Character::Character(char* p_name, float p_position[3], int p_joystick, int p_life, int p_magic, int p_damage, float p_velocity, const char* p_modelURL, bool p_debugMode) : Entity(p_position, 5.f, p_modelURL){
    m_name                  = p_name;
    m_joystick              = p_joystick;
    m_lives                 = 3;
    m_life                  = p_life;
    m_magic                 = p_magic;
    m_maxLife               = p_life;
    m_maxMagic              = p_magic;
    m_damage                = p_damage;
    m_velocity              = p_velocity;
    m_orientation           = true;
    m_stunned               = false;  
    m_blocking              = false;
    m_shielded              = false;
    m_winged                = false;    

    m_runningFactor         = 1;

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

    m_basicAttack           = false;
    m_specialAttackUp       = false;
    m_specialAttackDown     = false;
    m_specialAttackSide     = false;
    m_ultimateAttack        = false;

    m_waitRelease           = false;


    m_playerIndex = Character::m_playerCount++;

    m_soundManager = SoundManager::instance();
    m_soundManager->createSound(&soundSteps, "assets/pasos_1.wav");

    m_debugMode = p_debugMode;

}

Character::~Character(){}

//Receives an attack from other player
//Parameters: damage, can you block it?
void Character::receiveAttack(int p_damage, bool p_block){
    if((p_block && m_blocking) || m_shielded)
    {
        std::cout << m_name << " blocked an attack and his life remains " << m_life << " HP." << std::endl << std::endl;
    }else{
        changeLife(-p_damage);
        std::cout << m_name << " took an attack and now has " << m_life << " HP." << std::endl << std::endl;
    }
}

//Increases or decreases life
void Character::changeLife(int p_variation){
    m_life += p_variation;

    if (m_life < 0){
        m_life = 0;
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
        m_velocity *= 2;
        m_winged = true;
    }
}

//Decreases number of lives
void Character::die(){
    m_lives--;
    
    //HUD Stuff

    //Delete when m_lives == 0
}


void Character::lookLeft(){
    m_orientation = false;
}

void Character::lookRight(){
    m_orientation = true;
}

bool Character::isJumping(){
    return m_jumping;
}

//Assing joystick with index p_joystick (-1 for Keyboard)
void Character::assignJoystick(int p_joystick){
    //Only assign to player 2 for now
    if (m_playerIndex == 1)
        m_joystick = p_joystick;
}


//Updates joysticks state and booleans for each action
void Character::updateInputs(){
    InputManager* t_inputManager = InputManager::instance();
    
    //Update joysticks state first
    t_inputManager->updateJoysticks();

    //Keyboard input
    if (m_joystick == -1){

        /* Controls:
            *   Left/Right or A/D           Movement
            *   Space                       Jump
            *   E                           Basic Attack
            *   X + Up/W                    Up Special Attack
            *   X + Down/S                  Down Special Attack
            *   X + Left/Right or A/D       Side Special Attack
            *   Q                           Pick item
            *   B                           Block
            *   LShift/RShift               Run
            *   Z                           Ultimate Attack
        */

        m_upInput = t_inputManager->isKeyPressed(Key_W) || t_inputManager->isKeyPressed(Key_Up);
        m_downInput = t_inputManager->isKeyPressed(Key_S) || t_inputManager->isKeyPressed(Key_Down);
        m_leftInput = t_inputManager->isKeyPressed(Key_A) || t_inputManager->isKeyPressed(Key_Left);
        m_rightInput = t_inputManager->isKeyPressed(Key_D) || t_inputManager->isKeyPressed(Key_Right);
        
        m_jumpInput = t_inputManager->isKeyPressed(Key_Space);
        m_runInput = t_inputManager->isKeyPressed(Key_LShift) || t_inputManager->isKeyPressed(Key_RShift);
        m_blockInput = t_inputManager->isKeyPressed(Key_B);
        m_pickInput = t_inputManager->isKeyPressed(Key_Q);
        
        m_basicAttackInput = t_inputManager->isKeyPressed(Key_E);
        m_specialAttackUpInput = t_inputManager->isKeyPressed(Key_X) && m_upInput;
        m_specialAttackDownInput = t_inputManager->isKeyPressed(Key_X) && m_downInput;
        m_specialAttackSideInput = t_inputManager->isKeyPressed(Key_X) && (m_leftInput || m_rightInput);
        m_ultimateAttackInput = t_inputManager->isKeyPressed(Key_Z);
    }

    //Joystick input 
    else if (m_joystick != -2){

        /* Controls (XBOX 360 Controller):
            *   Left/Right      Movement
            *   A               Jump
            *   X               Basic Attack
            *   B + Up          Up Special Attack
            *   B + Down        Down Special Attack
            *   B + Left/Right  Side Special Attack
            *   Y               Pick item
            *   LB              Block
            *   RB              Run
            *   LT + RT         Ultimate Attack
        */

        m_upInput = t_inputManager->getAxisPosition(m_joystick, Axis_Y) <= -75 || t_inputManager->getAxisPosition(m_joystick, Axis_PovY) == -100;
        m_downInput = t_inputManager->getAxisPosition(m_joystick, Axis_Y) >= 75 || t_inputManager->getAxisPosition(m_joystick, Axis_PovY) == 100;
        m_leftInput = t_inputManager->getAxisPosition(m_joystick, Axis_X) <= -75 || t_inputManager->getAxisPosition(m_joystick, Axis_PovX) == -100;
        m_rightInput = t_inputManager->getAxisPosition(m_joystick, Axis_X) >= 75 || t_inputManager->getAxisPosition(m_joystick, Axis_PovX) == 100;

        m_jumpInput = t_inputManager->isButtonPressed(m_joystick, Button_A);
        m_runInput = t_inputManager->isButtonPressed(m_joystick, Button_RB);
        m_blockInput = t_inputManager->isButtonPressed(m_joystick, Button_LB);
        m_pickInput = t_inputManager->isButtonPressed(m_joystick, Button_Y);

        m_basicAttackInput = t_inputManager->isButtonPressed(m_joystick, Button_X);
        m_specialAttackUpInput = t_inputManager->isButtonPressed(m_joystick, Button_B) && m_upInput;
        m_specialAttackDownInput = t_inputManager->isButtonPressed(m_joystick, Button_B) && m_downInput;
        m_specialAttackSideInput = t_inputManager->isButtonPressed(m_joystick, Button_B) && (m_leftInput || m_rightInput);
        m_ultimateAttackInput = t_inputManager->getAxisPosition(m_joystick, Axis_Z) >= 0 && t_inputManager->getAxisPosition(m_joystick, Axis_R) >= 0;
    }

    //NPC
    else{
        m_upInput = false;
        m_downInput = false;
        m_leftInput = false;
        m_rightInput = false;
        
        m_jumpInput = false;
        m_runInput = false;
        m_blockInput = false;
        m_pickInput = false;
        
        m_basicAttackInput = false;
        m_specialAttackUpInput = false;
        m_specialAttackDownInput = false;
        m_specialAttackSideInput = false;
        m_ultimateAttackInput = false;
    }
}

//Calls action functions when they are active
void Character::checkActions(){
    if (m_jumping)
        jump();

    if (m_basicAttack)
        basicAttack();

    if (m_specialAttackUp)
        specialAttackUp();

    if (m_specialAttackDown)
        specialAttackDown();

    if (m_specialAttackSide)
        specialAttackSide();

    if (m_ultimateAttack)
        ultimateAttack();
}

void Character::playerInput(){
    InputManager* t_inputManager = InputManager::instance();
    m_frameDeltaTime = EngineManager::instance()->getFrameDeltaTime();

    updateInputs();

    //Change to keyboard
    //if (t_inputManager->isKeyPressed(Key_Return)){
    //    assignJoystick(-1);
    //}

    //Change to joystick (START BUTTON)
    if (t_inputManager->isButtonPressed(0, Button_Start)){
        assignJoystick(0);
    }

    //Exit
    if(t_inputManager->isKeyPressed(Key_Escape))
        EngineManager::instance()->stop();

    if(!m_stunned)
    {
        //Jump
        // 10 frames going up, where gravity is disabled. Then gravity gets enabled again
        if(m_jumpInput){
            if (!m_waitRelease){
                m_jumping = true;
                m_waitRelease = true;
            }
        }

        //Basic Attack
        else if(m_basicAttackInput){
            if (!m_waitRelease){
                m_basicAttack = true;
                m_waitRelease = true;
            }
        }

        //Special attack up
        else if(m_specialAttackUpInput){
            if (!m_waitRelease){
                m_specialAttackUp = true;
                m_waitRelease = true;
            }
        }

        //Special attack down
        else if(m_specialAttackDownInput){
            if (!m_waitRelease){
                m_specialAttackDown = true;
                m_waitRelease = true;
            }
        }

        //Special attack side
        else if(m_specialAttackSideInput){
            if (!m_waitRelease){
                m_specialAttackSide = true;
                m_waitRelease = true;
            }
        }

        //Ultimate Attack
        else if(m_ultimateAttackInput){
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
        if(m_runInput){
            m_runningFactor = 2;
            //std::cout << m_name << " is running" << std::endl;
        }

        //Left
        if(m_leftInput){
            if(!m_soundManager->isPlaying(&soundSteps))
                m_soundManager->playSound(soundSteps, false);
            moveX(m_velocity * m_frameDeltaTime * m_runningFactor * -1);
            lookLeft();
        }

        //Right
        if(m_rightInput){
            if(!m_soundManager->isPlaying(&soundSteps))
                m_soundManager->playSound(soundSteps, false);
            moveX(m_velocity * m_frameDeltaTime * m_runningFactor);
            lookRight();
        }

        //Block
        m_blocking = m_blockInput;
        if (m_blocking){
            //std::cout << m_name << " is blocking" << std::endl;
        }

        //Pick object
        if (m_pickInput){
            pickItem();
        }

    }
    checkActions();    
}

//Update state of player
void Character::playerUpdate(){
    updatePosition(m_jumping);
    if(m_debugMode)
        playerDebug->update();
    //Increase magic every second and with attacks
}

void Character::jump(){
    // Start or continue jump movement
    if(m_jumpCurrentTime < m_jumpMaxTime){
        moveY(m_jumpTable[m_jumpCurrentTime++]*2);
    }
    else{                                                                       // Jump has ended. Starting to go down
        // Activate gravity
        // Check collision with the floor
        // If there is collision
        m_jumping = false;                                                          // We are on the floor. Reset jump
        m_jumpCurrentTime = 0;
    }
}

void Character::pickItem(){
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