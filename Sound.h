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
	void stopSoundEffects();
	void startSoundEffects();

public:
	Sound(Ogre::SceneManager* scnMgr);
	~Sound();
	void toggleBackground();
	void setBackgroundMusic();
	void playHit();
	void playHit2();
	void playScore();
	void playSwoosh();
	void toggleSoundEffects();
	void lowerMusicVolume();
	void raiseMusicVolume();
};

#endif // SOUND_H
