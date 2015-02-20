/*
-----------------------------------------------------------------------------
Filename:    Racquetball.h
-----------------------------------------------------------------------------

*/

#ifndef __Racquetball_h_
#define __Racquetball_h_

#include "BaseApplication.h"
#include "Ball.h"

//---------------------------------------------------------------------------

class Racquetball : public BaseApplication
{
public:
    Racquetball(void);
    virtual ~Racquetball(void);

protected:
    virtual void createScene(void);
    virtual void createCamera(void);
};

//---------------------------------------------------------------------------

#endif // #ifndef __Racquetball_h_

//---------------------------------------------------------------------------
