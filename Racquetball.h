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
	    virtual void createScene(void);
	    virtual void createCamera(void);
	    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	private:
		virtual bool processUnbufferedInput(const Ogre::FrameEvent& evt);
};

} // namespace gTech

//---------------------------------------------------------------------------

#endif // #ifndef __Racquetball_h_

//---------------------------------------------------------------------------
