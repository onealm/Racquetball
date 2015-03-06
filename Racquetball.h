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
#include <string>
#include "Ball.h"
#include "Player.h"
#include "Paddle.h"
#include "Sound.h"

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
		    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		    
		    //GUI
		    OgreBites::Label* scoreLabel;

		private:
			virtual void initPhysics(void);
			virtual bool processUnbufferedInput(const Ogre::FrameEvent& evt);
	};

} // namespace gTech

//---------------------------------------------------------------------------

#endif // #ifndef __Racquetball_h_

//---------------------------------------------------------------------------
