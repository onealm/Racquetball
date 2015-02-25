#ifndef PLAYING_ROOM_H
#define PLAYING_ROOM_H
/*
-----------------------------------------------------------------------------
Filename:    PlayingRoom.h
-----------------------------------------------------------------------------
*/

#include "BaseApplication.h"

class PlayingRoom
{
protected:
	

public:
	PlayingRoom(Ogre::SceneManager* scnMgr);
	~PlayingRoom();
	float uHeight;
	float uLength;
	float uWidth;
	float getHeight(void);
	float getLength(void);
	float getWidth(void);
};

#endif // PLAYING_ROOM_H