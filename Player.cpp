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
}

Player::~Player(void)
{
}

} // namespace gTech