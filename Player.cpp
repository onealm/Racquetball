/*
-----------------------------------------------------------------------------
Filename:    Player.cpp
-----------------------------------------------------------------------------

*/

#include "Player.h"

namespace gTech {

Player::Player(Ogre::SceneManager* scnMgr) 
{
	//Create ball
	Ogre::Entity* player = scnMgr->createEntity("Player1", "ninja.mesh");

	player->setCastShadows(true);

	//Attach ball to node
	playerNode = scnMgr->getRootSceneNode()->createChildSceneNode("Player", Ogre::Vector3(0, 0, 0));
	playerNode->attachObject(player);


	playerNode->scale(2.5f, 2.5f, 2.5f);

	//Set ball properties
	// ballRadius = 10.0f;
	// ballDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f);
	// ballDirection.normalise();
	// ballSpeed = 250.0f;
}

Player::~Player(void)
{
}

} // namespace gTech