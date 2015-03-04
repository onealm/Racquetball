/*
-----------------------------------------------------------------------------
Filename:    Sound.cpp
-----------------------------------------------------------------------------

Much code taken from SDL tutorials (init,)
*/

#include "Sound.h"

//The music that will be played 
Mix_Music* music = NULL;



//The sound effects that will be used 
Mix_Chunk *score = NULL; 
Mix_Chunk *hit = NULL; 
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
	score = Mix_LoadWAV( "magic-chime-01.mp3" ); 
	hit = Mix_LoadWAV( "tennis_ball_bounce_on_racket_001.mp3" ); 
	swoosh = Mix_LoadWAV( "tennis_racket_fast_movement_swoosh_002.mp3" ); 

	//If there was a problem loading the sound effects 
	if(( score == NULL ) || ( hit == NULL ) || ( swoosh == NULL ) ) 
	{ 
		return false; 
	} 

	//If everything loaded fine 
	return true; 
}
void Sound::playSwoosh()
{
	printf("Playing swoosh\n\n\n\n\n");
	 if ((Mix_PlayChannel( -1, score, -1 )) == -1)
	 	printf("Not playing swoosh\n\n\n\n\n");

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

