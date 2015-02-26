/*
-----------------------------------------------------------------------------
Filename:    Racquetball.cpp
-----------------------------------------------------------------------------

*/

#include "Racquetball.h"

namespace gTech {

PlayingRoom *playingRoom;
Ball *ball;
Player *player;

//---------------------------------------------------------------------------
Racquetball::Racquetball(void)
{
}
//---------------------------------------------------------------------------
Racquetball::~Racquetball(void)
{
}

//---------------------------------------------------------------------------
void Racquetball::createScene(void)
{
    //Ambient Light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    // Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
    // spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    // spotLight->setDiffuseColour(0, 0, 1.0);
    // spotLight->setSpecularColour(0, 0, 1.0);

    // spotLight->setDirection(-1, -1, 0);
    // spotLight->setPosition(Ogre::Vector3(300, 300, 0));

    playingRoom = new PlayingRoom(mSceneMgr);

    ball = new Ball(mSceneMgr);
    player = new Player(mSceneMgr);

    mCamera->setAutoTracking(true, mSceneMgr->getSceneNode("Player"));


    // playingRoom->addChild(ball->getNode());
    // playingRoom->addChild(player->getNode());

    ball->setPlayingRoom(playingRoom);
    player->setPlayingRoom(playingRoom);
}
//---------------------------------------------------------------------------

/*  
 *  Create Camera
 *  TODO: Follow Player/Paddle
 */
void Racquetball::createCamera(void)
{
    //Camera Creation
    mCamera = mSceneMgr->createCamera("PlayerCam");

    //Set Camera Position 
    mCamera->setPosition(Ogre::Vector3(0,1000,1000));

    //Set Camera Direction
    mCamera->lookAt(Ogre::Vector3(0, 700, -1000));

    //Set Near Clip Distance
    mCamera->setNearClipDistance(5);
 
    //Default Camera Controller
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

bool Racquetball::frameRenderingQueued(const Ogre::FrameEvent& evt) 
{
    bool ret = BaseApplication::frameRenderingQueued(evt);

    if (!processUnbufferedInput(evt))
        return false;

    return ret; 
}

bool Racquetball::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    static Ogre::Real mToggle = 0.0;    // The time left until next toggle
    static Ogre::Real mRotate = 0.13;   // The rotate constant
    static Ogre::Real mMove = 500;

    bool moved = false;

    Ogre::Vector3 transVector = Ogre::Vector3::ZERO;

    if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
    {
        transVector.z -= mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
    {
        transVector.z += mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_A)) // Forward
    {
        transVector.x -= mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_D)) // Backward
    {
        transVector.x += mMove;
    }

    mSceneMgr->getSceneNode("Player")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

    return true;
}

} // namespace gTech



#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, char *argv[])
    {
        // Create application object
        gTech::Racquetball app;

        try {
            app.go();
        } 
        catch(Ogre::Exception& e)  {
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
