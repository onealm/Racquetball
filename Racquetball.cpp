/*
-----------------------------------------------------------------------------
Filename:    Racquetball.cpp
-----------------------------------------------------------------------------

*/

#include "Racquetball.h"

namespace gTech 
{

    int time;
    int score;
    btDiscreteDynamicsWorld *ourWorld;
    PlayingRoom *playingRoom;
    Ball *ball;
    Player *player;
    Sound *gameSound;
    NetManager *mNet;
    std::deque<Ogre::Vector3> mWalkList;
    const int gameTime = 10;
    bool isClient;
    bool isServer;
    Uint16 port = 77777;
    // TCPSocket *hostSocket;
    // TCPSocket *clientSocket;

    //---------------------------------------------------------------------------
    Racquetball::Racquetball(void)
    {
    }
    //---------------------------------------------------------------------------
    Racquetball::~Racquetball(void)
    {
    }

    //---------------------------------------------------------------------------
    void Racquetball::initPhysics(void)
    {
        ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
    
        ourWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

        ourWorld->setGravity(btVector3(0,-45.80,0));
    }

    //---------------------------------------------------------------------------
    void Racquetball::createScene(void)
    {
        initPhysics();
        setupNetworking();

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
        playingRoom = new PlayingRoom(mSceneMgr, ourWorld);
        ball = new Ball(mSceneMgr, ourWorld);
        setupLights();
        player = new Player(mSceneMgr, ourWorld);

        //Player Node
        Ogre::SceneNode* playerNode = mSceneMgr->getSceneNode("Player");

        //bigPaddle = new Paddle(mSceneMgr, playerNode);

        /*Watch the Player
         *TODO:
         *Can still move mouse camera for now. Helps to see scene.
         *Eventually add a bit of outside scenery (waiting room) to see through "glass pane"
         *Have to be able to place camera outside of room to see player well enough 
         */
        //mCamera->setAutoTracking(true, mSceneMgr->getSceneNode("Player")); 
        mSceneMgr->getSceneNode("Player")->attachObject(mCamera);

        ball->setPlayingRoom(playingRoom);
        player->setPlayingRoom(playingRoom);
    }

    //Setup Networking
    //Not sure if this is the right place to put this
    void Racquetball::setupNetworking(void)
    {
        //Eventually have to make only one instance of game be server?
        //Or listen first and if nothing is open, start server?
        mNet = new NetManager();


        if(mNet->initNetManager() == false)
        {
            printf("SDL_net: Unable to initialize.");
        }
        if (isServer)
        {
            mNet->addNetworkInfo(PROTOCOL_TCP);
            mNet->setPort(port);
            mNet->startServer();
        }
        else
        {
            mNet->addNetworkInfo(PROTOCOL_TCP);
            mNet->setPort(port);
            mNet->setHost("localhost");
            mNet->startClient();
        }

    }

