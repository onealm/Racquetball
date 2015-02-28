/*
-----------------------------------------------------------------------------
Filename:    Ball.cpp
-----------------------------------------------------------------------------

Base code taken from class slides.
*/

#include "Ball.h"

Ball::Ball(Ogre::SceneManager* scnMgr) 
{

	//Create ball
	Ogre::Entity* ball = scnMgr->createEntity("Sphere", "sphere.mesh");
	ball->setMaterialName("Ogre/Eyes");
	ball->setCastShadows(true);

	//Attach ball to node
	ballNode = scnMgr->getRootSceneNode()->createChildSceneNode("Ball", Ogre::Vector3(0, 500, -500));
	ballNode->attachObject(ball);
	ballNode->scale(0.1f,0.1f,0.1f);

	//Set ball properties
	bRadius = 10.0f;
    bDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f);
    bDirection.normalise();
    bSpeed = 250.0f;

}

Ball::~Ball(void)
{
}


