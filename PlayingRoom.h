#ifndef PLAYING_ROOM_H
#define PLAYING_ROOM_H
/*
-----------------------------------------------------------------------------
Filename:    PlayingRoom.h
-----------------------------------------------------------------------------
*/

#include "BaseApplication.h"
#include <btBulletDynamicsCommon.h>

class PlayingRoom
{
	protected:
		

	public:
		PlayingRoom(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld);
		~PlayingRoom();
		btRigidBody *body;
		
		virtual void addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld, Ogre::Vector3 norm);
		
		Ogre::SceneNode *floorNode;
		Ogre::SceneNode *ceilingNode;
		Ogre::SceneNode *wall1Node;
		Ogre::SceneNode *wall2Node;
		Ogre::SceneNode *wall3Node;
		Ogre::SceneNode *wall4Node;

		float uHeight;
		float uLength;
		float uWidth;
		float getHeight(void);
		float getLength(void);
		float getWidth(void);
};

#endif // PLAYING_ROOM_H