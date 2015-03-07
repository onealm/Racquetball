/*
-----------------------------------------------------------------------------
Filename:    Paddle.cpp
-----------------------------------------------------------------------------
*/

#include "Paddle.h"

Paddle::Paddle(Ogre::SceneManager* scnMgr, Ogre::SceneNode* playerNode) 
{ 
    //Create Plane for Paddle
    Ogre::Plane pPaddle(-Ogre::Vector3::UNIT_Z, 0);

    Ogre::MeshManager::getSingleton().createPlane("pPaddle", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pPaddle, 120, 120, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
    Ogre::Entity *rPaddle = scnMgr->createEntity("pPaddle", "pPaddle");
    padNode = playerNode->createChildSceneNode("Paddle", Ogre::Vector3(25, 115, -25));

    padNode->attachObject(rPaddle);

    rPaddle->setMaterialName("TransparentGlassTinted");
    rPaddle->setCastShadows(true);

    //Back Paddle for Looks fthis
    {
        Ogre::Plane pPaddle1(Ogre::Vector3::UNIT_Z, 0);

        Ogre::MeshManager::getSingleton().createPlane("pPaddle1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pPaddle1, 120, 120, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
        Ogre::Entity *rPaddle1 = scnMgr->createEntity("pPaddle1", "pPaddle1");
        Ogre::SceneNode *padNode1 = playerNode->createChildSceneNode("Paddle1", Ogre::Vector3(25, 115, -24));

        padNode1->attachObject(rPaddle1);

        rPaddle1->setMaterialName("TransparentGlassTinted");
        rPaddle1->setCastShadows(true);
    }
}

Paddle::~Paddle(void)
{
}
