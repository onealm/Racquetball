/*
-----------------------------------------------------------------------------
Filename:    Ball.h
-----------------------------------------------------------------------------

*/
#ifndef BALL_H
#define BALL_H

#include "BaseApplication.h"
#include "PlayingRoom.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>

class Ball 
{
	protected:
		PlayingRoom* playingRoom;
		Ogre::SceneNode* ballNode;
		btRigidBody *ballBody;

	public:
		Ball(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld);
		~Ball();

		virtual void addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld);

		void moveBall(void)
		{
			btTransform transform;
			ballBody->getMotionState()->getWorldTransform(transform);
			//std::cout << transform.getOrigin().getY() << std::endl;
			btVector3 pos = transform.getOrigin();
			ballNode->setPosition(Ogre::Vector3((float)pos[0], (float)pos[1], (float)pos[2]));

			btQuaternion btq = ballBody->getOrientation();
			Ogre::Quaternion quat  = Ogre::Quaternion(btq.w(), btq.x(), btq.y(), btq.z());

			ballNode->setOrientation(quat);
		}

		Ogre::Real bRadius;
		Ogre::SceneNode* getNode() { return ballNode; }
		void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }

};

#endif // BALL_H