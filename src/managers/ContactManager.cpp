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
		}
	}
	p_contact->SetEnabled(true);
}

void ContactManager::checkPreSolve(b2Fixture* fixture1, b2Fixture* fixture2, b2Contact* p_contact, const b2Manifold* p_oldManifold){
	//std::cout << "CHECK PRESOLVE" << std::endl;
	int	  t_data1 = *reinterpret_cast<int*>(fixture1->GetBody()->GetUserData());
	int	  t_data2 = *reinterpret_cast<int*>(fixture2->GetBody()->GetUserData());
	
	if(t_data1 == 0 && (t_data2 == 1 || t_data2 == 2)){
		//std::cout << "PLAYER ID: " << t_data1 << std::endl;
		//std::cout << "OTHER  ID: " << t_data2 << std::endl;

        b2Fixture* otherFixture 	= fixture1;
        b2Fixture* playerFixture 	= fixture2;

		b2Body* otherBody	= otherFixture->GetBody();
		b2Body* playerBody	= playerFixture->GetBody();

		int numPoints = p_oldManifold->pointCount;
		for(int i = 0; i < numPoints; i++){			
			b2Vec2 pointVelPlatform	= otherBody->GetLinearVelocityFromWorldPoint(p_oldManifold->points[i].localPoint);
			b2Vec2 pointVelOther	= playerBody->GetLinearVelocityFromWorldPoint(p_oldManifold->points[i].localPoint);
			b2Vec2 relativeVel		= otherBody->GetLocalVector(pointVelOther - pointVelPlatform);

			//std::cout << "Vel: " << relativeVel.y << std::endl;

			if(relativeVel.y < 0)
				return; 	//Point in the platform
			else if(relativeVel.y < 3){
				b2Vec2 relativePoint = otherBody->GetLocalPoint(p_oldManifold->points[i].localPoint);
				//std::cout << relativePoint.y << std::endl;
				float platformFaceY = 0.5f;
				if(relativePoint.y > (platformFaceY - 0.1))
					return;		
			}
		}
		p_contact->SetEnabled(false);
	}
}
