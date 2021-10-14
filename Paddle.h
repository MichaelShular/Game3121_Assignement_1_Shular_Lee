#pragma once
#ifndef PADDLE_H
#define PADDLE_H

#include "Ogre.h"

using namespace Ogre;

class Paddle {
public:
	Paddle(Ogre::SceneManager* scMgr, SceneNode* SceneNode);
	~Paddle();
	Ogre::Vector3 GetPosition();
	void MoveRight();
	void MoveLeft();

private:
	SceneManager* mSceneManager;
	SceneNode* mSceneNode;
	Entity* mEntity;
	int32 mBallSpeed;
	Vector3 mBallDirection;
	int mNumLife;
	bool mStay;
};

#endif // !PADDLE_H