
#include <iostream>
#include "../headers/managers/ContactManager.hpp"


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
