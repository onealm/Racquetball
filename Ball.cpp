/*
-----------------------------------------------------------------------------
Filename:    Ball.cpp
-----------------------------------------------------------------------------

Base code taken from class slides.
*/

#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld) 
{

	//Create ball
	Ogre::Entity* ball = scnMgr->createEntity("Sphere", "sphere.mesh");
	ball->setMaterialName("Ogre/Eyes");
	ball->setCastShadows(true);

	//Attach ball to node
	ballNode = scnMgr->getRootSceneNode()->createChildSceneNode("Ball", Ogre::Vector3(0, 900, -500));
	ballNode->attachObject(ball);
	ballNode->scale(0.4f,0.4f,0.4f);

	//Set ball properties
	bRadius = 40.0f;

    addToWorld(ballNode, ourWorld);
}

Ball::Ball(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld, bool isMulti) 
{

	//Create ball
	Ogre::Entity* ball = scnMgr->createEntity("sphere.mesh");
	ball->setMaterialName("Ogre/Eyes");
	ball->setCastShadows(true);

	//Attach ball to node
	ballNode = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 900, -500));
	ballNode->attachObject(ball);
	ballNode->scale(0.4f,0.4f,0.4f);

	//Set ball properties
	bRadius = 40.0f;

    //addToWorld(ballNode, ourWorld);
}

Ball::~Ball(void)
{
}

void Ball::addToWorld(Ogre::SceneNode *newBtBode, btDiscreteDynamicsWorld *ourWorld)
{
	Ogre::Vector3 pos = newBtBode->getPosition();
	Ogre::Quaternion qt = newBtBode->getOrientation();
	btScalar mass(1.0f);
	btVector3 localInertia(0, 0, 0);

	btCollisionShape *shape = new btSphereShape(btScalar(bRadius));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	transform.setRotation(btQuaternion(qt.x, qt.y, qt.z, qt.w));
	shape->calculateLocalInertia(mass, localInertia);
	btDefaultMotionState *motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	rbInfo.m_restitution = 1.0f;
	rbInfo.m_friction = 0;
	ballBody = new btRigidBody(rbInfo);
	ballBody->setUserPointer((void *)(newBtBode));
	ourWorld->addRigidBody(ballBody);
}
