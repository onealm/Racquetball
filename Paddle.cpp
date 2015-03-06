/*
-----------------------------------------------------------------------------
Filename:    Paddle.cpp
-----------------------------------------------------------------------------
*/

#include "Paddle.h"

Paddle::Paddle(Ogre::SceneManager* scnMgr, Ogre::SceneNode* playerNode) 
{ 
    //Create Plane for Paddle
	Ogre::Plane pPaddle(Ogre::Vector3::UNIT_Y, 0);

    Ogre::MeshManager::getSingleton().createPlane("pPaddle", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pPaddle, 200, 400, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

    //Create Paddle Entity and attach to player
    Ogre::Entity *rPaddle = scnMgr->createEntity("rPaddle", "pPaddle");
    Ogre::SceneNode* padNode = playerNode->createChildSceneNode("Paddle", Ogre::Vector3(25, 115, -25));
    padNode->attachObject(rPaddle);

    //Rotate to see
    padNode->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(90));
    padNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    padNode->scale(.4f,.4f,.4f);
    
    //Set Texture
    rPaddle->setMaterialName("Metal_Steel_Textured");
    rPaddle->setCastShadows(true);
}

Paddle::~Paddle(void)
{
}