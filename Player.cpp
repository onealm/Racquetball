#include "Player.h"

namespace gTech {

Player::Player(Ogre::SceneManager* scnMgr) 
{
	//Create ball
	Ogre::Entity* player = scnMgr->createEntity("Player", "ninja.mesh");

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

// void Player::frameRenderingQueued(const Ogre::FrameEvent& evt) 
// {
// 	bool ret = BaseApplication::frameRenderingQueued(evt);

// 	if (!processUnbufferedInput(evt))
// 		return false;

// 	return ret;

	
// }

// bool Player::processUnbufferedInput(const Ogre::FrameEvent& evt)
// {
//     static Ogre::Real mToggle = 0.0;    // The time left until next toggle
//     static Ogre::Real mRotate = 0.13;   // The rotate constant
//     static Ogre::Real mMove = 250;

//     Ogre::Vector3 transVector = Ogre::Vector3::ZERO;

// 	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
// 	{
//     	transVector.z -= mMove;
// 	}
// 	if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
// 	{
// 	    transVector.z += mMove;
// 	}

// 	mSceneMgr->getSceneNode("NinjaNode")->translate
// 		(mSceneMgr->getSceneNode("NinjaNode")->getOrientation() * transVector * evt.timeSinceLastFrame, Ogre::Node::TS_WORLD);
// }

} // namespace gTech