/*
-----------------------------------------------------------------------------
Filename:    Ball.h
-----------------------------------------------------------------------------

*/

#include "BaseApplication.h"
#include "PlayingRoom.h"

class Ball 
{
protected:
	Ogre::SceneNode* ballNode;
	Ogre::Real ballRadius;
	Ogre::Vector3 ballDirection;
	Ogre::Real ballSpeed;
	PlayingRoom* playingRoom;
	Ogre::Real bRadius;
	Ogre::Real bSpeed;
	Ogre::Vector3 bDirection;
public:
	Ball(Ogre::SceneManager* scnMgr, PlayingRoom* playingRoom);
	~Ball();
	void move(const Ogre::FrameEvent& evt);
};