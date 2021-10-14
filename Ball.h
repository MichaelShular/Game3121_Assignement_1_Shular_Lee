#pragma once
#ifndef BALL_H
#define BALL_H

#include "Ogre.h"
#include "Paddle.h"

using namespace Ogre;

class Ball {
public:
	Ball(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Paddle* pad);
	~Ball();
	Ogre::Vector3 GetPosition();
	void Reset();
	void RemoveLife();
	void SetBallDir();
	void getNumberOfLife();
	void Update(Ogre::Real real);
	
	void SetStart();
	void Moving();
	void CollisionDetection();
	
private:
	Paddle* pad;
	SceneManager* mSceneManager;
	SceneNode* mSceneNode;
	Entity* mEntity;
	int32 mBallSpeed;
	Vector3 mBallDirection;
	int mNumLife;
	bool mStay;
};

#endif // !BALL_H
