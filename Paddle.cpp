/*
-----------------------------------------------------------------------------
Filename:    Paddle.cpp
-----------------------------------------------------------------------------
*/

#include "Paddle.h"

/*
height desribes ydir
width describes xdir
length describes zdir
*/
Ogre::Real rHeight = 2000;
Ogre::Real rWidth = 2000;
Ogre::Real rLength = 4000;

Paddle::Paddle(Ogre::SceneManager* scnMgr) 
{ 
    //Create Plane for Paddle
	Ogre::Plane pPaddle(Ogre::Vector3::UNIT_Y, 0);

    Ogre::MeshManager::getSingleton().createPlane("pPaddle", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pPaddle, 500, 800, 5, 8, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    

    //Create Paddle Entities and Set Them
    Ogre::Entity *paddle = scnMgr->createEntity("paddle", "pPaddle");
    scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 500, 0))->attachObject(paddle);
    
    //Set Textures
    rFloor->setMaterialName("Metal_Steel_Textured");
    rFloor->setCastShadows(true);
}

Paddle::~Paddle(void)
{
}
