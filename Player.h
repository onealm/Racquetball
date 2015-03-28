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
			//btTransform transform;
			body->getMotionState()->getWorldTransform(transform);
		
			btVector3 pos = transform.getOrigin();
			playerNode->setPosition(Ogre::Vector3((float)pos[0], (float)pos[1], (float)pos[2]));

			Ogre::Vector3 origin = playerNode->getPosition() + dist;
			transform.setOrigin(btVector3(origin.x, origin.y, origin.z));
			//body->setLinearVelocity(btVector3(origin);

			btQuaternion btq = body->getOrientation();
			Ogre::Quaternion quat  = Ogre::Quaternion(btq.w(), btq.x(), btq.y(), btq.z());
			
			playerNode->setOrientation(quat);

		}
		
		Ogre::SceneNode* getNode() { return playerNode; }
		void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }
};

} // namespace gTech
#endif // PLAYER_H