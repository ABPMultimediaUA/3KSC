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

#include "../include/AI/AISparky.hpp"
#include "../include/AI/AINode.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/managers/InputManager.hpp"
#include "../include/entities/Arena.hpp"
#include "../include/AI/Pathfinding.hpp"
#include "../include/entities/characters/Character.hpp"

#include <iostream>
#include <fstream>
#include <json.hpp>

AISparky::AISparky(Character* p_player)
    : AICharacter(p_player){
    buildTree();
}

AISparky::~AISparky(){
    
}

// Updates all the variables required by the tree to work properly
void AISparky::update(){
    
}

// Builds the tree containing Sparky's AI. Builds all the trues to a node. If no trues are left, builds the falses and repeats itself with the next node
void AISparky::buildTree(){
    std::ifstream t_file("assets/ai/example.json");
    nlohmann::json t_json;
    t_file >> t_json;
    auto nodes = t_json["nodes"];

    std::cout << nodes[0]["name"] << " <- This is data from a json file" << std::endl;
}
