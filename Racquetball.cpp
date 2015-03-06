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
Paddle *bigPaddle;
Sound *gameSound;
int time;
int score;

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
    time = 0;
    score = 0;
    //Ambient Light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    //Create Point Light
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 2000, 0));

    pointLight->setDiffuseColour(1.0, 1.0, 1.0);
    pointLight->setSpecularColour(1.0, 1.0, 1.0);

    //Sound
    gameSound = new Sound(mSceneMgr);
    gameSound->setBackgroundMusic();

    //Set Up Room
    playingRoom = new PlayingRoom(mSceneMgr);
    ball = new Ball(mSceneMgr);
    player = new Player(mSceneMgr);

    //Player Node
    Ogre::SceneNode* playerNode = mSceneMgr->getSceneNode("Player");

    bigPaddle = new Paddle(mSceneMgr, playerNode);

    /*Watch the Player
     *TODO:
     *Can still move mouse camera for now. Helps to see scene.
     *Eventually add a bit of outside scenery (waiting room) to see through "glass pane"
     *Have to be able to place camera outside of room to see player well enough 
     */
    //mCamera->setAutoTracking(true, mSceneMgr->getSceneNode("Player")); 
    mSceneMgr->getSceneNode("Player")->attachObject(mCamera);

    //mSceneMgr->getSceneNode("Player")->attachObject(mSceneMgr->getSceneNode("Paddle"));

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
    scoreLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "ScoreLabel", "Score: 0", 400);
 
}

bool Racquetball::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    static Ogre::Real mToggle = 0.0;    // The time left until next toggle
    static Ogre::Real mRotate = 0.13;   // The rotate constant
    static Ogre::Real mMove = 500;
    time++;

    moveBall(evt);

    Ogre::Vector3 transVector = Ogre::Vector3::ZERO;

    if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
    {
        transVector.z -= mMove;
        gameSound->playSwoosh();
    }
    if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
    {
        transVector.z += mMove;
        //gameSound->playHit(); //REMOVE
    }
    if (mKeyboard->isKeyDown(OIS::KC_A)) // Left
    {
        transVector.x -= mMove;
        //gameSound->playHit2(); //REMOVE
    }
    if (mKeyboard->isKeyDown(OIS::KC_D)) // Right
    {
        transVector.x += mMove;
        //gameSound->playScore(); //REMOVE
    }
    if (mKeyboard->isKeyDown(OIS::KC_P)) // Right
    {
        gameSound->toggleBackground();
    }
    //Temporary Score Workaround
    if (time >= 1500)
    {
        time = 0;
        score++;
        gameSound->playScore();

        Ogre::stringstream ss;
        ss << score;
        std::string str = ss.str();

        std::string s = "Score: " + str;

        scoreLabel->setCaption(Ogre::DisplayString(s)); 
    }

    mSceneMgr->getSceneNode("Player")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

    return true;
}
void Racquetball::moveBall(const Ogre::FrameEvent& evt) 
{

    Ogre::SceneNode* ballNode = mSceneMgr->getSceneNode("Ball");
    Ogre::Vector3 bPosition = ballNode->getPosition();

    //Find direction
    if (bPosition.y < -playingRoom->uHeight/4.0f + ball->bRadius + playingRoom->uHeight/4.0f && ball->bDirection.y < 0.0f)
    { 
        ball->bDirection.y = -ball->bDirection.y;
        gameSound->playHit();
    }
    if (bPosition.y > playingRoom->uHeight - ball->bRadius && ball->bDirection.y > 0.0f) 
    {
        ball->bDirection.y = -ball->bDirection.y;
        gameSound->playHit();
    }
    if (bPosition.z < -playingRoom->uLength/2.0f + ball->bRadius - playingRoom->uLength/8.0f && ball->bDirection.z < 0.0f) 
    {
        ball->bDirection.z = -ball->bDirection.z;
        gameSound->playHit();
    }
    if (bPosition.z > playingRoom->uLength/2.0f - ball->bRadius - playingRoom->uLength/8.0f && ball->bDirection.z > 0.0f) 
    {
        ball->bDirection.z = -ball->bDirection.z;
        gameSound->playHit();
    }
    if (bPosition.x < -playingRoom->uWidth/2.0f + ball->bRadius && ball->bDirection.x < 0.0f) 
    {
        ball->bDirection.x = -ball->bDirection.x;
        gameSound->playHit();
    }
    if (bPosition.x > playingRoom->uWidth/2.0f - ball->bRadius && ball->bDirection.x > 0.0f) 
    {
        ball->bDirection.x = -ball->bDirection.x;
        gameSound->playHit();
    }

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
