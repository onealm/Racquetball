/*
-----------------------------------------------------------------------------
Filename:    Sound.h
-----------------------------------------------------------------------------

*/
#ifndef SOUND_H
#define SOUND_H

#include "BaseApplication.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class Sound 
{
protected:
	bool init(); 
	bool load_files();
	void clean_up();

public:
	Sound(Ogre::SceneManager* scnMgr);
	~Sound();
	void toggleBackground();
	void setBackgroundMusic();
	void playSwoosh();
};

#endif // SOUND_H