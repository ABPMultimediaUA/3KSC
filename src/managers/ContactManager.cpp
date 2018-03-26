/*
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
    along with this program.  If not, see http://www.gnu.org/licenses/.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*/

#include "../include/managers/ContactManager.hpp"
#include <iostream>
#include "../include/entities/characters/Character.hpp"
#include "../include/entities/items/Portal.hpp"


void ContactManager::BeginContact(b2Contact* p_contact){
	void* dataA = p_contact->GetFixtureA()->GetUserData();
	void* dataB = p_contact->GetFixtureB()->GetUserData();
	checkCollision(dataB, dataA);
}

void ContactManager::EndContact(b2Contact* p_contact){
	void* dataA = p_contact->GetFixtureA()->GetUserData();
	void* dataB = p_contact->GetFixtureB()->GetUserData();
	checkLeave(dataB, dataA);
}

void ContactManager::checkCollision(void* p_data1, void* p_data2){
	onCollide(p_data1, p_data2);
	onCollide(p_data2, p_data1);
}

void ContactManager::checkLeave(void* p_data1, void* p_data2){
	onLeave(p_data1, p_data2);
	onLeave(p_data2, p_data1);
}

void ContactManager::onCollide(void* p_data1, void* p_data2){
	if(p_data1){
		if(p_data1 == (void*)888){
			if(static_cast<Portal*>(p_data2))
				static_cast<Portal*>(p_data2)->onEnter();
		}
		else
			static_cast<Character*>( p_data1 )->onTouchGround();
	}
}

void ContactManager::onLeave(void* p_data1, void* p_data2){
	if(p_data1){
		if(p_data1 == (void*)888){
			if(static_cast<Portal*>(p_data2))
				static_cast<Portal*>(p_data2)->onLeave();
		}
		else
			static_cast<Character*>(p_data1)->onLeaveGround();
	}
}
