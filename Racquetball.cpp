/*
-----------------------------------------------------------------------------
Filename:    Racquetball.cpp
-----------------------------------------------------------------------------

*/

#include "Racquetball.h"

PlayingRoom *playingRoom;
Ball *ball;

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

    playingRoom = new PlayingRoom(mSceneMgr);
    ball = new Ball(mSceneMgr);
    //playingRoom->addChild(ball->getNode());
    ball->setPlayingRoom(playingRoom);
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
    mCamera->setPosition(Ogre::Vector3(0,200,0));

    //Set Camera Direction
    mCamera->lookAt(Ogre::Vector3(0, 500, -200));

    //Set Near Clip Distance
    mCamera->setNearClipDistance(5);
 
    //Default Camera Controller
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}





#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, char *argv[])
    {
        // Create application object
        Racquetball app;

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
