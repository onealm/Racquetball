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

		virtual void addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld, Ogre::Vector3 norm);

		float uHeight;
		float uLength;
		float uWidth;
		float getHeight(void);
		float getLength(void);
		float getWidth(void);
};

#endif // PLAYING_ROOM_H