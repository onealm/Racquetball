/*
-----------------------------------------------------------------------------
Filename:    Ball.h
-----------------------------------------------------------------------------

*/

#include "BaseApplication.h"

class Ball 
{
protected:
	Ogre::SceneNode* ballNode;
	Ogre::Real ballRadius;
	Ogre::Vector3 ballDirection;
	Ogre::Real ballSpeed;
	PlayingField* playingRoom;
public:
	Ball(Ogre::SceneManager* scnMgr);
	~Ball();
	void move(const Ogre::FrameEvent& evt);
	Ogre::SceneNode* getNode() { return rootNode; }
	void setPlayingField(PlayingField * pr) { playingRoom = pr; }
};