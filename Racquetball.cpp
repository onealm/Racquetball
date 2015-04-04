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

    bool reset = false;


    btDiscreteDynamicsWorld *ourWorld;
    PlayingRoom *playingRoom;
    Ball *ball;
    Ogre::SceneNode* bNode;
    Ogre::SceneNode* pNode;
    Player *player;
    Player *player2;
    Sound *gameSound;
    std::deque<Ogre::Vector3> mWalkList;
    Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
    static Ogre::Real mMove = 1250;

    const int gameTime = 10;
    bool hitPaddle;
    bool destroyedWidgets = false;


    //Networking
    NetManager *mNet;
    Ogre::SceneNode *playerNode2;
    bool isClient = false;
    bool isServer = false;
    bool multiPlayerSetup = false;
    uint32_t buffer[8];
    int serverScore;
    int clientScore;

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
        ourWorld->setGravity(btVector3(0,-45.80f,0));
    }

    //---------------------------------------------------------------------------
    void Racquetball::createScene(void)
    {
        initPhysics();

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
        pNode = mSceneMgr->getSceneNode("Player");
        bNode = mSceneMgr->getSceneNode("Ball");
        setupNetworking();
    }

    //Setup Networking
    //Not sure if this is the right place to put this
    void Racquetball::setupNetworking(void)
    {
        mNet = new NetManager();

        if(isServer)
        {
            mNet->setupServer();
            // printf("*****I'm a Server! (and a client)\n");
        }

        if(isClient)
        {
            mNet->setupClient();
            // printf("*****I'm a Client! (and a server)\n");
        }
    }

    struct GameUpdate 
    {
        float paddle_x;
        float paddle_y;
        float paddle_z;
        float ball_x;
        float ball_y;
        float ball_z;
        int serverScore;
        int clientScore;
    };

    void Racquetball::prepServerMessage(void)
    {
        Ogre::Vector3 bPos = bNode->getPosition();
        Ogre::Vector3 pPos = pNode->getPosition();
        GameUpdate update = {pPos.x, pPos.y, pPos.z, bPos.x, bPos.y, bPos.z, serverScore, clientScore};
        GameUpdate* dest = reinterpret_cast<GameUpdate*>(&buffer[0]);
        *dest = update;
    }

    void Racquetball::prepClientMessage(void)
    {
        Ogre::Vector3 pPos = pNode->getPosition();
        GameUpdate update = {pPos.x, pPos.y, pPos.z};
        GameUpdate* dest = reinterpret_cast<GameUpdate*>(&buffer[0]);
        *dest = update;
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
        if(!isClient)
        {
            trail->addNode(mSceneMgr->getSceneNode("Ball")); 
        } 
    }
    //---------------------------------------------------------------------------

    //Create Camera
    void Racquetball::createCamera(void)
    {
        //Camera Creation
        mCamera = mSceneMgr->createCamera("PlayerCam");

        //Set Camera Position 
        mCamera->setPosition(Ogre::Vector3(0, 600, 1750));

        //Set Camera Direction
        mCamera->lookAt(Ogre::Vector3(0, 0, -1000));

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
        winCondition = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "winLabel", "First to 10 wins.", 200);
        startGame = mTrayMgr->createLabel(OgreBites::TL_LEFT, "startLabel", "Press SPACE to begin.", 200);
        gameOver = mTrayMgr->createLabel(OgreBites::TL_BOTTOM, "GameOver", "Time Left: " + gameTime, 300);
     
    }

    void Racquetball::setupMultiPlayer(void)
    {
        if(isServer)
        {
            player2 = new Player(mSceneMgr, ourWorld, true);
            multiPlayerSetup = true;

            //Ogre::SceneNode* playerNode2 = mSceneMgr->getSceneNode("Player5");
        }
        if(isClient)
        {
            player2 = new Player(mSceneMgr, ourWorld, true);
            playerNode2 = player2->getPlayerNode2();
            multiPlayerSetup = true;
            //mSceneMgr->destroySceneNode("Ball");
            //ball = new Ball(mSceneMgr, ourWorld, true);
            // Ogre::SceneNode* playerNode2 = mSceneMgr->getSceneNode("Player2");
            //Change self paddle to top paddle
        }
    }

    bool Racquetball::keyPressed( const OIS::KeyEvent& evt )
    {
        BaseApplication::keyPressed( evt );
        if(score != 10)
        {
            switch (evt.key)
            {
                //Networking
                case OIS::KC_H:
                    if(!isClient && !isServer)
                    {
                        isServer = true;
                        setupNetworking();
                    }
                    break;
                case OIS::KC_J:
                    if(!isClient && !isServer)
                    {
                        isClient = true;
                        setupNetworking();
                    }
                //Sounds
                case OIS::KC_P:
                    gameSound->toggleBackground();    
                    break;
                case OIS::KC_M:
                    gameSound->toggleSoundEffects();
                    break;
                case OIS::KC_1:
                    gameSound->lowerMusicVolume();
                    break;
                case OIS::KC_2:
                    gameSound->raiseMusicVolume();
                    break;
                //Movement
                case OIS::KC_W:
                    transVector.z -= mMove;
                    gameSound->playSwoosh();
                    break;
                case OIS::KC_S:
                    transVector.z += mMove;
                    break;
                case OIS::KC_A:
                    transVector.x -= mMove;
                    break;
                case OIS::KC_D:
                    transVector.x += mMove;
                    break;
                default:
                    break;
            }

        }
        return true;
    }

    bool Racquetball::keyReleased( const OIS::KeyEvent& evt )
    {
        BaseApplication::keyReleased( evt );
        switch (evt.key)
        {
            //Movement
            case OIS::KC_W:
                transVector.z = 0;
                break;
            case OIS::KC_S:
                transVector.z = 0;
                break;
            case OIS::KC_A:
                transVector.x = 0;
                break;
            case OIS::KC_D:
                transVector.x = 0;
                break;
            default:
                break;
        }
    }

    bool Racquetball::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
    {
        BaseApplication::mousePressed( evt, id );
        switch (id)
        {
            case OIS::MB_Left:
                transVector.y += mMove;
                break;
            case OIS::MB_Right:
                transVector.y -= mMove;
                break;
            default:
                break;
        }
        return true;
    }
    bool Racquetball::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
    {
        BaseApplication::mousePressed( evt, id );
        switch (id)
        {
            case OIS::MB_Left:
                transVector.y = 0;
                break;
            case OIS::MB_Right:
                transVector.y = 0;
                break;
            default:
                break;
        }
        return true;
    }

    bool Racquetball::processUnbufferedInput(const Ogre::FrameEvent& evt)
    {
        static Ogre::Real mToggle = 0.0;    // The time left until next toggle
        static Ogre::Real mRotate = 0.13;   // The rotate constant
        static Ogre::Real mMove = 1250;

        static Ogre::Real mTime = 0;
        static Ogre::Real mCollision = 0.0;
		uint32_t* currBuffer;

        //transVector.y = 0;     
        //NETWORKING
        if(!multiPlayerSetup && (isServer || isClient))
        {
            setupMultiPlayer();
        }

        if(reset) 
        {
            mTime += evt.timeSinceLastFrame;
        }

        mToggle -= evt.timeSinceLastFrame;
        mCollision -= evt.timeSinceLastFrame;
        

        time++;

        if (mToggle < 0.0f && mKeyboard->isKeyDown(OIS::KC_SPACE))
        {
            if(!destroyedWidgets) {
                mTrayMgr->destroyWidget(winCondition);
                mTrayMgr->destroyWidget(startGame);
                destroyedWidgets = true;
            }
            mTime = 0;
            score = 0;
            Ogre::stringstream ss;
            ss << score;
            std::string str = ss.str();

            std::string s = "Score: " + str;
            scoreLabel->setCaption(Ogre::DisplayString(s)); 

            reset = true;
            mToggle = 0.5;
            int a = rand()%2;
            int b = rand()%2;
            int c = rand()%2;
            float d = (rand() % 1000 + 1);
            float e = (rand() % 1000 + 1);
            float f = (rand() % 1000 + 1);    
            if(a){
                d = -d;
            }
            if(b){
                e = -e;
            }
            if(c){
                f = -f;
            }
            if(!isClient)
            {
                ball->getBody()->getWorldTransform().setOrigin(btVector3(0, 900, -500));
                ball->getBody()->setLinearVelocity(btVector3(d, e, f));
            }
            
        }

        //GameOver/Score
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

        
        if(reset || score==10)
        {
            ourWorld->stepSimulation(evt.timeSinceLastFrame, 1, 1.0f/60.0f);
        }
        if(!isClient)
        {
            ball->moveBall();
        }
        player->movePaddle(transVector * evt.timeSinceLastFrame);
      




        //NETWORKING
        if (true)
        {
            time = 0;
            if(isServer)
            {
                prepServerMessage();
                
                mNet->receiveClientMessages();
                currBuffer = mNet->getBuffer();   
                if(mNet->isConnected())
                {
                    mNet->sendServerMessages(buffer);
                }

                //interpret data
                GameUpdate* dest = reinterpret_cast<GameUpdate*>(&currBuffer[0]);

                //Set Pos
                player2->movePaddleTo(Ogre::Vector3(dest->paddle_x, dest->paddle_y, dest->paddle_z));
                
            } 

            if(isClient)
            {
                prepClientMessage();
                mNet->sendClientMessages(buffer);   
                mNet->receiveServerMessages(); 
                currBuffer = mNet->getBuffer();       

                //interpret data
                GameUpdate* dest = reinterpret_cast<GameUpdate*>(&currBuffer[0]);

                //Set Pos
                player2->movePaddleTo(Ogre::Vector3(dest->paddle_x, dest->paddle_y, dest->paddle_z));
                ball->moveBallTo(Ogre::Vector3(dest->ball_x, dest->ball_y, dest->ball_z));
 
            }
        }
        

        //PHYSICS
        int numManifolds = ourWorld->getDispatcher()->getNumManifolds();
        for(int i = 0; i < numManifolds; i++) 
        {

            btPersistentManifold* contactManifold =  ourWorld->getDispatcher()->getManifoldByIndexInternal(i);
            btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());

            if(!isClient)
            {
                if((obA->getUserPointer() == ball->ballNode) && (obB->getUserPointer() == player->playerNode)) 
                {
                    int numContacts = contactManifold->getNumContacts();
                    for (int j=0;j<numContacts;j ++)
                    {

                        btManifoldPoint& pt = contactManifold->getContactPoint(j);
                        if (pt.getDistance()<0.0000f)
                        {
                            // printf("Ball and player");
                            hitPaddle = true;
                        }
                    }
                }

                if((obA->getUserPointer() == ball->ballNode) && (obB->getUserPointer() == playingRoom->wall4Node)) 
                {
                    int numContacts = contactManifold->getNumContacts();
                    
                    for (int j=0;j<1;j++)
                    {
                                               
                        btManifoldPoint& pt = contactManifold->getContactPoint(j);
                        if (pt.getDistance()<0.0000f && mCollision <= 0.0f)
                        {
                            // printf("Ball and wall \n\n");
                            //std::cout << hitPaddle;
                            mCollision = 0.5f;
                            if(hitPaddle) {
                                score++;
                                gameSound->playScore();
                                hitPaddle = false;
                            }
                            Ogre::stringstream ss;
                            ss << score;
                            std::string str = ss.str();

                            std::string s = "Score: " + str;
                            scoreLabel->setCaption(Ogre::DisplayString(s)); 

                        }
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
            srand(time(NULL));
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
