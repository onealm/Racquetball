/*
-----------------------------------------------------------------------------
Filename:    Racquetball.h
-----------------------------------------------------------------------------

*/

#ifndef __Racquetball_h_
#define __Racquetball_h_

#include "BaseApplication.h"
#include <btBulletDynamicsCommon.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Ball.h"
#include "Player.h"
#include "Sound.h"
#include "NetManager.h"



//---------------------------------------------------------------------------
namespace gTech {

	class Racquetball : public BaseApplication
	{
		public:
		    Racquetball(void);
		    virtual ~Racquetball(void);

		protected:
			virtual void createFrameListener(void);
		    virtual void createScene(void);
		    virtual void createCamera(void);
		    virtual void setupLights(void);
		    virtual void setupNetworking(void);
		    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		    virtual void prepMessage(void);
		    
		    //GUI
		    OgreBites::Label* scoreLabel;
		    OgreBites::Label* gameOver;

		    //Netmanager
		    NetManager *mNet;

		private:
			virtual void initPhysics(void);
			virtual bool processUnbufferedInput(const Ogre::FrameEvent& evt);
	};

} // namespace gTech

//---------------------------------------------------------------------------

#endif // #ifndef __Racquetball_h_

//---------------------------------------------------------------------------
