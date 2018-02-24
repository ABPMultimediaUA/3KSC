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

#ifndef AI_PLUP
#define AI_PLUP

#include "AIManager.hpp"
#include <Box2D.h>
#include "AINode.hpp"

class AIPlup : public AIManager{
    private:
        static AIPlup* m_instance;
        float m_PLUP_distance_to_enemy;       // Fraction that determines if an enemy is close
        float m_PLUP_distance_to_item;        // Fraction that determines if an item is close
        float m_PLUP_life;                    // Plup's current life
        float m_PLUP_mana;                    // Plup's current mana
        float m_PLUP_special_up_range;        // Fraction that determines if an enemy is in range of special ability up
        float m_PLUP_special_side_range;      // Fraction that determines if an enemy is in range of special ability side
        float m_PLUP_snowman_placed;          // Determines if a snowman is already placed or not
        b2Vec2 m_PLUP_position;               // Vector containing Plup's position
        AINode* m_PLUP_root;                  // Root of Plup's tree
    public:
        static AIPlup* instance();
        AIPlup();
        ~AIPlup();
        void update();
        void buildTree();
};

#endif

