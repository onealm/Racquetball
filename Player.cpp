/*
-----------------------------------------------------------------------------
Filename:    Player.cpp
-----------------------------------------------------------------------------

*/

#include "Player.h"

namespace gTech {

	Player::Player(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld) 
	{
		//Create ball
		Ogre::Entity* player = scnMgr->createEntity("Player1", "cube.mesh");

		player->setCastShadows(true);

		//Attach ball to node
		playerNode = scnMgr->getRootSceneNode()->createChildSceneNode("Player", Ogre::Vector3(0, 100, 0));
		playerNode->attachObject(player);


		playerNode->scale(4.5f, 1.5f, 0.25f);

		addToWorld(playerNode, ourWorld);
	}

	Player::~Player(void)
	{
	}

	void Player::addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld)
	{
		Ogre::Vector3 pos = newBtNode->getPosition() + (Ogre::Vector3(25, 450, -25));
	    btScalar mass(0.0f);
	    btVector3 localInertia(0, 0, 0);

	    btCollisionShape *shape = new btBoxShape(btVector3(450, 100, 100));
	    transform.setIdentity();
	    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	    shape->calculateLocalInertia(mass, localInertia);
	    btDefaultMotionState *motionState = new btDefaultMotionState(transform);
	    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	    rbInfo.m_restitution = 0.0;
	    rbInfo.m_friction = 0;
	    body = new btRigidBody(rbInfo);
	    body->setLinearVelocity(btVector3(0, 0, 0));
	    body->setUserPointer((void *)(newBtNode));
	    ourWorld->addRigidBody(body);
	}

} // namespace gTech