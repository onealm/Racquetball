#ifndef PADDLE_H
#define PADDLE_H
/*
-----------------------------------------------------------------------------
Filename:    Paddle.h
-----------------------------------------------------------------------------
*/

#include "BaseApplication.h"

class Paddle
{
	protected:
		

	public:
		Paddle(Ogre::SceneManager* scnMgr, Ogre::SceneNode* playerNode);
		~Paddle();
};

#endif // PADDLE_H