/*
-----------------------------------------------------------------------------
Filename:    Sound.cpp
-----------------------------------------------------------------------------

Much code taken from SDL tutorials (init, load_files, clean_up)
*/

#include "Sound.h"

//The music that will be played 
Mix_Music* music = NULL;

//The sound effects that will be used 
Mix_Chunk *hit = NULL; 
Mix_Chunk *hit2 = NULL;
Mix_Chunk *score = NULL; 
Mix_Chunk *swoosh = NULL;

Sound::Sound(Ogre::SceneManager* scnMgr) 
{
	init();
	load_files();
}

Sound::~Sound(void)
{
	clean_up();
}

bool Sound::init() 
{ 
	//Initialize audio SDL subsystems 
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) 
	{ 
		return false; 
	} 

	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
	{ 
		return false; 
	}  

	//If everything initialized fine 
	return true; 
}

bool Sound::load_files() 
{
	printf("ENTERED LOAD\n\n\n\n\n\n");
	//Load the music 
	music = Mix_LoadMUS( "midnight-ride-01a.mp3" ); 

	//If there was a problem loading the music 
	printf("Got past MIXLOAD!!!!\n\n\n\n\n\n\n");
	if( music == NULL ) 
	{ 
		printf("ITS NULL!!!!!\n\n\n\n\n");
		return false; 
	}


	//Load the sound effects 
	hit = Mix_LoadWAV( "tennis_ball_bounce_on_racket_001.wav" );
	hit2 = Mix_LoadWAV("tennis_ball_bounce_on_racket_002.wav");
	score = Mix_LoadWAV( "magic-chime-01.wav" ); 
	swoosh = Mix_LoadWAV( "tennis_racket_fast_movement_swoosh_002.wav" ); 

	//If there was a problem loading the sound effects 
	if(( score == NULL ) || ( hit == NULL ) || ( swoosh == NULL ) ) 
	{ 
		printf("THERE WAS A PROBLEM LOADING THE SOUND EFFECTS! \n\n\n\n");
		return false; 
	} 

	//If everything loaded fine 
	return true; 
}

void Sound::playHit()
{
	 if ((Mix_PlayChannel( -1, hit, 0 )) == -1)
	 	printf("Not playing hit\n\n\n\n\n");

}

void Sound::playHit2()
{
	 if ((Mix_PlayChannel( -1, hit2, 0 )) == -1)
	 	printf("Not playing hit2\n\n\n\n\n");

}

void Sound::playScore()
{
	 if ((Mix_PlayChannel( -1, score, 0 )) == -1)
	 	printf("Not playing score\n\n\n\n\n");

}

void Sound::playSwoosh()
{
	 if ((Mix_PlayChannel( -1, swoosh, 0 )) == -1)
	 {
	 	printf("Not playing swoosh\n\n\n\n\n");
	 }

}

void Sound::clean_up()
{
	// //Free the sound effects 
	
	Mix_FreeChunk( score ); 
	Mix_FreeChunk( hit ); 
	Mix_FreeChunk( swoosh ); 

	//Free the music 
	Mix_FreeMusic( music ); 

	//Quit SDL_mixer 
	Mix_CloseAudio(); 

	//Quit SDL 
	SDL_Quit();
}

void Sound::setBackgroundMusic()
{
	Mix_PlayMusic( music, -1 );
	Mix_VolumeMusic(50);
}

void Sound::toggleBackground()
{
        //If there is no music playing 
        if( Mix_PlayingMusic() == 0 ) 
        { 
        	//Play the music 
        	if( Mix_PlayMusic( music, -1 ) == -1 ) 
        	{ 
        		printf("WRONG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n");
        	} 
        }
        else
        {
        	//If the music is paused 
        	if( Mix_PausedMusic() == 1 ) 
        	{ 
        		//Resume the music 
        		Mix_ResumeMusic(); 
        	} 
        	//If the music is playing 
        	else 
        	{ 
        		//Pause the music 
        		Mix_PauseMusic();
        	}
        }
}

void Sound::stopSoundEffects()
{
	Mix_Volume(-1, 0);
}

void Sound::startSoundEffects()
{
	Mix_Volume(-1, 64);
}

void Sound::toggleSoundEffects()
{
	if(Mix_Volume(-1, -1) == 0)
	{
		startSoundEffects();
	}
	else if(Mix_Volume(-1, -1) > 0)
	{
		stopSoundEffects();
	}
}

void Sound::lowerMusicVolume()
{
	int volume = Mix_VolumeMusic(-1);
	if(volume > 0)
	{
		Mix_VolumeMusic(--volume);
	}	
}

void Sound::raiseMusicVolume()
{
	int volume = Mix_VolumeMusic(-1);
	if(volume < 128)
	{
		Mix_VolumeMusic(++volume);
	}	
}

