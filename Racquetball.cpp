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

    //Set Up Room
    playingRoom = new PlayingRoom(mSceneMgr);
    ball = new Ball(mSceneMgr);
    player = new Player(mSceneMgr);

    /*Watch the Player
     *TODO:
     *Can still move mouse camera for now. Helps to see scene.
     *Eventually add a bit of outside scenery (waiting room) to see through "glass pane"
     *Have to be able to place camera outside of room to see player well enough 
     */
    //mCamera->setAutoTracking(true, mSceneMgr->getSceneNode("Player")); 
    mSceneMgr->getSceneNode("Player")->attachObject(mCamera);

    // playingRoom->addChild(ball->getNode());
    // playingRoom->addChild(player->getNode());

    ball->setPlayingRoom(playingRoom);
    player->setPlayingRoom(playingRoom);
}
//---------------------------------------------------------------------------

//Create Camera
void Racquetball::createCamera(void)
{
    //Camera Creation
    mCamera = mSceneMgr->createCamera("PlayerCam");

    //Set Camera Position 
    mCamera->setPosition(Ogre::Vector3(0, 400, 1750));

    //Set Camera Direction
    mCamera->lookAt(Ogre::Vector3(0, 750, -1000));

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
void Racquetball::createFrameListener(void)
{
    BaseApplication::createFrameListener();
    
    //Label for score. Change with setCaption(const Ogre::DisplayString& caption)
    scoreLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "ScoreLabel", "Score: 0", 200);
 
}

bool Racquetball::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    static Ogre::Real mToggle = 0.0;    // The time left until next toggle
    static Ogre::Real mRotate = 0.13;   // The rotate constant
    static Ogre::Real mMove = 500;

    moveBall(evt);

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
void Racquetball::moveBall(const Ogre::FrameEvent& evt) 
{

    Ogre::SceneNode* ballNode = mSceneMgr->getSceneNode("Ball");
    Ogre::Vector3 bPosition = ballNode->getPosition();

    //Find direction
    if (bPosition.y < -playingRoom->uHeight/2.0f + ball->bRadius && ball->bDirection.y < 0.0f) 
        ball->bDirection.y = -ball->bDirection.y;
    if (bPosition.y > playingRoom->uHeight/2.0f - ball->bRadius && ball->bDirection.y > 0.0f) 
        ball->bDirection.y = -ball->bDirection.y;
    if (bPosition.z < -playingRoom->uLength/2.0f + ball->bRadius && ball->bDirection.z < 0.0f) 
        ball->bDirection.z = -ball->bDirection.z;
    if (bPosition.z > playingRoom->uLength/2.0f - ball->bRadius && ball->bDirection.z > 0.0f) 
        ball->bDirection.z = -ball->bDirection.z;
    if (bPosition.x < -playingRoom->uWidth/2.0f + ball->bRadius && ball->bDirection.x < 0.0f) 
        ball->bDirection.x = -ball->bDirection.x;
    if (bPosition.x > playingRoom->uWidth/2.0f - ball->bRadius && ball->bDirection.x > 0.0f) 
        ball->bDirection.x = -ball->bDirection.x;

    //Move the ball
    ballNode->translate(ball->bSpeed * evt.timeSinceLastFrame * ball->bDirection);
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
