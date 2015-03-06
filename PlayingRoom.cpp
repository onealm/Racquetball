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

PlayingRoom::PlayingRoom(Ogre::SceneManager* scnMgr, btDiscreteDynamicsWorld *ourWorld) 
{
    uHeight = rHeight;
    uWidth = rWidth;
    uLength = rLength;
    //This is really messy looking, oh well, FiX this if we have time to
    //Create Room Planes
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


    //Create Plane Entities and Set Them
    Ogre::Entity *rFloor = scnMgr->createEntity("rFloor", "pFloor");
    Ogre::SceneNode *floorNode = scnMgr->getRootSceneNode()->createChildSceneNode("Floor", Ogre::Vector3(0, 0, -rLength/8));
    floorNode->attachObject(rFloor);

    Ogre::Entity *rCeiling = scnMgr->createEntity("rCeiling", "pCeiling");
    Ogre::SceneNode *ceilingNode = scnMgr->getRootSceneNode()->createChildSceneNode("Ceiling", Ogre::Vector3(0, rHeight, -rLength/8));
    ceilingNode->attachObject(rCeiling);

    Ogre::Entity *rWall1 = scnMgr->createEntity("rWall1", "pWall1");
    Ogre::SceneNode *wall1Node = scnMgr->getRootSceneNode()->createChildSceneNode("Wall1", Ogre::Vector3(rWidth/2, rHeight/2, -rLength/8));
    wall1Node->attachObject(rWall1);

    Ogre::Entity *rWall2 = scnMgr->createEntity("rWall2", "pWall2");
    Ogre::SceneNode *wall2Node = scnMgr->getRootSceneNode()->createChildSceneNode("Wall2", Ogre::Vector3(-rWidth/2, rHeight/2, -rLength/8));
    wall2Node->attachObject(rWall2);

    Ogre::Entity *rWall3 = scnMgr->createEntity("rWall3", "pWall3");
    Ogre::SceneNode *wall3Node = scnMgr->getRootSceneNode()->createChildSceneNode("Wall3", Ogre::Vector3(0, rHeight/2, rLength/2-rLength/8));
    wall3Node->attachObject(rWall3);

    Ogre::Entity *rWall4 = scnMgr->createEntity("rWall4", "pWall4");
    Ogre::SceneNode *wall4Node = scnMgr->getRootSceneNode()->createChildSceneNode("Wall4", Ogre::Vector3(0, rHeight/2, -rLength/2-rLength/8));
    wall4Node->attachObject(rWall4);

    //Set Textures
    rFloor->setMaterialName("Gym_Floor");
    rFloor->setCastShadows(true);
    rCeiling->setMaterialName("Ceiling");
    rCeiling->setCastShadows(true);
    rWall1->setMaterialName("Side_Walls");
    rWall1->setCastShadows(true);
    rWall2->setMaterialName("Side_Walls");
    rWall2->setCastShadows(true);
    rWall3->setMaterialName("White_Wall");
    rWall3->setCastShadows(true);
    rWall4->setMaterialName("White_Wall");
    rWall4->setCastShadows(true);

    addToWorld(floorNode, ourWorld, Ogre::Vector3::UNIT_Y);
    addToWorld(ceilingNode, ourWorld, -Ogre::Vector3::UNIT_Y);
    addToWorld(wall1Node, ourWorld, -Ogre::Vector3::UNIT_X);
    addToWorld(wall2Node, ourWorld, Ogre::Vector3::UNIT_X);
    addToWorld(wall3Node, ourWorld, -Ogre::Vector3::UNIT_Z);
    addToWorld(wall4Node, ourWorld, Ogre::Vector3::UNIT_Z);
}

PlayingRoom::~PlayingRoom(void)
{
}

void PlayingRoom::addToWorld(Ogre::SceneNode *newBtNode, btDiscreteDynamicsWorld *ourWorld, Ogre::Vector3 norm)
{
    Ogre::Vector3 pos = newBtNode->getPosition();
    btScalar mass(0.0f);
    btVector3 localInertia(0, 0, 0);

    btCollisionShape *shape = new btStaticPlaneShape(btVector3(norm.x, norm.y, norm.z), 0);
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    shape->calculateLocalInertia(mass, localInertia);
    btDefaultMotionState *motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
    rbInfo.m_restitution = 1;
    rbInfo.m_friction = 0;
    btRigidBody *body = new btRigidBody(rbInfo);
    body->setUserPointer((void *)(newBtNode));
    ourWorld->addRigidBody(body);
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