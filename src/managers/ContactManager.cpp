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


void ContactManager::BeginContact(b2Contact* p_contact){
	void* dataA = p_contact->GetFixtureA()->GetUserData();
	void* dataB = p_contact->GetFixtureB()->GetUserData();
	
	if ( dataA ){
		if(dataA == (void*)888){
			if(static_cast<Character*>( dataB ))
			{
				std::cout<<"Entrando al portal"<<std::endl;
			}
		}
		else{
			static_cast<Character*>( dataA )->onTouchGround();
		}
	}

	if ( dataB ){
		if(dataB == (void*)888){
			if(static_cast<Character*>( dataA ))
			{
				std::cout<<"Entrando al portal"<<std::endl;
			}
		}
		else{
			static_cast<Character*>( dataB)->onTouchGround();
		}
	}
}

void ContactManager::EndContact(b2Contact* p_contact){
	void* dataA = p_contact->GetFixtureA()->GetUserData();
	void* dataB = p_contact->GetFixtureB()->GetUserData();
	
	if ( dataA ){
		if(dataA == (void*)888){
			if(static_cast<Character*>( dataB ))
				std::cout<<"Saliendo portal"<<std::endl;
		}
	}

	if ( dataB ){
		if(dataB == (void*)888){
			if(static_cast<Character*>( dataA ))
			std::cout<<"Saliendo portal"<<std::endl;
		}
	}
}

int ContactManager::getJump(){
	return m_numFootContacts;
}
