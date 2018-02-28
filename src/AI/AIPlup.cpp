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

#include "../include/AI/AIPlup.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/entities/characters/Character.hpp"
#include "../include/entities/Arena.hpp"
#include <iostream>
#include <string>
        
//Instance initialization
AIPlup* AIPlup::m_instance = 0;

//Returns the only instance of this class
AIPlup* AIPlup::instance(){
    if (!m_instance)
        m_instance = new AIPlup();

    return m_instance;
}

AIPlup::AIPlup(){}

// Updates all the variables required by the tree to work properly
void AIPlup::update(){
    std::cout<<std::endl; // SIN ESTO NO FUNCIONA WTFFFF
    int t_PLUP_index = 1;
    m_PLUP_special_up_range = 0.0;
    m_PLUP_special_side_range = 0.0;
    /*************************************************************/
    /****************      Get Plup's life        ****************/
    /*************************************************************/
    m_PLUP_life = (float)Arena::getInstance()->getPlayer(t_PLUP_index)->getHP();

    /*************************************************************/
    /****************      Get Plup's mana        ****************/
    /*************************************************************/
    m_PLUP_mana = (float)Arena::getInstance()->getPlayer(t_PLUP_index)->getMP();

    /*************************************************************/
    /**************  Get distance to closest enemy  **************/
    /*************************************************************/
    int t_playerCount = Arena::getInstance()->getPlayerCount();
    Character* t_currentPlayer;

    // Get Plup's coordinates
    t_currentPlayer = Arena::getInstance()->getPlayer(t_PLUP_index);
    float self_x = t_currentPlayer->getX();
    float self_y = t_currentPlayer->getY();
    float self_z = t_currentPlayer->getZ();

    m_PLUP_position = b2Vec2(self_x, self_y);
    m_PLUP_distance_to_enemy = PhysicsManager::instance()->getDistanceToClosestCharacter(m_PLUP_position);
   
    /*************************************************************/
    /*   Check if an enemy is in range for a special attack up   */
    /*************************************************************/
    float t_PLUP_special_up_wideness = 50.0;
    float t_PLUP_special_side_wideness = 200.0;
    float t_PLUP_special_side_heighth = 20.0;

    for (int i = 0; i < t_playerCount; i++){
        //Plup shall not take himself into consideration
        if (i == t_PLUP_index)
            continue;

        // Get enemy coordinates
        t_currentPlayer = Arena::getInstance()->getPlayer(i);
        float target_x = t_currentPlayer->getX();
        float target_y = t_currentPlayer->getY();
        float target_z = t_currentPlayer->getZ();

        float t_closestBodyFraction;

        b2Vec2 t_p1 = b2Vec2(self_x, self_y);
        b2Vec2 t_p2 = b2Vec2(target_x, target_y);
        
        if(abs(target_x-self_x) < t_PLUP_special_up_wideness){
            t_closestBodyFraction = PhysicsManager::instance()->RaycastBetween(t_p1, t_p2);

            // Check wether there is an object between the 2 characters
            if(t_closestBodyFraction >= 0.83f){ //If there is not an intersection to the raycast
                m_PLUP_special_up_range = 1.0;
            }
        }

        /*************************************************************/
        /*  Check if an enemy is in range for a special attack side  */
        /*************************************************************/
        if(abs(target_x-self_x) < t_PLUP_special_side_wideness){
            if(abs(target_y-self_y) < t_PLUP_special_side_heighth){
                float t_closestBodyFraction = PhysicsManager::instance()->RaycastBetween(t_p1, t_p2);

                // Check wether there is an object between the 2 characters
                if(t_closestBodyFraction >= 0.83f){ //If there is not an intersection to the raycast
                    m_PLUP_special_side_range = 1.0;
                }
            }
        }
    }

    /*************************************************************/
    /*******  Check if there is already a snowman placed  ********/
    /*************************************************************/
    t_currentPlayer = Arena::getInstance()->getPlayer(t_PLUP_index);
    /*if(t_currentPlayer->getCurrentSnowmen() > 0)
        m_PLUP_snowman_placed = 1.0;
    else*/
        m_PLUP_snowman_placed = 0.0;

    /*************************************************************/
    /*******        Check if there is an item close       ********/
    /*************************************************************/
    m_PLUP_distance_to_item = 0.0; // TODO: Raycast to items only

    /*************************************************************/
    /*******        MAKE DECISION ABOUT WHAT TO DO        ********/
    /*************************************************************/
    std::string t_action = m_PLUP_root->makeDecision(m_PLUP_root)->m_action;

    if (t_action == "move"){
        std::cout<<"I AM MOVING"<<std::endl;
    }
    else if (t_action == "basic_attack"){
        std::cout<<"I AM ATTACKING"<<std::endl;
        t_currentPlayer->basicAttack();
    }
    else if (t_action == "special_attack_up"){
        std::cout<<"I AM DOING A SPECIAL ATTACK UP"<<std::endl;
        t_currentPlayer->specialAttackUp();
    }
    else if (t_action == "special_attack_side"){
        std::cout<<"I AM DOING A SPECIAL ATTACK SIDE"<<std::endl;
        t_currentPlayer->specialAttackSide();
    }
    else if (t_action == "special_attack_down"){
        std::cout<<"I AM DOING A SPECIAL ATTACK DOWN"<<std::endl;
        t_currentPlayer->specialAttackDown();
    }
    else if (t_action == "block"){
        std::cout<<"I AM BLOCKING"<<std::endl;
    }
    else{
       // std::cout<<"NOTHING?"<<std::endl;
    }
}

