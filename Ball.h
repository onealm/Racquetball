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
public:
	Ball(Ogre::SceneManager* scnMgr);
	~Ball();
	void move(const Ogre::FrameEvent& evt);
	Ogre::SceneNode* getNode() { return ballNode; }
	void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }
};