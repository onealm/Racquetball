/*
-----------------------------------------------------------------------------
Filename:    Racquetball.h
-----------------------------------------------------------------------------

*/

#ifndef __Racquetball_h_
#define __Racquetball_h_

#include "BaseApplication.h"
#include "Ball.h"
#include "Player.h"

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
	    virtual void moveBall(const Ogre::FrameEvent& evt);
	    //GUI
	    OgreBites::Label* scoreLabel;

	private:
		virtual bool processUnbufferedInput(const Ogre::FrameEvent& evt);
};

} // namespace gTech

//---------------------------------------------------------------------------

#endif // #ifndef __Racquetball_h_

//---------------------------------------------------------------------------
