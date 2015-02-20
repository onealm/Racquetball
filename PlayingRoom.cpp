/*
-----------------------------------------------------------------------------
Filename:    PlayingRoom.cpp
-----------------------------------------------------------------------------
*/

#include "PlayingRoom.h"

/*
height desribes ydir
width describes xdir
length describes zdir
*/
Ogre::Real rHeight = 2000;
Ogre::Real rWidth = 2000;
Ogre::Real rLength = 4000;

PlayingRoom::PlayingRoom(Ogre::SceneManager* scnMgr) 
{
	Ogre::Plane pFloor(Ogre::Vector3::UNIT_Y, 0);
    Ogre::Plane pCeiling(-Ogre::Vector3::UNIT_Y, 0);
    Ogre::Plane pWall1(-Ogre::Vector3::UNIT_X, 0);
    Ogre::Plane pWall2(Ogre::Vector3::UNIT_X, 0);
    Ogre::Plane pWall3(-Ogre::Vector3::UNIT_Z, 0);
    Ogre::Plane pWall4(Ogre::Vector3::UNIT_Z, 0);

    Ogre::MeshManager::getSingleton().createPlane("pFloor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pFloor, rWidth, rLength, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::MeshManager::getSingleton().createPlane("pCeiling", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pCeiling, rWidth, rLength, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::MeshManager::getSingleton().createPlane("pWall1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pWall1, rLength, rHeight, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane("pWall2", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pWall2, rLength, rHeight, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane("pWall3", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pWall3, rWidth, rHeight, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
    Ogre::MeshManager::getSingleton().createPlane("pWall4", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, pWall4, rWidth, rHeight, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);

    Ogre::Entity *rFloor = scnMgr->createEntity("rFloor", "pFloor");
    scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, -rLength/8))->attachObject(rFloor);
    Ogre::Entity *rCeiling = scnMgr->createEntity("rCeiling", "pCeiling");
    scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, rHeight, -rLength/8))->attachObject(rCeiling);
    Ogre::Entity *rWall1 = scnMgr->createEntity("rWall1", "pWall1");
    scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(rWidth/2, rHeight/2, -rLength/8))->attachObject(rWall1);
    Ogre::Entity *rWall2 = scnMgr->createEntity("rWall2", "pWall2");
    scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-rWidth/2, rHeight/2, -rLength/8))->attachObject(rWall2);
    Ogre::Entity *rWall3 = scnMgr->createEntity("rWall3", "pWall3");
    scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, rHeight/2, rLength/2-rLength/8))->attachObject(rWall3);
    Ogre::Entity *rWall4 = scnMgr->createEntity("rWall4", "pWall4");
    scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, rHeight/2, -rLength/2-rLength/8))->attachObject(rWall4);

    rFloor->setMaterialName("Examples/Rockwall");
    rFloor->setCastShadows(true);
    rCeiling->setMaterialName("Examples/Rockwall");
    rCeiling->setCastShadows(true);
    rWall1->setMaterialName("Examples/Rockwall");
    rWall1->setCastShadows(true);
    rWall2->setMaterialName("Examples/Rockwall");
    rWall2->setCastShadows(true);
    rWall3->setMaterialName("Examples/Rockwall");
    rWall3->setCastShadows(true);
    rWall4->setMaterialName("Examples/Rockwall");
    rWall4->setCastShadows(true);
}

PlayingRoom::~PlayingRoom(void)
{

}

float getHeight(void)
{
	return rHeight;
}
float getLength(void)
{
	return rWidth;
}
float getWidth(void)
{
	return rLength;
}