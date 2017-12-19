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
#include "../headers/managers/InputManager.hpp"
#include "../headers/managers/EngineManager.hpp"
#include "../headers/extra/Keycodes.hpp"
#include "../headers/extra/Axis.hpp"
#include "../headers/extra/Buttons.hpp"
#include <iostream>

//Static members
Character** Character::m_players = new Character*[4];
int Character::m_playerCount = 0;

Character::Character(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation, int p_joystick):Entity(p_position){
    m_name                  = p_name;
    m_life                  = p_life;
    m_damage                = p_damage;
    m_velocity              = p_velocity;
    m_orientation           = p_orientation;
    m_stunned     = false;  
    m_blocking    = false;    

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

    m_joystick              = p_joystick;

    m_playerIndex = Character::m_playerCount++;
    Character::m_players[m_playerIndex] = this;

    m_soundManager = SoundManager::instance();
    m_soundManager->createSound(&soundSteps, "assets/pasos_1.wav");
}

Character::~Character(){}

void Character::reciveAttack(int p_damage, bool p_orientation, bool p_block, float p_force){ //damage, side of the attack, can you block it?, dragging force
    if(p_block && m_blocking && p_orientation == m_orientation)
    {
        //attack blocked
        //use p_force
    }else{
        m_life -= p_damage;
        //use p_force
        if(m_life<=0){
            //die
        }
    }
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
            *   Q                           Pick object
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
    else{

        /* Controls (XBOX 360 Controller):
            *   Left/Right      Movement
            *   A               Jump
            *   X               Basic Attack
            *   B + Up          Up Special Attack
            *   B + Down        Down Special Attack
            *   B + Left/Right  Side Special Attack
            *   Y               Pick object
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
    //if (t_inputManager->isButtonPressed(0, Button_Start)){
    //    assignJoystick(0);
    //}

    //Exit
    if(t_inputManager->isKeyPressed(Key_Escape))
        EngineManager::instance()->stop();

    if(!m_stunned)
    {
        //Jump
        // 10 frames going up, where gravity is disabled. Then gravity gets enabled again
        if(m_jumpInput){
            m_jumping = true;     // Begin jump movement
        }

        m_runningFactor = 1;

        //Basic Attack
        if(m_basicAttackInput){
            m_basicAttack = true;
        }

        //Special attack up
        if (m_specialAttackUpInput){
            m_specialAttackUp = true;
        }

        //Special attack down
        if (m_specialAttackDownInput){
            m_specialAttackDown = true;
        }

        //Special attack side
        if (m_specialAttackSideInput){
            m_specialAttackSide = true;
        }

         //Ultimate Attack
        if(m_ultimateAttackInput){
            m_ultimateAttack = true;
        }

        //Sprint
        if(m_runInput){
            m_runningFactor = 2;
            std::cout << "Running" << std::endl;
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
        if (m_blocking)
            std::cout << "Blocking" << std::endl;

        //Pick object
        if (m_pickInput)
            pickObject();

    }

    checkActions();    
}

void Character::jump(){
    // Start or continue jump movement
    if(m_jumpCurrentTime < m_jumpMaxTime){
        moveY(m_jumpTable[m_jumpCurrentTime++]*3);
    }
    else{                                                                       // Jump has ended. Starting to go down
        // Activate gravity
        // Check collision with the floor
        // If there is collision
        m_jumping = false;                                                          // We are on the floor. Reset jump
        m_jumpCurrentTime = 0;
    }
}

void Character::pickObject(){
    std::cout << "Picked object" << std::endl;
}

void Character::basicAttack(){}

void Character::specialAttackUp(){}

void Character::specialAttackDown(){}

void Character::specialAttackSide(){}

void Character::ultimateAttack(){}

//Returns the player count
int Character::getPlayerCount(){
    return Character::m_playerCount;
}

//Returns the player with the given index
Character* Character::getPlayer(int p_index){
    return Character::m_players[p_index];
}

//Returns the index of the player
int Character::getIndex(){
    return m_playerIndex;
}