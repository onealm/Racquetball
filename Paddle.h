#ifndef PADDLE_H
#define PADDLE_H
/*
-----------------------------------------------------------------------------
Filename:    Paddle.h
-----------------------------------------------------------------------------
*/

#include "BaseApplication.h"
#include <btBulletDynamicsCommon.h>
#include <stdio.h>
#include <stdlib.h>

class Paddle
{
	protected:
		Ogre::SceneNode *padNode;

	public:
		Paddle(Ogre::SceneManager* scnMgr, Ogre::SceneNode* playerNode);
		~Paddle();

};

#endif // PADDLE_H