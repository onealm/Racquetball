/*
-----------------------------------------------------------------------------
Filename:    Player.h
-----------------------------------------------------------------------------

*/
#ifndef PLAYER_H
#define PLAYER_H

#include "BaseApplication.h"
#include <btBulletDynamicsCommon.h>
#include "PlayingRoom.h"
#include <stdio.h>
#include <stdlib.h>

namespace gTech {

class Player
{
	protected:
		Ogre::SceneNode* playerNode;
		PlayingRoom* playingRoom;
		btTransform transform;
		btRigidBody *body;
	public:
		Player(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld);
		~Player();

		virtual void addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld);

		void movePaddle(Ogre::Vector3 dist)
		{
			/*Ogre::Vector3 origin = playerNode->getPosition() + Ogre::Vector3(25, 115, -25) + dist;
			transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
			body->getMotionState()->setWorldTransform(transform);*/
		}
		
		Ogre::SceneNode* getNode() { return playerNode; }
		void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }
};

} // namespace gTech
#endif // PLAYER_H