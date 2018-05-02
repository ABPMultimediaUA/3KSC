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
#include "../include/AI/AINode.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/managers/InputManager.hpp"
#include "../include/entities/Arena.hpp"
#include "../include/AI/Pathfinding.hpp"
#include "../include/entities/characters/Character.hpp"
#include <iostream>
#include <fstream>

AIPlup::AIPlup(Character* p_player)
    : AICharacter(p_player){
    buildTree();
}

AIPlup::~AIPlup(){}

// Updates all the variables required by the tree to work properly
void AIPlup::update(){
    int m_index = 1;
    m_specialUpRange = 0.0;
    m_specialSideRange = 0.0;
    m_distanceToPortal = 0.0f;

    /*************************************************************/
    /****************      Get Portal state       ****************/
    /*************************************************************/
    m_portalActive = m_arena->portalIsActive();

    /*************************************************************/
    /****************   Get distance to Portal    ****************/
    /*************************************************************/
    if(m_portalActive){
        m_distanceToPortal = m_physicsManager->getDistanceBetween(m_position,b2Vec2(m_arena->getPortalPosition()[0],m_arena->getPortalPosition()[1]));
    }

    /*************************************************************/
    /****************      Get Plup's life        ****************/
    /*************************************************************/
    m_HP = (float)m_arena->getPlayer(m_index)->getHP();

    /*************************************************************/
    /****************      Get Plup's mana        ****************/
    /*************************************************************/
    m_MP = (float)m_arena->getPlayer(m_index)->getMP();

    /*************************************************************/
    /**************  Get distance to closest enemy  **************/
    /*************************************************************/
    int t_playerCount = m_arena->getPlayerCount();
    Character* t_currentPlayer;
    
    // Get Plup's coordinates
    t_currentPlayer = m_arena->getPlayer(m_index);
    float self_x, self_y, self_z;
    self_x = t_currentPlayer->getX();
    self_y = t_currentPlayer->getY();
    self_z = t_currentPlayer->getZ();
    m_position = b2Vec2(self_x, self_y);
    m_distanceToEnemy = m_physicsManager->getDistanceToClosestCharacter(m_position);

    /*************************************************************/
    /*   Check if an enemy is in range for a special attack up   */
    /*************************************************************/
    float t_PLUP_special_up_wideness = 10.0;
    float t_PLUP_special_up_min_height = 40.0;
    float t_PLUP_special_side_wideness = 200.0;
    float t_PLUP_special_side_heighth = 20.0;

    for (int i = 0; i < t_playerCount; i++){
        //Plup shall not take himself into consideration
        if (i == m_index)
            continue;

        // Get enemy coordinates
        t_currentPlayer = m_arena->getPlayer(i);
        float target_x, target_y, target_z = 0;
        if(t_currentPlayer!=0){
            target_x = t_currentPlayer->getX();
            target_y = t_currentPlayer->getY();
            target_z = t_currentPlayer->getZ();
        }

        float t_closestBodyFraction;

        b2Vec2 t_p1 = b2Vec2(self_x, self_y);
        b2Vec2 t_p2 = b2Vec2(target_x, target_y);
        
        if(abs(target_x-self_x) < t_PLUP_special_up_wideness){
            if(abs(target_y-self_y) < t_PLUP_special_up_min_height){
                t_closestBodyFraction = m_physicsManager->RaycastBetween(t_p1, t_p2);

                // Check wether there is an object between the 2 characters
                if(t_closestBodyFraction >= 0.83f){ //If there is not an intersection to the raycast
                    m_specialUpRange = 1.0;
                }
            }
        }

        /*************************************************************/
        /*  Check if an enemy is in range for a special attack side  */
        /*************************************************************/
        if(abs(target_x-self_x) < t_PLUP_special_side_wideness){
            if(abs(target_y-self_y) < t_PLUP_special_side_heighth){
                float t_closestBodyFraction = m_physicsManager->RaycastBetween(t_p1, t_p2);

                // Check wether there is an object between the 2 characters
                if(t_closestBodyFraction >= 0.83f){ //If there is not an intersection to the raycast
                    m_specialSideRange = 1.0;
                }
            }
        }
    }

    /*************************************************************/
    /*******  Check if there is already a snowman placed  ********/
    /*************************************************************/
    t_currentPlayer = m_arena->getPlayer(m_index);
    if(t_currentPlayer!=0){
        if(t_currentPlayer->getCurrentSnowmen() > 0)
            m_PLUP_snowman_placed = 1.0;
        else
            m_PLUP_snowman_placed = 0.0;
    }

    /*************************************************************/
    /*******        Check if there is an item close       ********/
    /*************************************************************/
    b2Vec2 t_closestItemPosition;
    t_closestItemPosition = m_arena->getClosestItemPosition(m_position);
    m_distanceToItem = m_physicsManager->getDistanceBetween(t_closestItemPosition, m_position);

    /*************************************************************/
    /*******             Get closest character            ********/
    /*************************************************************/
    Character* t_closestPlayer = m_physicsManager->getClosestCharacter(m_position);

    /*************************************************************/
    /*******        MAKE DECISION ABOUT WHAT TO DO        ********/
    /*************************************************************/
    int t_action;
    t_action = m_nodes[0]->makeDecision(m_nodes[0])->m_action;
    std::cout<<"action: "<<t_action<<std::endl;
    std::cout<<"distance to enemy: "<<m_distanceToEnemy<<std::endl;
    if (t_action == 6){
        b2Vec2 t_destination;
        if(t_closestPlayer!=0){
            if(m_position.x > t_closestPlayer->getX()){
                t_destination = m_pathfinding->getClosestWaypoint(m_position, 0); // Find waypoint to the left
            }
            else{
                t_destination = m_pathfinding->getClosestWaypoint(m_position, 1); // Find waypoint to the right
            }

            float t_destination_float[2];
            t_destination_float[0] = t_destination.x;
            t_destination_float[1] = t_destination.y;
            std::cout<<"target X: "<<t_destination_float[0]<<std::endl;
            std::cout<<"target Y: "<<t_destination_float[1]<<std::endl;
            std::cout<<"self X: "<<m_position.x<<std::endl;
            std::cout<<"self Y: "<<m_position.y<<std::endl;
            t_currentPlayer->moveToPath(t_destination_float);
        }
    }
    else if (t_action == 3){
        t_currentPlayer->basicAttack();
    }
    else if (t_action == 0){
        m_inputManager->setAction(Action::SpecialAttackUp, m_index);
    }
    else if (t_action == 2){
        //m_inputManager->setAction(Action::SpecialAttackSide, m_index);
    }
    else if (t_action == 1){
        // m_inputManager->setAction(Action::SpecialAttackDown, m_index);
        t_currentPlayer->specialAttackDown();
    }
    else if (t_action == 4){
        m_inputManager->setAction(Action::Block, m_index);
    }
    else{
       //std::cout<<"NOTHING?"<<std::endl;
    }
}