    void Racquetball::setupLights(void) 
    { 
        mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5,0.5,0.5)); 
        Ogre::Vector3 dir(-1,-1,0.5); dir.normalise(); 
        Ogre::Light* l = mSceneMgr->createLight("light1"); 
        l->setType(Ogre::Light::LT_DIRECTIONAL); 
        l->setDirection(dir);

        Ogre::NameValuePairList pairList; 
        pairList["numberOfChains"] = "1"; 
        pairList["maxElements"] = "80"; 
        Ogre::RibbonTrail* trail = static_cast<Ogre::RibbonTrail*>(mSceneMgr->createMovableObject("1", "RibbonTrail", &pairList)); 
        trail->setMaterialName("Examples/LightRibbonTrail"); 
        trail->setTrailLength(400);

        mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(trail);

        trail->setInitialColour(0, 1.0, 0.8, 0); 
        trail->setColourChange(0, 0.5, 0.5, 0.5, 0.5); 
        trail->setInitialWidth(0, ball->bRadius); 
        trail->addNode(mSceneMgr->getSceneNode("Ball")); 
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
        gameOver = mTrayMgr->createLabel(OgreBites::TL_BOTTOM, "GameOver", "Time Left: " + gameTime, 300);
     
    }

    bool Racquetball::processUnbufferedInput(const Ogre::FrameEvent& evt)
    {
        static Ogre::Real mToggle = 0.0;    // The time left until next toggle
        static Ogre::Real mRotate = 0.13;   // The rotate constant
        static Ogre::Real mMove = 500;
        static Ogre::Real mTime = 0;
        static Ogre::Real mCollision = 0.0;

        mTime += evt.timeSinceLastFrame;
        mToggle -= evt.timeSinceLastFrame;
        mCollision -= evt.timeSinceLastFrame;
        time++;

        isServer = true;

        Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
        if (isServer)
        {
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
            if (mKeyboard->isKeyDown(OIS::KC_Z)) // Down
            {
                transVector.y -= mMove;
                //gameSound->playScore(); //REMOVE
            }
            if (mKeyboard->isKeyDown(OIS::KC_SPACE)) // Up
            {
                transVector.y += mMove;
            }

            if (mToggle < 0.0f && mKeyboard->isKeyDown(OIS::KC_P))
            {
                mToggle = 0.5;
                gameSound->toggleBackground();
            }
            if (mToggle < 0.0f && mKeyboard->isKeyDown(OIS::KC_M))
            {  
                mToggle = 0.5;
                gameSound->toggleSoundEffects();
            }
            if(mKeyboard->isKeyDown(OIS::KC_1))
            {
                gameSound->lowerMusicVolume();
            }

            if(mKeyboard->isKeyDown(OIS::KC_2))
            {
                gameSound->raiseMusicVolume();
            }
        }
        else
        {
            if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
            {
                //send host 'W'
            }
            if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
            {
                //send host 'S'
            }
            if (mKeyboard->isKeyDown(OIS::KC_A)) // Left
            {
                //send host 'A'
            }
            if (mKeyboard->isKeyDown(OIS::KC_D)) // Right
            {
                //send host 'D'
            }
            if (mToggle < 0.0f && mKeyboard->isKeyDown(OIS::KC_P))
            {
                mToggle = 0.5;
                gameSound->toggleBackground();
            }
            if (mToggle < 0.0f && mKeyboard->isKeyDown(OIS::KC_M))
            {  
                mToggle = 0.5;
                gameSound->toggleSoundEffects();
            }
            if(mKeyboard->isKeyDown(OIS::KC_1))
            {
                gameSound->lowerMusicVolume();
            }

            if(mKeyboard->isKeyDown(OIS::KC_2))
            {
                gameSound->raiseMusicVolume();
            }
        }
        if (score >= 10)
        {
            gameOver->setCaption(Ogre::DisplayString("Game Over!"));
        }
        else
        {
            Ogre::stringstream go;
            go << (int)(mTime);
            std::string str2 = go.str();

            std::string s2 = "Time: " + str2;

            gameOver->setCaption(Ogre::DisplayString(s2));
        }

        //mSceneMgr->getSceneNode("Player")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
        //mSceneMgr->getSceneNode("Player")->setPosition(transVector * evt.timeSinceLastFrame);
        ourWorld->stepSimulation(evt.timeSinceLastFrame, 1, 1.0f/60.0f);
        ball->moveBall();
        playingRoom->moveRoom();
        player->movePaddle(transVector * evt.timeSinceLastFrame);

        int numManifolds = ourWorld->getDispatcher()->getNumManifolds();
        for(int i = 0; i < numManifolds; i++) {

            btPersistentManifold* contactManifold =  ourWorld->getDispatcher()->getManifoldByIndexInternal(i);
            btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());
            if((obA->getUserPointer() == ball->ballNode) && (obB->getUserPointer() == playingRoom->wall4Node)) {
                std::cout << "Success";
            
                int numContacts = contactManifold->getNumContacts();
                for (int j=0;j<1;j++)
                {
                    btManifoldPoint& pt = contactManifold->getContactPoint(j);
                    if (pt.getDistance()<0.0000f && mCollision < 0.0f)
                    {
                        const btVector3& ptA = pt.getPositionWorldOnA();
                        const btVector3& ptB = pt.getPositionWorldOnB();
                        const btVector3& normalOnB = pt.m_normalWorldOnB;
                        score++;
                        mCollision = 0.5f;
                        Ogre::stringstream ss;
                        ss << score;
                        std::string str = ss.str();

                        std::string s = "Score: " + str;
                        scoreLabel->setCaption(Ogre::DisplayString(s)); 
                        gameSound->playScore();
                    }
                }
            }
        }

        return true;
    }

} // namespace gTech



#ifdef __cplusplus
extern "C" 
{
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
