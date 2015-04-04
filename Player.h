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

//btVector3 size = btVector3(2000,2000,4000);

class Player
{
	protected:
		
		PlayingRoom* playingRoom;
		btTransform transform;
		btRigidBody *body;
	public:
		Player(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld);
		Player(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld, bool play2);
		~Player();

		Ogre::SceneNode * getPlayerNode2(void);

		virtual void addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld);

		Ogre::SceneNode* playerNode;
		Ogre::SceneNode* playerNode2;

		void movePaddle(Ogre::Vector3 translation)
		{			
			//(225, 75, 22.5)
			//
			btVector3 pos = transform.getOrigin() + btVector3(translation.x, translation.y, translation.z);
			if((float)pos[0] > -775.5 && (float)pos[0] < 775.5 &&
				(float)pos[1] > 75 && (float)pos[1] < 1925 &&
					(float)pos[2] > -750 && (float)pos[2] < 1485) {
						transform.getOrigin() += btVector3(translation.x, translation.y, translation.z);
						playerNode->setPosition(Ogre::Vector3((float)pos[0], (float)pos[1], (float)pos[2]));
			}
			body->setWorldTransform(transform);
		}

		void movePaddleTo(Ogre::Vector3 newPosition){
			
						transform.setOrigin(btVector3(newPosition.x, newPosition.y, newPosition.z));
						playerNode2->setPosition(newPosition);
			
			body->setWorldTransform(transform);
		}
		
		Ogre::SceneNode* getNode() { return playerNode; }
		void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }
};

} // namespace gTech
#endif // PLAYER_H