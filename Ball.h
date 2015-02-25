/*
-----------------------------------------------------------------------------
Filename:    Ball.h
-----------------------------------------------------------------------------

*/
#ifndef BALL_H
#define BALL_H

#include "BaseApplication.h"
#include "PlayingRoom.h"


class Ball 
{
protected:
	Ogre::SceneNode* ballNode;
	Ogre::Real bRadius;
	Ogre::Vector3 bDirection;
	Ogre::Real bSpeed;
	PlayingRoom* playingRoom;
	float bWidth;
	float bLength;
public:
	Ball(Ogre::SceneManager* scnMgr);
	~Ball();
	void move(const Ogre::FrameEvent& evt);
	Ogre::SceneNode* getNode() { return ballNode; }
	void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }
};

#endif // BALL_H