// Builds the tree containing Plup's AI. Builds all the trues to a node. If no trues are left, builds the falses and repeats itself with the next node
void AIPlup::buildTree(){
    // Read JSON
    std::ifstream t_file("assets/ai/ai_tree_plup.json");
    nlohmann::json t_json;
    t_file >> t_json;
    auto nodes = t_json["nodes"];

    // Initialize
    int t_comparison_type;
    float t_value;
    float* t_data;
    int t_node_type;
    int t_action;
    int t_true_child;
    int t_false_child;
    m_nodes = new AINode*[53];
    
    // Iterate through every node
    for(int i=0; nodes[i]!=nullptr; i++){
        t_comparison_type = -1;
        t_value = -1.0f;
        t_data = 0;
        t_action = -1;

        if(nodes[i]["type"] == "comparison"){   // Comparison
            t_node_type = 0;
        }
        else{                                   // Action
            t_node_type = 1;
        }
        
        // Determine which variable to use to create the node
        if(t_node_type == 0){
            t_comparison_type = nodes[i]["data"]["comparison_type"];
            if(nodes[i]["name"] == "portal_active"){
                t_data = &m_distanceToPortal;
            }
            else if(nodes[i]["name"] == "on_portal"){
                t_data = &m_distanceToPortal;
            }
            else if(nodes[i]["name"] == "enemy_close"){
                t_data = &m_distanceToEnemy;
            }
            else if(nodes[i]["name"] == "life_above_first_threshold"){
                t_data = &m_HP;
            }
            else if(nodes[i]["name"] == "life_above_second_threshold"){
                t_data = &m_HP;
            }
            else if(nodes[i]["name"] == "life_under_second_threshold"){
                t_data = &m_HP;
            }
            else if(nodes[i]["name"] == "mana_above_first_threshold"){
                t_data = &m_MP;
            }
            else if(nodes[i]["name"] == "snowman_placed"){
                t_data = &m_PLUP_snowman_placed;
            }
            else if(nodes[i]["name"] == "special_up_range"){
                t_data = &m_specialUpRange;
            }
            else if(nodes[i]["name"] == "mana_above_second_threshold"){
                t_data = &m_MP;
            }
            else if(nodes[i]["name"] == "special_side_range"){
                t_data = &m_specialSideRange;
            }
            else if(nodes[i]["name"] == "mana_above_third_threshold"){
                t_data = &m_MP;
            }
            else if(nodes[i]["name"] == "basic_attack_range"){
                t_data = &m_distanceToEnemy;
            }
            else if(nodes[i]["name"] == "time_above_first_threshold"){
                t_data = &m_time;
            }
            else if(nodes[i]["name"] == "time_above_second_threshold"){
                t_data = &m_time;
            }
            else if(nodes[i]["name"] == "item_close"){
                t_data = &m_distanceToItem;
            }
            else if(nodes[i]["name"] == "pick_up_range"){
                t_data = &m_distanceToItem;
            }
            t_value = nodes[i]["data"]["value"];
        }
        else{
            t_action = nodes[i]["data"]["value"];
        }
        // Create AINode   
        m_nodes[i] = new AINode(t_comparison_type, t_value, t_data, t_action);
    }

    // Set child nodes
    for(int i=0; nodes[i]!=nullptr; i++){
        t_true_child = -1;
        t_false_child = -1;
        if(nodes[i]["data"]["children"] != nullptr){
            if(nodes[i]["data"]["children"][0] != nullptr){
                t_true_child = nodes[i]["data"]["children"][0];
                m_nodes[i]->m_true_children = m_nodes[t_true_child];
            }
            if(nodes[i]["data"]["children"][1] != nullptr){
                t_false_child = nodes[i]["data"]["children"][1];
                m_nodes[i]->m_false_children = m_nodes[t_false_child];
            }
        }
    }
}
