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

class Ball 
{
	protected:
		PlayingRoom* playingRoom;
		
		btRigidBody *ballBody;

	public:
		Ball(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld);
		~Ball();

		virtual void addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld);
		
		Ogre::SceneNode* ballNode;
		
		void moveBall(void)
		{
			btTransform transform;
			ballBody->getMotionState()->getWorldTransform(transform);

			btVector3 velocity = ballBody->getLinearVelocity();
			ballBody->setLinearVelocity(1.00001*velocity);

			btVector3 pos = transform.getOrigin();
			ballNode->setPosition(Ogre::Vector3((float)pos[0], (float)pos[1], (float)pos[2]));

			btQuaternion btq = ballBody->getOrientation();
			Ogre::Quaternion quat  = Ogre::Quaternion(btq.w(), btq.x(), btq.y(), btq.z());

			ballNode->setOrientation(quat);
		}

		Ogre::Real bRadius;
		btRigidBody* getBody() { return ballBody; }
		void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }

};

#endif // BALL_H