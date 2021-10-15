#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include "Ogre.h"

using namespace Ogre;
/// This class is used to create and control aspects the object paddle.
class Paddle {
public:
	Paddle(Ogre::SceneManager* scMgr, SceneNode* SceneNode);
	/// Paddle destructor.
	~Paddle() {};
	Ogre::Vector3 GetPosition();
	void MoveRight();
	void MoveLeft();
	AxisAlignedBox GetWorldAABB();
private:
	SceneManager* mSceneManager;
	SceneNode* mSceneNode;
	Entity* mEntity;	
};

#endif // !PADDLE_H
