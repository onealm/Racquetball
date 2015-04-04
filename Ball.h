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
		Ball(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld, bool isMulti); 
		~Ball();

		virtual void addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld);
		
		Ogre::SceneNode* ballNode;
		
		void moveBall(void)
		{
			btTransform transform;
			ballBody->getMotionState()->getWorldTransform(transform);

			btVector3 velocity = ballBody->getLinearVelocity();
			if(velocity[0] > 3000 || velocity[1] > 3000 || velocity[2] > 3000){}
			else{
				ballBody->setLinearVelocity(1.00005*velocity);
			}

			btVector3 pos = transform.getOrigin();
			ballNode->setPosition(Ogre::Vector3((float)pos[0], (float)pos[1], (float)pos[2]));

			btQuaternion btq = ballBody->getOrientation();
			Ogre::Quaternion quat  = Ogre::Quaternion(btq.w(), btq.x(), btq.y(), btq.z());

			ballNode->setOrientation(quat);
		}

		void moveBallTo(Ogre::Vector3 newPosition){
			btTransform trans;
			ballBody->getMotionState()->getWorldTransform(trans);
			trans.setOrigin(btVector3(newPosition.x, newPosition.y, newPosition.z));
			ballNode->setPosition(newPosition);
			ballBody->setWorldTransform(trans);
		}

		Ogre::Real bRadius;
		btRigidBody* getBody() { return ballBody; }
		void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }

};

#endif // BALL_H