// Builds the tree containing Plup's AI. Builds all the trues to a node. If no trues are left, builds the falses and repeats itself with the next node
void AIPlup::buildTree(){
    // Enemy close
    m_PLUP_root = new AINode(0, 400, &m_PLUP_distance_to_enemy);
        // Life > 80%
        m_PLUP_root->m_true_children[0] = new AINode(0, 80.0, &m_PLUP_life);
            //Mana > 35%
            m_PLUP_root->m_true_children[0]->m_true_children[0] = new AINode(0, 35.0, &m_PLUP_mana);
                // Snowman placed
                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 1.0, &m_PLUP_snowman_placed);
                    // In range of Special Attack Up
                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 1.0, &m_PLUP_special_up_range);
                        // Mana > 25%
                        m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 25.0, &m_PLUP_mana);
                            // DO ACTION: SPECIAL ATTACK UP
                            m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_up");
                            // In range of Special Attack side
                            m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_side_range);
                                // Mana > 20%
                                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 20.0, &m_PLUP_mana);
                                    // DO ACTION: SPECIAL ATTACK SIDE
                                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_side");
                                    // In range of basic attack
                                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                        // DO ACTION: BASIC ATTACK
                                        m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                        // DO ACTION: MOVE
                                        m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                            // In range of basic attack
                            m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                // DO ACTION: BASIC ATTACK
                                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                // DO ACTION: MOVE
                                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                        // In range of Special Attack Up (ALREADY CREATED. REFERENCE IT)
                        m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0];
                    // DO ACTION: SPECIAL ATTACK DOWN
                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "special_attack_down");
                // In range of Special Attack Up
                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_up_range);
                    // Mana > 25%
                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 25.0, &m_PLUP_mana);
                        // DO ACTION: SPECIAL ATTACK UP
                        m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_up");
                        // In range of Special Attack Side
                        m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_side_range);
                            // Mana > 20%
                            m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 20.0, &m_PLUP_mana);
                                // DO ACTION: SPECIAL ATTACK SIDE
                                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_side");
                                // In range of basic attack
                                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                    // DO ACTION: BASIC ATTACK
                                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                    // DO ACTION: MOVE
                                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                            // In range of basic attack
                            m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                // DO ACTION: BASIC ATTACK
                                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                // DO ACTION: MOVE
                                m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                    // In range of Special Attack Side (ALREADY CREATED. REFERENCE IT)
                    m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0];
            // Life > 50%
            m_PLUP_root->m_true_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_life);
                //Mana > 35%
                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 35.0, &m_PLUP_mana);
                    // Snowman placed
                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 1.0, &m_PLUP_snowman_placed);
                        // In range of Special Attack Up
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 1.0, &m_PLUP_special_up_range);
                            // Mana > 25%
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 25.0, &m_PLUP_mana);
                                // DO ACTION: SPECIAL ATTACK UP
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_up");
                                // In range of Special Attack side
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_side_range);
                                    // Mana > 20%
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 20.0, &m_PLUP_mana);
                                        // DO ACTION: SPECIAL ATTACK SIDE
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_side");
                                        // In range of basic attack
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                            // DO ACTION: BASIC ATTACK
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                            // OR DO ACTION: BLOCK
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                            // DO ACTION: MOVE
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                                // In range of basic attack
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                    // DO ACTION: BASIC ATTACK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                    // OR DO ACTION: BLOCK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                    // DO ACTION: MOVE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                            // In range of Special Attack Up (ALREADY CREATED. REFERENCE IT)
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0];
                        // DO ACTION: SPECIAL ATTACK DOWN
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "special_attack_down");
                    // In range of Special Attack Up
                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_up_range);
                        // Mana > 25%
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 25.0, &m_PLUP_mana);
                            // DO ACTION: SPECIAL ATTACK UP
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_up");
                            // In range of Special Attack Side
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_side_range);
                                // Mana > 20%
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 20.0, &m_PLUP_mana);
                                    // DO ACTION: SPECIAL ATTACK SIDE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_side");
                                    // In range of basic attack
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                        // DO ACTION: BASIC ATTACK
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                        // OR DO ACTION: BLOCK
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                        // DO ACTION: MOVE
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                                // In range of basic attack
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                    // DO ACTION: BASIC ATTACK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                    // OR DO ACTION: BLOCK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                    // DO ACTION: MOVE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                        // In range of Special Attack Side (ALREADY CREATED. REFERENCE IT)
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0];
                // Life < 25%
                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(1, 80.0, &m_PLUP_life);
                    //Mana > 35%
                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 35.0, &m_PLUP_mana);
                    // Snowman placed
                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 1.0, &m_PLUP_snowman_placed);
                        // In range of Special Attack Up
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 1.0, &m_PLUP_special_up_range);
                            // Mana > 25%
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(0, 25.0, &m_PLUP_mana);
                                // DO ACTION: SPECIAL ATTACK UP
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_up");
                                // In range of Special Attack side
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_side_range);
                                    // Mana > 20%
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 20.0, &m_PLUP_mana);
                                        // DO ACTION: SPECIAL ATTACK SIDE
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_side");
                                        // In range of basic attack
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                            // DO ACTION: BASIC ATTACK
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                            // OR DO ACTION: BLOCK
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                            // OR DO ACTION: MOVE
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[2] = new AINode(-1, 0, 0, "move");
                                            // DO ACTION: MOVE
                                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                                // In range of basic attack
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                    // DO ACTION: BASIC ATTACK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                    // OR DO ACTION: BLOCK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                    // OR DO ACTION: MOVE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[2] = new AINode(-1, 0, 0, "move");
                                    // DO ACTION: MOVE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                            // In range of Special Attack Up (ALREADY CREATED. REFERENCE IT)
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = m_PLUP_root->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0];
                        // DO ACTION: SPECIAL ATTACK DOWN
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "special_attack_down");
                    // In range of Special Attack Up
                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_up_range);
                        // Mana > 25%
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 25.0, &m_PLUP_mana);
                            // DO ACTION: SPECIAL ATTACK UP
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_up");
                            // In range of Special Attack Side
                            m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 1.0, &m_PLUP_special_side_range);
                                // Mana > 20%
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(0, 20.0, &m_PLUP_mana);
                                    // DO ACTION: SPECIAL ATTACK SIDE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "special_attack_side");
                                    // In range of basic attack
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                        // DO ACTION: BASIC ATTACK
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                        // OR DO ACTION: BLOCK
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                        // OR DO ACTION: MOVE
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[2] = new AINode(-1, 0, 0, "move");
                                        // DO ACTION: MOVE
                                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                                // In range of basic attack
                                m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = new AINode(0, 50.0, &m_PLUP_distance_to_enemy);
                                    // DO ACTION: BASIC ATTACK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "basic_attack");
                                    // OR DO ACTION: BLOCK
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[1] = new AINode(-1, 0, 0, "block");
                                    // OR DO ACTION: MOVE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[2] = new AINode(-1, 0, 0, "move");
                                    // DO ACTION: MOVE
                                    m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "move");
                        // In range of Special Attack Side (ALREADY CREATED. REFERENCE IT)
                        m_PLUP_root->m_true_children[0]->m_false_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0]->m_false_children[0] = m_PLUP_root->m_true_children[0]->m_true_children[0]->m_false_children[0]->m_true_children[0]->m_false_children[0];
        // Item close
        m_PLUP_root->m_false_children[0] = new AINode(0, 300.0, &m_PLUP_distance_to_item);
            // DO ACTION: PICK ITEM UP
            m_PLUP_root->m_false_children[0]->m_false_children[0] = new AINode(-1, 0, 0, "pick_item_up");
            // DO ACTION: MOVE
            m_PLUP_root->m_false_children[0]->m_true_children[0] = new AINode(-1, 0, 0, "move");
}
