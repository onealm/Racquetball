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
	PlayingRoom* playingRoom;
	Ogre::SceneNode* ballNode;
	float bWidth;
	float bLength;
public:
	Ball(Ogre::SceneManager* scnMgr);
	~Ball();
	Ogre::Real bRadius;
	Ogre::Vector3 bDirection;
	Ogre::Real bSpeed;
	Ogre::SceneNode* getNode() { return ballNode; }
	void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }
};

#endif // BALL_H