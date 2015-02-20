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
	float getHeight(void);
	float getLength(void);
	float getWidth(void);
};