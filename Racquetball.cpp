/*
-----------------------------------------------------------------------------
Filename:    Racquetball.cpp
-----------------------------------------------------------------------------

*/

#include "Racquetball.h"

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
    mCamera->setPosition(Ogre::Vector3(250,-250,250));

    //Set Camera Direction
    mCamera->lookAt(Ogre::Vector3(0,0,0));

    //Set Near Clip Distance
    mCamera->setNearClipDistance(5);
 
    //Default Camera Controller
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}




//FROM TUTORIAL APPLICATION
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Racquetball app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
