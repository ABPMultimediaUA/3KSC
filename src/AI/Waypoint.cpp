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
#include "../include/AI/Waypoint.hpp"

// Creates waypoint with id of p_id, and places it at (x,y) in space (z is not needed)
Waypoint::Waypoint(int p_id, float p_position_x, float p_position_y){
    m_id = p_id;
    m_position[0] = p_position_x;
    m_position[1] = p_position_y;
    m_connected_waypoints[0] = 0; // Open 1 slot
}

Waypoint::~Waypoint(){}

// Connects waypoint 1 with waypoint 2, and waypoint 2 with waypoint 1
void Waypoint::connect(Waypoint *w1, Waypoint *w2){
    // Iterate through the list of connected waypoints of w1 to find an empty slot
    for(int i=0; i<w1->m_connected_waypoints.size(); i++)
    {
        if(w1->m_connected_waypoints[i] == 0){ // Slot is empty
            w1->m_connected_waypoints[i] = w2; // Assign connected waypoint
            w1->m_connected_waypoints[i+1] = 0;// Ready next slot
        }
    }

    // Iterate through the list of connected waypoints of w2 to find an empty slot
    for(int i=0; i<w2->m_connected_waypoints.size(); i++)
    {
        if(w2->m_connected_waypoints[i] == 0){ // Slot is empty
            w2->m_connected_waypoints[i] = w1; // Assign connected waypoint
            w2->m_connected_waypoints[i+1] = 0;// Ready next slot
        }
    }
}

// Disconnects waypoint 1 from waypoint 2, and viceversa
void Waypoint::disconnect(Waypoint *w1, Waypoint *w2){
    // Iterate through the list of connected waypoints of w1 to find an empty slot
    for(int i=0; i<w1->m_connected_waypoints.size(); i++)
    {
        if(w1->m_connected_waypoints[i] == w2){ // Slot is empty
            w1->m_connected_waypoints[i] = 0; // Assign connected waypoint
        }
    }

    // Iterate through the list of connected waypoints of w2 to find an empty slot
    for(int i=0; i<w2->m_connected_waypoints.size(); i++)
    {
        if(w2->m_connected_waypoints[i] == w1){ // Slot is empty
            w2->m_connected_waypoints[i] = 0; // Assign connected waypoint
        }
    }
}

// Returns true if waypoint 1 is connected to waypoint 2
bool Waypoint::isConnected(Waypoint *w2){
    for(int i=0; i<this->m_connected_waypoints.size(); i++){
        if(this->m_connected_waypoints[i]==w2){
            return true;
        }
    }
    return false;
}