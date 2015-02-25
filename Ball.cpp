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
	ball->setMaterialName("BallColor/CubeMap");
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

void Ball::move(const Ogre::FrameEvent& evt) 
{
	//Locate the ball
	Ogre::Vector3 bPosition = ballNode->getPosition();
	PlayingRoom* playingRoom = this->playingRoom;


	//Find direction
	if (bPosition.y < -playingRoom->uHeight/2.0f + bRadius && bDirection.y < 0.0f) 
		bDirection.y = -bDirection.y;
	if (bPosition.y > playingRoom->uHeight/2.0f - bRadius && bDirection.y > 0.0f) 
		bDirection.y = -bDirection.y;
	if (bPosition.z < -playingRoom->uLength/2.0f + bRadius && bDirection.z < 0.0f) 
		bDirection.z = -bDirection.z;
	if (bPosition.z > playingRoom->uLength/2.0f - bRadius && bDirection.z > 0.0f) 
		bDirection.z = -bDirection.z;
	if (bPosition.x < -playingRoom->uWidth/2.0f + bRadius && bDirection.x < 0.0f) 
		bDirection.x = -bDirection.x;
	if (bPosition.x > playingRoom->uWidth/2.0f - bRadius && bDirection.x > 0.0f) 
		bDirection.x = -bDirection.x;

	//Move the ball
	ballNode->translate(bSpeed * evt.timeSinceLastFrame * bDirection);
}
