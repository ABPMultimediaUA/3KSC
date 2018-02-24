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


void ContactManager::BeginContact(b2Contact* p_contact){
	//check if fixture A was the foot sensor
	void* fixtureUserData = p_contact->GetFixtureA()->GetUserData();
	if(fixtureUserData == (void*)999){
		m_numFootContacts++;
		//std::cout << "Tocando suelo!" << m_numFootContacts << std::endl;
	}
	//check if fixture B was the foot sensor
	fixtureUserData = p_contact->GetFixtureB()->GetUserData();
	if(fixtureUserData == (void*)999){
		m_numFootContacts++;
		//std::cout << "Tocando suelo!" << m_numFootContacts << std::endl;
	}
}

void ContactManager::EndContact(b2Contact* p_contact){
	//check if fixture A was the foot sensor
	void* fixtureUserData = p_contact->GetFixtureA()->GetUserData();
	if(fixtureUserData == (void*)999){
		m_numFootContacts--;
		//std::cout << "En el aireee!" << m_numFootContacts << std::endl;
	}
	//check if fixture B was the foot sensor
	fixtureUserData = p_contact->GetFixtureB()->GetUserData();
	if(fixtureUserData == (void*)999){
		m_numFootContacts--;
		//std::cout << "En el aireee!" << m_numFootContacts << std::endl;
	}
}

int ContactManager::getJump(){
	return m_numFootContacts;
}
