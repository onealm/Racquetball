#include "Player.h"

namespace gTech {

Player::Player(Ogre::SceneManager* scnMgr) 
{
	//Create ball
	Ogre::Entity* player = scnMgr->createEntity("Player", "ninja.mesh");
	player->setMaterialName("BallColor/CubeMap");
	player->setCastShadows(true);

	//Attach ball to node
	playerNode = scnMgr->getRootSceneNode()->createChildSceneNode("scenePlayer", Ogre::Vector3(0, 0, 0));
	playerNode->attachObject(player);
	//playerNode->scale(0.1f,0.1f,0.1f);

	//Set ball properties
	// ballRadius = 10.0f;
	// ballDirection = Ogre::Vector3(1.0f, 2.0f, 3.0f);
	// ballDirection.normalise();
	// ballSpeed = 250.0f;
}

Player::~Player(void)
{
}

// void Player::move(const Ogre::FrameEvent& evt) 
// {
// 	//Locate the ball
// 	Ogre::Vector3 bPosition = playerNode->getPosition();

// 	//Find direction
// 	if (bPosition.y < -playingRoom->getHeight()/2.0f + bRadius && bDirection.y < 0.0f) 
// 		bDirection.y = -bDirection.y;
// 	if (bPosition.y > playingRoom->getHeight()/2.0f - bRadius && bDirection.y > 0.0f) 
// 		bDirection.y = -bDirection.y;
// 	if (bPosition.z < -playingRoom->getLength()/2.0f + bRadius && bDirection.z < 0.0f) 
// 		bDirection.z = -bDirection.z;
// 	if (bPosition.z > playingRoom->getLength()/2.0f - bRadius && bDirection.z > 0.0f) 
// 		bDirection.z = -bDirection.z;
// 	if (bPosition.x < -playingRoom->getWidth()/2.0f + bRadius && bDirection.x < 0.0f) 
// 		bDirection.x = -bDirection.x;
// 	if (bPosition.x > playingRoom->getWidth()/2.0f - bRadius && bDirection.x > 0.0f) 
// 		bDirection.x = -bDirection.x;

// 	//Move the ball
// 	playerNode->translate(bSpeed * evt.timeSinceLastFrame * bDirection);
// }

} // namespace gTech