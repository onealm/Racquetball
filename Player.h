#ifndef PLAYER_H
#define PLAYER_H

#include "BaseApplication.h"
#include "PlayingRoom.h"

namespace gTech {

class Player 
{
	protected:
		Ogre::SceneNode* playerNode;
		Ogre::Real playerRadius;
		Ogre::Vector3 playerDirection;
		Ogre::Real playerSpeed;
		PlayingRoom* playingRoom;
	public:
		Player(Ogre::SceneManager* scnMgr);
		~Player();
		void frameRenderingQueued(const Ogre::FrameEvent& evt);
		bool processUnbufferedInput(const Ogre::FrameEvent& evt);
		Ogre::SceneNode* getNode() { return playerNode; }
		void setPlayingRoom(PlayingRoom * pr) { playingRoom = pr; }
};

} // namespace gTech
#endif // PLAYER_H