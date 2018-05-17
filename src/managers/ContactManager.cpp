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
	//std::cout << "Beg" << std::endl;
	b2Fixture* fixtureA = p_contact->GetFixtureA();
	b2Fixture* fixtureB = p_contact->GetFixtureB();
	
	checkCollision(fixtureA, fixtureB, p_contact);
	checkCollision(fixtureB, fixtureA, p_contact);
}

void ContactManager::EndContact(b2Contact* p_contact){
	//std::cout << "End" << std::endl;
	b2Fixture* fixtureA = p_contact->GetFixtureA();
	b2Fixture* fixtureB = p_contact->GetFixtureB();

	checkLeave(fixtureA, fixtureB, p_contact);
	checkLeave(fixtureB, fixtureA, p_contact);
}

void ContactManager::PreSolve(b2Contact* p_contact, const b2Manifold* p_oldManifold){
	//std::cout << "Pre" << std::endl;
	b2Fixture* fixtureA = p_contact->GetFixtureA();
	b2Fixture* fixtureB = p_contact->GetFixtureB();

	checkPreSolve(fixtureA, fixtureB, p_contact, p_oldManifold);
	checkPreSolve(fixtureB, fixtureA, p_contact, p_oldManifold);
}

void ContactManager::checkCollision(b2Fixture* fixture1, b2Fixture* fixture2, b2Contact* p_contact){
	void* t_data = fixture1->GetUserData();
	if(t_data){
		/*
		if(static_cast<Portal*>(p_data2) && static_cast<Character*>(t_data)){
			//comprobamos que el character exista de verdad
			if(static_cast<Character*>(t_data)->getValidation() != 123)
				return;
			static_cast<Portal*>(p_data2)->onEnter(static_cast<Character*>(t_data));
		}else
			static_cast<Character*>(t_data)->onTouchGround();
		*/
		if(static_cast<Character*>(t_data)){
			static_cast<Character*>(t_data)->onTouchGround();
			//std::cout << "TOUCH" << std::endl;
		}
	}
}

void ContactManager::checkLeave(b2Fixture* fixture1, b2Fixture* fixture2, b2Contact* p_contact){
	void* t_data = fixture1->GetUserData();
	if(t_data){
		/*
		if(static_cast<Portal*>(p_data2) && static_cast<Character*>(t_data)){
			//comprobamos que el character exista de verdad
			if(static_cast<Character*>(t_data)->getValidation() != 123)
				return;
			static_cast<Portal*>(p_data2)->onLeave(static_cast<Character*>(t_data));
		}else
			static_cast<Character*>(t_data)->onLeaveGround();
		*/
		if(static_cast<Character*>(t_data)){
			static_cast<Character*>(t_data)->onLeaveGround();
			//std::cout << "LEAVE" << std::endl;
			p_contact->SetEnabled(true);
		}
	}
	p_contact->SetEnabled(true);
}

void ContactManager::checkPreSolve(b2Fixture* fixture1, b2Fixture* fixture2, b2Contact* p_contact, const b2Manifold* p_oldManifold){
//	std::cout << "CHECK PRESOLVE" << std::endl;
	//void* t_data = fixture1->GetUserData();
	int	  t_data1 = *reinterpret_cast<int*>(fixture1->GetBody()->GetUserData());
	int	  t_data2 = *reinterpret_cast<int*>(fixture2->GetBody()->GetUserData());
	//std::cout << "ASDF: " << *reinterpret_cast<int*>(fixture1->GetBody()->GetUserData()) << std::endl;
	//std::cout << "ASDF: " << t_data1 << std::endl;
	
	if(t_data1 == 0 && t_data2 == 1){
		//check if one of the fixtures is the platform
        b2Fixture* playerFixture 	= fixture1;
        b2Fixture* otherFixture 	= fixture2;
        /*
        if(t_data){
            playerFixture = fixture1;
            otherFixture = fixture2;
        }else
            return;
		*/
		b2Body* playerBody	= playerFixture->GetBody();
		b2Body* otherBody	= otherFixture->GetBody();

		int* player_id = reinterpret_cast<int*>(playerBody->GetUserData());
		int* other_id  = reinterpret_cast<int*>(otherBody->GetUserData());
		//std::cout << "PLAYER ID: " << *player_id << std::endl;
		//std::cout << "OTHER  ID: " << *other_id << std::endl;

		int numPoints = p_oldManifold->pointCount;
		//int numPoints = p_contact->GetManifold()->pointCount;
		//b2WorldManifold worldManifold;
		//p_contact->GetWorldManifold( &worldManifold );
		//std::cout << numPoints << std::endl;

		//check if p_contact points are moving downward
		for(int i = 0; i < numPoints; i++){
			b2Vec2 pointVel = otherBody->GetLinearVelocityFromWorldPoint( p_oldManifold->points[i].localPoint );
			std::cout << pointVel.y << std::endl;
			if(pointVel.y < 0){
				std::cout << "SALIMOS" << std::endl;
				return;//point is moving down, leave p_contact solid and exit
			}
		}

		//no points are moving downward, p_contact should not be solid
		p_contact->SetEnabled(false);
	}
}
